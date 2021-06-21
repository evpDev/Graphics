#pragma once

#include "tiny_obj_loader.h"
#include "GameComponent.h"
#include "ProjectUtils.h"
#include "TextureLoader.h"
#include "Game.h"
#include <d3d11.h>

//#pragma comment(lib, "d3dx11.lib")

class Game;

class CustomMeshComponent : public GameComponent {
public:
	SimpleExtendedVertex* points;
	Game* g;

	D3D11_SAMPLER_DESC sampDesc;
	ID3D11Texture2D* texture;
	ID3D11SamplerState* samplerLinear;
	ID3D11ShaderResourceView* texSRV;

	CustomMeshComponent();
	CustomMeshComponent(Game* g);
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff, LPCSTR vertexShaderName, LPCSTR pixelShaderName);
	int initialize();
	void draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
	void update(ID3D11DeviceContext* context, ConstantBuffer* cb);

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();
	void release();
};