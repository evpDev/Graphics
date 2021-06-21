#include "CubeComponent.h"

using namespace DirectX;

CubeComponent::CubeComponent() :
	points {
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
	} {
	mesh = new MeshFilter(points, sizeof(points), indexes, sizeof(indexes));
	meshRenderer = new MeshRenderer(mesh, points);
}

int CubeComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {

	meshRenderer->initialize(display, device, sizeof(SimpleVertex), constBuff, "VSMainColor", "PSMainColor");

	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	meshRenderer->initLayout(device, inputElements2, 2);

	return 0;
}

void CubeComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) {
	meshRenderer->draw(context, device, constBuff, sizeof(SimpleVertex));
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

int* CubeComponent::getIndexes() {
	return mesh->getIndexes();
}

int CubeComponent::getIndexesSize() {
	return mesh->getIndexesSize();
}

int* CubeComponent::getPoints() {
	return mesh->getPoints();
}

int CubeComponent::getPointsSize() {
	return mesh->getPointsSize();
}

void CubeComponent::release() {
	meshRenderer->vertexShader->Release();
	meshRenderer->pixelShader->Release();
}