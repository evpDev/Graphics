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
	} {
	mesh = new MeshFilter(points, sizeof(points), indexes, sizeof(indexes));
	meshRenderer = new MeshRenderer(mesh, points);
}

int PyramidComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {

	meshRenderer->initialize(display, device, sizeof(SimpleVertex), "VSMainColor", "PSMainColor");

	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	meshRenderer->initLayout(device, inputElements2, 2);

	return 0;
}

void PyramidComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device) {
	meshRenderer->draw(context, device, sizeof(SimpleVertex));
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

int* PyramidComponent::getIndexes() {
	return mesh->getIndexes();
}

int PyramidComponent::getIndexesSize() {
	return mesh->getIndexesSize();
}

int* PyramidComponent::getPoints() {
	return mesh->getPoints();
}

int PyramidComponent::getPointsSize() {
	return mesh->getPointsSize();
}

void PyramidComponent::release() {
	meshRenderer->vertexShader->Release();
	meshRenderer->pixelShader->Release();
}