#include "PlaneComponent.h"

using namespace DirectX;

PlaneComponent::PlaneComponent() :
	points{
		{ XMFLOAT3(-5.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-4.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-3.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-2.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 0.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 1.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 2.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 3.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 4.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f, -5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

		{ XMFLOAT3(-5.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-4.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-3.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-2.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 0.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 1.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 2.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 3.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 4.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f,  5.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

		{ XMFLOAT3(-5.0f,  0.0f, -4.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-5.0f,  0.0f, -3.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-5.0f,  0.0f, -2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-5.0f,  0.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-5.0f,  0.0f,  0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-5.0f,  0.0f,  1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-5.0f,  0.0f,  2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-5.0f,  0.0f,  3.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-5.0f,  0.0f,  4.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },

		{ XMFLOAT3( 5.0f,  0.0f, -4.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f, -3.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f, -2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f,  0.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f,  1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f,  2.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f,  3.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3( 5.0f,  0.0f,  4.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
},
	indexes{
		0,11, 1,12, 2,13, 3,14, 4,15, 5,16, 6,17, 7,18, 8,19, 9,20, 10,21,
		0,10, 22,31, 23,32, 24,33, 25,34, 26,35, 27,36, 28,37, 29,38, 30,39, 11,21,
	}, 
	wasSet(false) {
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

	/*D3D11_BUFFER_DESC bd;*/
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * getPointsSize();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	/*D3D11_SUBRESOURCE_DATA InitData;*/
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = getPoints();

	/*ID3D11Buffer* vertexBuff;*/
	if (!wasSet) {
		res = device->CreateBuffer(&bd, &InitData, &vertexBuff); ZCHECK(res);
	}

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * getIndexesSize();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = getIndexes();

	/*ID3D11Buffer* indexBuff;*/
	if (!wasSet) {
		res = device->CreateBuffer(&bd, &InitData, &indexBuff); ZCHECK(res);
	}

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &offset);
	context->IASetIndexBuffer(indexBuff, DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	/*-------------------------Constant Buffer------------------------------*/
	//D3D11_BUFFER_DESC 
		constantBufDesc = {};
	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = 0;
	constantBufDesc.MiscFlags = 0;
	constantBufDesc.StructureByteStride = 0;
	constantBufDesc.ByteWidth = sizeof(ConstantBuffer);

	//ID3D11Buffer* constBuff;
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
	return (int*)indexes;
}

int PlaneComponent::getIndexesSize() {
	return std::size(indexes);
}

int* PlaneComponent::getPoints() {
	return (int*)points;
}

int PlaneComponent::getPointsSize() {
	return std::size(points);
}