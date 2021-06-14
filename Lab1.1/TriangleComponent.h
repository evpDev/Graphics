#pragma once
#include <wrl.h>
#include "GameComponent.h"
#include "ProjectUtils.h"
#include "DisplayWin32.h"

#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>

class TriangleComponent : public GameComponent {
public:
	const static int VERTICLES_NUM = 3;
	int points;
	DirectX::XMFLOAT4 positions[4];
	DirectX::XMFLOAT4 colors[4];
	int rastState;
	int verticles[3];

	TriangleComponent();
	TriangleComponent(int* indexes);
	TriangleComponent(DirectX::XMFLOAT4* positions, DirectX::XMFLOAT4* colors, int posColSize, int* indexes);
	void destroyResources();
	void draw();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName = "VSMain", LPCSTR pixelShaderName = "PSMain");
	void reload();
	void update();

	int* getIndexes();
	int getIndexesSize();
	void release();

	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
};