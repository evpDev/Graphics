#pragma once
#include "PyramidComponent.h"
#include "ProjectUtils.h"

class CubeComponent : public PyramidComponent {
public:
	SimpleVertex points[8];
	WORD indexes[36];

	CubeComponent();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device);

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();

	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
};