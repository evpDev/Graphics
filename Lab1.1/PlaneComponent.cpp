#include "PlaneComponent.h"

using namespace DirectX;

PlaneComponent::PlaneComponent() : wasSet(false) {
	int planeLinesX = 11;
	int pointsSize = (planeLinesX - 1) * 4;
	points = (SimpleVertex*) malloc(sizeof(SimpleVertex) * pointsSize);
	for (int i = -5, j = 0; i <= 5; i++, j++) {
		points[j] = {
			XMFLOAT3(i,  0.0f, -5.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
		};
		points[j + planeLinesX] = {
			XMFLOAT3(i,  0.0f, 5.0f),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
		};
	}
	for (int i = -4, j = 2 * planeLinesX; i <= 4; i++, j++) {
		points[j] = {
			XMFLOAT3(-5.0f,  0.0f, i),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
		};
		points[j + planeLinesX - 2] = {
			XMFLOAT3(5.0f,  0.0f, i),
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
		};
	}

	int indexesSize = planeLinesX * 4;
	indexes = (WORD*) malloc(sizeof(WORD) * indexesSize);
	for (int i = 0; i < planeLinesX; i++) {
		indexes[i * 2] = i;
		indexes[i * 2 + 1] = i + planeLinesX;
	}
	for (int i = planeLinesX; i < (planeLinesX - 1) * 2; i++) {
		indexes[i * 2] = planeLinesX + i;
		indexes[i * 2 + 1] = indexes[i * 2] + planeLinesX - 2;
	}
	indexes[(planeLinesX - 1) * 4] = 0;
	indexes[(planeLinesX - 1) * 4 + 1] = planeLinesX - 1;
	indexes[(planeLinesX - 1) * 4 + 2] = planeLinesX;
	indexes[(planeLinesX - 1) * 4 + 3] = planeLinesX * 2 - 1;

	mesh = new MeshFilter(points, pointsSize, indexes, indexesSize);
}

int PlaneComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {

	GameComponent::initialize(display, device, "VSMainColor", "PSMainColor");

	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElements2, 2, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);

	return 0;
}

int PlaneComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) {
	HRESULT res;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * getPointsSize();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = points;

	if (!wasSet) {
		res = device->CreateBuffer(&bd, &InitData, &vertexBuff); ZCHECK(res);
	}

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * getIndexesSize();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = getIndexes();

	if (!wasSet) {
		res = device->CreateBuffer(&bd, &InitData, &indexBuff); ZCHECK(res);
	}

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &offset);
	context->IASetIndexBuffer(indexBuff, DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	/*-------------------------Constant Buffer------------------------------*/
	constantBufDesc = {};
	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = 0;
	constantBufDesc.MiscFlags = 0;
	constantBufDesc.StructureByteStride = 0;
	constantBufDesc.ByteWidth = sizeof(ConstantBuffer);

	if (!wasSet) {
		res = device->CreateBuffer(&constantBufDesc, NULL, constBuff); ZCHECK(res);
	}
	/*-------------------------Constant Buffer------------------------------*/

	context->IASetInputLayout(layout);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);
	context->VSSetConstantBuffers(0, 1, constBuff);

	wasSet = true;
}

int* PlaneComponent::getIndexes() {
	return mesh->getIndexes();
}

int PlaneComponent::getIndexesSize() {
	return mesh->getIndexesSize();
}

int* PlaneComponent::getPoints() {
	return mesh->getPoints();
}

int PlaneComponent::getPointsSize() {
	return mesh->getPointsSize();
}