#pragma once
#include <wrl.h>
#include "GameComponent.h"
#include "DisplayWin32.h"

#include <d3d11.h>

class PyramidComponent : public GameComponent {
public:
	SimpleVertex points[5];
	WORD indexes[18];
	//ID3D11InputLayout* layout;

	PyramidComponent();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device);
	int initialize();

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();
};