#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() {}

MeshRenderer::MeshRenderer(MeshFilter* mesh, void* points) : mesh(mesh), points(points) {}

void MeshRenderer::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff2, UINT pointsTypeSize) {
	context->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &offset);
	context->IASetIndexBuffer(indexBuff, DXGI_FORMAT_R16_UINT, 0);
	context->IASetInputLayout(layout);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);
	context->VSSetConstantBuffers(0, 1, &constBuff);
}

void MeshRenderer::update(ID3D11DeviceContext* context, ConstantBuffer* cb) {
	context->UpdateSubresource(constBuff, 0, NULL, cb, 0, 0);
}

int MeshRenderer::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, UINT pointsTypeSize, ID3D11Buffer** constBuff2, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {
	HRESULT res;
	ID3DBlob* errorVertexCode;
	stride = pointsTypeSize;
	offset = 0;

	res = D3DCompileFromFile(L"MiniTri.fx",
		nullptr /*macros*/,
		nullptr /*include*/,
		vertexShaderName,
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexShaderByteCode,
		&errorVertexCode);

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(display->hWnd, L"MiniTri.fx", L"Missing Shader File", MB_OK);
		}

		return 0;
	}


	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

	ID3DBlob* errorPixelCode;
	res = D3DCompileFromFile(L"MiniTri.fx",
		nullptr /*macros*/,
		nullptr /*include*/,
		pixelShaderName,
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pixelShaderByteCode,
		&errorPixelCode);

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorPixelCode) {
			char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(display->hWnd, L"MiniTri.fx", L"Missing Shader File", MB_OK);
		}

		return 0;
	}

	device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader);

	device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader);

	/*-------------------------Init buffers------------------------------*/
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = pointsTypeSize * mesh->getPointsSize();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.ByteWidth = sizeof(WORD) * mesh->getIndexesSize();
	bd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd2.CPUAccessFlags = 0;
	/*-------------------------Init buffers------------------------------*/

	/*-------------------------Constant Buffer------------------------------*/
	constantBufDesc = {};
	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = 0;
	constantBufDesc.MiscFlags = 0;
	constantBufDesc.StructureByteStride = 0;
	constantBufDesc.ByteWidth = sizeof(ConstantBuffer);
	/*-------------------------Constant Buffer------------------------------*/

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = points;
	res = device->CreateBuffer(&bd, &InitData, &vertexBuff); ZCHECK(res);
	InitData.pSysMem = mesh->getIndexes();
	res = device->CreateBuffer(&bd2, &InitData, &indexBuff); ZCHECK(res);
	res = device->CreateBuffer(&constantBufDesc, NULL, &constBuff); ZCHECK(res);
}

//HRESULT MeshRenderer::initMatrixes(DisplayWin32* display) {
//	RECT rc;
//	GetClientRect(display->hWnd, &rc);
//	UINT width = rc.right - rc.left;
//	UINT height = rc.bottom - rc.top;
//
//	world = XMMatrixIdentity();
//
//	XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -8.0f, 0.0f);
//	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//	view = XMMatrixLookAtLH(Eye, At, Up);
//
//	//projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
//	projection = XMMatrixOrthographicLH(orthoScale, orthoScale, 0.01f, 1000.0f);
//
//	cb.mWorld = XMMatrixTranspose(world);
//	cb.mView = XMMatrixTranspose(view);
//	cb.mProjection = XMMatrixTranspose(projection);
//
//	return S_OK;
//}

void MeshRenderer::initLayout(Microsoft::WRL::ComPtr<ID3D11Device> device, D3D11_INPUT_ELEMENT_DESC* inputElements, int inputElementsSize) {
	device->CreateInputLayout(inputElements, inputElementsSize, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);
	/*LPCWSTR filename = L"SARS_CoV_2_Vaccine_Red_Diffuse.png";
	g->textureLoader->loadTextureFromFile(filename, texture, texSRV, true, false, 0);*/
}