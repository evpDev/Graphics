#pragma once
//#include "windows.h"
#include "DisplayWin32.h"
#include "ProjectUtils.h"
#include "MeshFilter.h"
//#include "TextureLoader.h"
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <iostream>

class MeshRenderer {
public:
	D3D11_BUFFER_DESC bd;
	D3D11_BUFFER_DESC constantBufDesc;
	D3D11_SUBRESOURCE_DATA InitData;
	ID3D11Buffer* vertexBuff;
	ID3D11Buffer* indexBuff;
	MeshFilter* mesh;
	void* points;

	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;
	ID3DBlob* errorVertexCode;

	bool wasSet;

	MeshRenderer();
	MeshRenderer(MeshFilter* mesh, void* points);
	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff, UINT pointsTypeSize);
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName = "", LPCSTR pixelShaderName = "");
	void initLayout(Microsoft::WRL::ComPtr<ID3D11Device> device, D3D11_INPUT_ELEMENT_DESC* inputElements, int inputElementsSize);
};