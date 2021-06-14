#pragma once
//#include "Game.h"
#include <directxmath.h>
#include <wrl.h>
#include "DisplayWin32.h"
#include "windows.h"

#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>

struct SimpleVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct SimpleExtendedVertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 Tex;
	DirectX::XMFLOAT3 Normal;
};

class GameComponent {
	//Game game;
public:
	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;
	ID3DBlob* errorVertexCode;

	GameComponent();
	void destroyResources();
	virtual int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) = 0;

	virtual int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName = "", LPCSTR pixelShaderName = "");
	void reload();
	void update();

	virtual int* getIndexes() = 0;
	virtual int getIndexesSize() = 0;
	virtual int* getPoints();
	virtual int getPointsSize();

};