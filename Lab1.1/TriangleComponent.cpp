#include "TriangleComponent.h"

using namespace DirectX;

TriangleComponent::TriangleComponent() {}

TriangleComponent::TriangleComponent(int* indexes) :
	positions { 
		XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),
		XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f),
		XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f),
		XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f), 
	},
	colors {
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	}
{	
	std::copy(indexes, indexes + VERTICLES_NUM, verticles);
}

TriangleComponent::TriangleComponent(DirectX::XMFLOAT4* positions, 
		DirectX::XMFLOAT4* colors, 
		int posColSize,
		int* indexes
) {
	std::copy(positions, positions + posColSize, this->positions);
	std::copy(colors, colors + posColSize, this->colors);
	std::copy(indexes, indexes + VERTICLES_NUM, this->verticles);
 }

int TriangleComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device) {
	
	GameComponent::initialize(display, device);
	
	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElements2, 2, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);

	return 0;
}

int* TriangleComponent::getIndexes() {
	return verticles;
}

int TriangleComponent::getIndexesSize() {
	return std::size(verticles);
}