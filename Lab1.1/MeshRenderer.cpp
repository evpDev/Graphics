#include "MeshRenderer.h"

MeshRenderer::MeshRenderer() : wasSet(false) {}

MeshRenderer::MeshRenderer(MeshFilter* mesh, void* points) : wasSet(false), mesh(mesh), points(points) {}

int MeshRenderer::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff, UINT pointsTypeSize) {
	HRESULT res;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = pointsTypeSize * mesh->getPointsSize();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = points;
	if (!wasSet) {
		res = device->CreateBuffer(&bd, &InitData, &vertexBuff); ZCHECK(res);
	}

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * mesh->getIndexesSize();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = mesh->getIndexes();

	if (!wasSet) {
		res = device->CreateBuffer(&bd, &InitData, &indexBuff); ZCHECK(res);
	}

	UINT stride = pointsTypeSize;
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &offset);
	context->IASetIndexBuffer(indexBuff, DXGI_FORMAT_R16_UINT, 0);

	/*-------------------------Constant Buffer------------------------------*/
	constantBufDesc = {};
	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = 0;
	constantBufDesc.MiscFlags = 0;
	constantBufDesc.StructureByteStride = 0;
	constantBufDesc.ByteWidth = sizeof(ConstantBuffer);

	if (!wasSet) {
		res = device->CreateBuffer(&constantBufDesc, NULL, constBuff); ZCHECK(res);
	}
	/*-------------------------Constant Buffer------------------------------*/

	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	if (!wasSet) {
		res = device->CreateSamplerState(&sampDesc, &samplerLinear); ZCHECK(res);
	}

	context->IASetInputLayout(layout);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);
	context->VSSetConstantBuffers(0, 1, constBuff);
}

int MeshRenderer::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {
	HRESULT res;
	ID3DBlob* errorVertexCode;
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
}

void MeshRenderer::initLayout(Microsoft::WRL::ComPtr<ID3D11Device> device, D3D11_INPUT_ELEMENT_DESC* inputElements, int inputElementsSize) {
	device->CreateInputLayout(inputElements, inputElementsSize, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);
	/*LPCWSTR filename = L"SARS_CoV_2_Vaccine_Red_Diffuse.png";
	g->textureLoader->loadTextureFromFile(filename, texture, texSRV, true, false, 0);*/
}