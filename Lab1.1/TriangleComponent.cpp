#include "TriangleComponent.h"

using namespace DirectX;

TriangleComponent::TriangleComponent() {}

TriangleComponent::TriangleComponent(int* inds) :
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
	
	int pointsSize = 4;
	points = (SimpleVertex*) malloc(sizeof(SimpleVertex) * pointsSize);
	for (int i = 0; i < pointsSize; i++) {
		points[i] = {
			XMFLOAT3(positions[i].x, positions[i].y, positions[i].z),
			XMFLOAT4(colors[i].x, colors[i].y, colors[i].z, colors[i].w)
		};
	}
	indexes = (WORD*) malloc(sizeof(WORD) * VERTICLES_NUM);
	std::copy(inds, inds + VERTICLES_NUM, indexes);
	mesh = new MeshFilter(points, pointsSize, indexes, VERTICLES_NUM);
	meshRenderer = new MeshRenderer(mesh, points);
}

TriangleComponent::TriangleComponent(DirectX::XMFLOAT4* positions, 
		DirectX::XMFLOAT4* colors, 
		int posColSize,
		int* indexes
) {
	std::copy(positions, positions + posColSize, this->positions);
	std::copy(colors, colors + posColSize, this->colors);
	//std::copy(indexes, indexes + VERTICLES_NUM, this->verticles);
 }

int TriangleComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {
	
	meshRenderer->initialize(display, device, sizeof(SimpleVertex), constBuff, "VSMainColor", "PSMainColor");
	
	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	meshRenderer->initLayout(device, inputElements2, 2);

	return 0;
}

void TriangleComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) {
	meshRenderer->draw(context, device, constBuff, sizeof(SimpleVertex));
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

int* TriangleComponent::getIndexes() {
	return mesh->getIndexes();
}

int TriangleComponent::getIndexesSize() {
	return mesh->getIndexesSize();
}

int* TriangleComponent::getPoints() {
	return mesh->getPoints();
}

int TriangleComponent::getPointsSize() {
	return mesh->getPointsSize();
}

void TriangleComponent::release() {
	meshRenderer->vertexShader->Release();
	meshRenderer->pixelShader->Release();
}