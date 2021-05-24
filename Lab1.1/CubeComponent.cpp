#include "CubeComponent.h"

using namespace DirectX;

CubeComponent::CubeComponent() :
	points{
		{ XMFLOAT3(-1.0f,  2.0f,  1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f,  2.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3( 1.0f,  2.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3( 1.0f,  2.0f,  1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f,  0.0f,  1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f,  0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 1.0f,  0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 1.0f,  0.0f,  1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) }
	},
	indexes {
		0,1,2, 0,3,7, 2,1,5,
		0,2,3, 0,7,4, 2,5,6,
		3,2,6, 5,1,0, 7,6,5,
		3,6,7, 5,0,4, 7,5,4,
	} {}

int CubeComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device) {

	GameComponent::initialize(display, device);

	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElements2, 2, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);

	return 0;
}

int* CubeComponent::getIndexes() {
	return (int*)indexes;
}

int CubeComponent::getIndexesSize() {
	return std::size(indexes);
}

int* CubeComponent::getPoints() {
	return (int*) points;
}

int CubeComponent::getPointsSize() {
	return std::size(points);
}