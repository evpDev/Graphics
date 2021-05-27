#include "PyramidComponent.h"

using namespace DirectX;

PyramidComponent::PyramidComponent() :
	points {
		{ XMFLOAT3( 0.0f,  1.5f,  0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f,  0.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3( 1.0f,  0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f,  0.0f,  1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 1.0f,  0.0f,  1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) }
	},
	indexes {
		0,2,1,
		0,3,4,
		0,1,3,
		0,4,2,
		1,2,3,
		2,4,3,
	} {}

int PyramidComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device) {

	GameComponent::initialize(display, device);

	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElements2, 2, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);

	return 0;
}

int PyramidComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) {
	return 0;
}

int* PyramidComponent::getIndexes() {
	return (int*) indexes;
}

int PyramidComponent::getIndexesSize() {
	return std::size(indexes);
}

int* PyramidComponent::getPoints() {
	return (int*) points;
}

int PyramidComponent::getPointsSize() {
	return std::size(points);
}