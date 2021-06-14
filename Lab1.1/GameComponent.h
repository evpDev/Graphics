#pragma once
//#include "Game.h"
#include <directxmath.h>
#include <wrl.h>
#include "DisplayWin32.h"
#include "windows.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"

#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>

struct Transform {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	Transform();
};

class GameComponent {
	//Game game;
public:
	Transform transform;
	MeshFilter* mesh;
	MeshRenderer* meshRenderer;
	//
	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;
	ID3DBlob* errorVertexCode;
	//

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
	virtual void release();
};