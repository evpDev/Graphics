#pragma once

#include "windows.h"

#include "DisplayWin32.h"
#include "InputDevice.h"
#include "TriangleComponent.h"
#include "PyramidComponent.h"
#include "CubeComponent.h"
#include "PlaneComponent.h"
#include "CustomMeshComponent.h"
#include "Keys.h"
#include "TextureLoader.h"
#include <vector>
#pragma comment(lib, "dxgi.lib")
#include <chrono>

#include <d3d.h>
#include <d3d11_1.h>
#include <d3d11_4.h>

class TextureLoader;
class InputDevice;

class Game {
public:
	ID3D11Texture2D* backBuffer;
	ID3D11DeviceContext* context;
	ID3D11Debug* debug;
	ID3DUserDefinedAnnotation* annotation;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	LPCWSTR name;
	std::chrono::time_point<std::chrono::steady_clock> prevTime;
	int renderSRV;
	ID3D11RenderTargetView* rtv;
	int screenResized;
	int startTime;
	IDXGISwapChain* swapChain;
	IDXGISwapChain1* swapChain1; // there is no in scheme
	float totalTime;
	unsigned int frameCount; // there is no in scheme
	DisplayWin32* display;
	std::vector<GameComponent*> components;
	GameComponent* component;
	
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
	ID3D11Buffer* constBuff;
	InputDevice* inputDevice;
	float orthoScale;
	float perspectScale;
	boolean isPerspectiveView;
	TextureLoader* textureLoader;

	Game(HINSTANCE hInstance);
	void createBackBuffer();
	void destroyResources();
	void draw();
	void endFrame();
	void exit();
	int initialize(HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow);
	LRESULT messageHandler(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
	int prepareResources();
	void restoreTargets();
	void run();
	void update();
	void updateInternal();

	HRESULT initMatrixes();
	void setMatrixes();
	int prepareFrame();
};