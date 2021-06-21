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

	CustomMeshComponent();
	CustomMeshComponent(Game* g);
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName, LPCSTR pixelShaderName);
	int initialize();

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();
	void release();

	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
};