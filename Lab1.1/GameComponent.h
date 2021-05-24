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
	void draw();

	virtual int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device);
	void reload();
	void update();

	virtual int* getIndexes() = 0;
	virtual int getIndexesSize() = 0;
	virtual int* getPoints();
	virtual int getPointsSize();

};