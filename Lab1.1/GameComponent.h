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

	GameComponent();
	void destroyResources();
	virtual void draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device) = 0;

	virtual int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName = "", LPCSTR pixelShaderName = "");
	void reload();
	virtual void update(ID3D11DeviceContext* context, ConstantBuffer* cb);

	virtual int* getIndexes() = 0;
	virtual int getIndexesSize() = 0;
	virtual int* getPoints();
	virtual int getPointsSize();
	virtual void release();
};