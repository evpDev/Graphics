#include "CustomMeshComponent.h"

using namespace DirectX;

CustomMeshComponent::CustomMeshComponent()/* : wasSet(false)*/ {}

CustomMeshComponent::CustomMeshComponent(Game* g) : /*wasSet(false),*/ g(g) {
	const char* pathWithObj = "SARS_CoV_2_Vaccine.obj";
	const char* objPath = "";
	mesh = new MeshFilter(pathWithObj, objPath);

	points = (SimpleExtendedVertex*)malloc(sizeof(SimpleExtendedVertex) * getPointsSize());
	for (int i = 0; i < getPointsSize(); i++) {
		points[i] = {
			DirectX::XMFLOAT3(mesh->vertexes[i].x, mesh->vertexes[i].y, mesh->vertexes[i].z),
			DirectX::XMFLOAT2(mesh->textures[i].x, mesh->textures[i].y),
			DirectX::XMFLOAT3(mesh->normales[i].x, mesh->normales[i].y, mesh->normales[i].z)
		};
	}
	meshRenderer = new MeshRenderer(mesh, points);
}

int CustomMeshComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff2, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {

	meshRenderer->initialize(display, device, sizeof(SimpleExtendedVertex), constBuff2, "VSMain", "PSMain");

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	meshRenderer->initLayout(device, inputElements, 3);

	LPCWSTR filename = L"SARS_CoV_2_Vaccine_Red_Diffuse.png";
	g->textureLoader->loadTextureFromFile(filename, texture, texSRV, true, false, 0);

	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT res = device->CreateSamplerState(&sampDesc, &samplerLinear); ZCHECK(res);

	return 0;
}

void CustomMeshComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) {
	meshRenderer->draw(context, device, constBuff, sizeof(SimpleExtendedVertex));
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;D3D11_PRIMITIVE_TOPOLOGY_LINELIST
	context->PSSetShaderResources(0, 1, &texSRV);
	context->PSSetSamplers(0, 1, &samplerLinear);
}

void CustomMeshComponent::update(ID3D11DeviceContext* context, ConstantBuffer* cb) {
	meshRenderer->update(context, cb);
}

int* CustomMeshComponent::getIndexes() {
	return mesh->getIndexes();
}

int CustomMeshComponent::getIndexesSize() {
	return mesh->getIndexesSize();
}

int* CustomMeshComponent::getPoints() {
	return mesh->getPoints();
}

int CustomMeshComponent::getPointsSize() {
	return mesh->getPointsSize();
}

void CustomMeshComponent::release() {
	meshRenderer->vertexShader->Release();
	meshRenderer->pixelShader->Release();
}