#pragma once
#include "GameComponent.h"
#include "ProjectUtils.h"

class CubeComponent : public GameComponent {
public:
	SimpleVertex points[8];
	WORD indexes[36];

	CubeComponent();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName = "VSMain", LPCSTR pixelShaderName = "PSMain");

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();

	int draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
};