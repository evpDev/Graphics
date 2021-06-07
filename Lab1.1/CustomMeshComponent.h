#pragma once

#include "GameComponent.h"
#include "ProjectUtils.h"

class CustomMeshComponent : public GameComponent {
public:
	SimpleVertex points[5];
	//DirectX::XMFLOAT3* points2;
	SimpleVertex* points2;
	int pointsSize;
	WORD* indexes;
	int indexesSize;

	ID3D11Buffer* vertexBuff;
	D3D11_BUFFER_DESC bd;
	ID3D11Buffer* indexBuff;
	D3D11_BUFFER_DESC constantBufDesc;
	D3D11_SUBRESOURCE_DATA InitData;

	bool wasSet;

	CustomMeshComponent();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device);
	int initialize();

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();

	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
};