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

int TriangleComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {
	
	GameComponent::initialize(display, device, vertexShaderName, pixelShaderName);
	
	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElements2, 2, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);

	return 0;
}

int TriangleComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) {
	HRESULT res;

	D3D11_BUFFER_DESC dataBufDesc = {};
	dataBufDesc.Usage = D3D11_USAGE_DEFAULT;
	dataBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	dataBufDesc.CPUAccessFlags = 0;
	dataBufDesc.MiscFlags = 0;
	dataBufDesc.StructureByteStride = 0;
	dataBufDesc.ByteWidth = sizeof(XMFLOAT4) * std::size(positions);

	ID3D11Buffer* pb;
	ID3D11Buffer* cb;

	D3D11_SUBRESOURCE_DATA positionsData = {};
	positionsData.pSysMem = positions;
	positionsData.SysMemPitch = 0;
	positionsData.SysMemSlicePitch = 0;
	D3D11_SUBRESOURCE_DATA colorsData = {};
	colorsData.pSysMem = colors;
	colorsData.SysMemPitch = 0;
	colorsData.SysMemSlicePitch = 0;

	res = device->CreateBuffer(&dataBufDesc, &positionsData, &pb); ZCHECK(res);
	res = device->CreateBuffer(&dataBufDesc, &colorsData, &cb); ZCHECK(res);

	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * std::size(verticles);

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = verticles;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	ID3D11Buffer* ib;
	res = device->CreateBuffer(&indexBufDesc, &indexData, &ib); ZCHECK(res);

	ID3D11Buffer* vBuffers[] = { pb, cb };
	UINT strides[] = { 16, 16 };
	UINT offsets[] = { 0, 0 };

	context->IASetInputLayout(layout);
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 2, vBuffers, strides, offsets);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);

}

int* TriangleComponent::getIndexes() {
	return verticles;
}

int TriangleComponent::getIndexesSize() {
	return std::size(verticles);
}

void TriangleComponent::release() {
	vertexShader->Release();
	pixelShader->Release();
}