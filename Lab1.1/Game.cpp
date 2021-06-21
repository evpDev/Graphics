#include "Game.h"
#include "DisplayWin32.h"

#pragma warning(disable : 4267)

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include "winuser.h"
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <d3dcompiler.h>
#include <DirectXColors.h>
#include <thread>

#define ZCHECK(exp) if(FAILED(exp)) { printf("Check failed at file: %s at line %i", __FILE__, __LINE__); return 0; }

using namespace DirectX;

LRESULT Game::messageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	//auto id = std::this_thread::get_id();
	//std::cout << "WndProc id: " << id << "\n";

	switch (umessage) {
		// Check if the window is being destroyed.
		case WM_DESTROY:
		case WM_CLOSE: {
			PostQuitMessage(0);
			return 0;
		}

		case WM_SIZE: {
			std::cout << "Width " << LOWORD(lparam) << " Height " << HIWORD(lparam) << std::endl;

			return 0;
		}

		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN: {
			// If a key is pressed send it to the input object so it can record that state.
			std::cout << "Key: " << static_cast<unsigned int>(wparam) << std::endl;
			inputDevice->onKeyDown(static_cast<unsigned int>(wparam));
			if (static_cast<unsigned int>(wparam) == static_cast<unsigned int>(Keys::Escape)) PostQuitMessage(0);

			break;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP: {
			// If a key is released then send it to the input object so it can unset the state for that key.
			return 0;
		}

		case WM_MOUSEWHEEL: {
			inputDevice->onMouseWheel(static_cast<unsigned int>(wparam));
			std::cout << "Key: " << static_cast<unsigned int>(wparam) << std::endl;
			break;
		}

		// All other messages pass to the message handler in the system class.
		default: {
			return DefWindowProc(hwnd, umessage, wparam, lparam);
		}
	}

	cb->mWorld = XMMatrixTranspose(world);
	cb->mView = XMMatrixTranspose(view);
	cb->mProjection = XMMatrixTranspose(projection);
	return 0;
}

Game::Game(HINSTANCE hInstance) : textureLoader(new TextureLoader(this)) {
	name = L"Game";
	display = new DisplayWin32(name, hInstance, 800, 800);
	float totalTime = 0;
	unsigned int frameCount = 0;
	orthoScale = 5;
	perspectScale = -5;
	isPerspectiveView = false;
	inputDevice = new InputDevice(this);
	cb = new ConstantBuffer();

	components.push_back(new PlaneComponent());
	//components.push_back(new CubeComponent());
	//components.push_back(new PyramidComponent());
	/*int indxes[] = { 0,1,2 };
	components.push_back(new TriangleComponent(indxes));
	int indxes2[] = { 1,0,3 };
	components.push_back(new TriangleComponent(indxes2));*/

	components.push_back(new CustomMeshComponent(this));
}

int Game::initialize(HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	HRESULT res;

	prepareResources();

	for (GameComponent* tc : components) {
		tc->initialize(display, device);
	}

	prepareFrame();
	initMatrixes();

	return 0;
}

void Game::run() {
	MSG msg = {};

	// Loop until there is a quit message from the window or the user.
	bool isExitRequested = false;
	while (!isExitRequested) {
		// Handle the windows messages.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			isExitRequested = true;
		}

		draw();
	}
}

void Game::draw() {
	auto	curTime = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
	prevTime = curTime;

	totalTime += deltaTime;
	frameCount++;

	if (totalTime > 1.0f) {
		float fps = frameCount / totalTime;

		totalTime = 0.0f;

		WCHAR text[256];
		swprintf_s(text, TEXT("FPS: %f"), fps);
		SetWindowText(display->hWnd, text);

		frameCount = 0;
	}

	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	context->OMSetRenderTargets(1, &rtv, nullptr);

	context->ClearRenderTargetView(rtv, color);

	annotation->BeginEvent(L"BeginDraw");

	for (GameComponent* gc : components) {
		gc->draw(context, device);
		gc->update(context, cb);
		context->DrawIndexed(gc->getIndexesSize(), 0, 0);
	}
	annotation->EndEvent();

	endFrame();
}

int Game::prepareFrame() {
	HRESULT res;

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_FRONT;// D3D11_CULL_NONE;D3D11_CULL_BACK;D3D11_CULL_FRONT
	rastDesc.FillMode = D3D11_FILL_SOLID;//D3D11_FILL_SOLID;D3D11_FILL_WIREFRAME

	ID3D11RasterizerState* rastState;
	res = device->CreateRasterizerState(&rastDesc, &rastState); ZCHECK(res);

	context->RSSetState(rastState);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(display->screenWidth);
	viewport.Height = static_cast<float>(display->screenHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);
	context->OMSetRenderTargets(1, &rtv, nullptr);
}

int Game::prepareResources() {
	HRESULT res;

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = display->screenWidth;
	swapDesc.BufferDesc.Height = display->screenHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = display->hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;


	//Microsoft::WRL::ComPtr<ID3D11Device> device;

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&device,
		nullptr,
		&context);

	ZCHECK(res);

	//ID3D11Texture2D* backTex;
	res = swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backBuffer);	ZCHECK(res);
	res = device->CreateRenderTargetView(backBuffer, nullptr, &rtv);			ZCHECK(res);

	swapChain->QueryInterface<IDXGISwapChain1>(&swapChain1);

	context->QueryInterface(IID_ID3DUserDefinedAnnotation, (void**)&annotation);

	//ID3D11Debug* debug;
	device->QueryInterface(IID_ID3D11Debug, (void**)&debug);

}

void Game::destroyResources() {
	for (GameComponent* gc : components) {
		gc->release();
	}

	device->Release();
	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
}

void Game::endFrame() {
	swapChain1->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}

HRESULT Game::initMatrixes() {
	RECT rc;
	GetClientRect(display->hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	world = XMMatrixIdentity();

	XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -8.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	view = XMMatrixLookAtLH(Eye, At, Up);

	//projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
	projection = XMMatrixOrthographicLH(orthoScale, orthoScale, 0.01f, 1000.0f);

	cb->mWorld = XMMatrixTranspose(world);
	cb->mView = XMMatrixTranspose(view);
	cb->mProjection = XMMatrixTranspose(projection);

	return S_OK;
}