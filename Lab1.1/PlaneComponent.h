#pragma once
#include "GameComponent.h"
#include "ProjectUtils.h"

class PlaneComponent : public GameComponent {
public:
	SimpleVertex points[40];
	WORD indexes[40];

	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;
	ID3D11Buffer* indexBuff;
	ID3D11Buffer* vertexBuff;
	D3D11_BUFFER_DESC constantBufDesc;
	bool wasSet;

	PlaneComponent();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device);

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();

	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
};