#pragma once
#include <wrl.h>
#include "GameComponent.h"
#include "DisplayWin32.h"

#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>
//#pragma comment(lib, "d3d11.lib")
#include <directxmath.h>

class TriangleComponent {// : public GameComponent {
public:
	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;
	int points;
	DirectX::XMFLOAT4 positions[4];
	DirectX::XMFLOAT4 colors[4];
	int rastState;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;
	ID3DBlob* errorVertexCode;
	int verticles;

	TriangleComponent();
	void destroyResources();
	void draw();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device);
	void reload();
	void update();
};