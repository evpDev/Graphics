#pragma once
#include <wrl.h>
#include "GameComponent.h"
#include "ProjectUtils.h"
#include "DisplayWin32.h"

#include <d3d11.h>

class PyramidComponent : public GameComponent {
public:
	SimpleVertex points[5];
	WORD indexes[18];

	PyramidComponent();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff, LPCSTR vertexShaderName = "VSMain", LPCSTR pixelShaderName = "PSMain");
	int initialize();
	void draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();
	void release();
};