#pragma once
#include "GameComponent.h"
#include "ProjectUtils.h"

class PlaneComponent : public GameComponent {
public:
	SimpleVertex* points;
	WORD* indexes;

	PlaneComponent();
	int initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff, LPCSTR vertexShaderName = "VSMain", LPCSTR pixelShaderName = "PSMain");
	void draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff);
	void update(ID3D11DeviceContext* context, ConstantBuffer* cb);

	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();
	void release();
};