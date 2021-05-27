#pragma once
#include "GameComponent.h"
#include "ProjectUtils.h"

class PlaneComponent : public GameComponent {
public:
	SimpleVertex points[40];
	WORD indexes[40];

	PlaneComponent();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device);

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();

	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
};