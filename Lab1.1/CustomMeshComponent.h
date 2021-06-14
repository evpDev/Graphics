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
	//SimpleVertex points[5];
	//DirectX::XMFLOAT3* points2;
	SimpleExtendedVertex* points2;
	int pointsSize;
	WORD* indexes;
	int indexesSize;

	ID3D11Buffer* vertexBuff;
	D3D11_BUFFER_DESC bd;
	ID3D11Buffer* indexBuff;
	D3D11_BUFFER_DESC constantBufDesc;
	D3D11_SUBRESOURCE_DATA InitData;
	D3D11_SAMPLER_DESC sampDesc;
	Game* g;

	ID3D11Texture2D* texture;
	ID3D11SamplerState* samplerLinear;
	ID3D11ShaderResourceView* texSRV;

	bool wasSet;

	CustomMeshComponent();
	CustomMeshComponent(Game* g);
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName, LPCSTR pixelShaderName);
	void initPoints(tinyobj::attrib_t* attrib, std::vector<tinyobj::shape_t>* shapes);
	int initialize();

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();

	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
};