#include "CustomMeshComponent.h"

using namespace DirectX;

CustomMeshComponent::CustomMeshComponent() : wasSet(false) {}

CustomMeshComponent::CustomMeshComponent(Game* g) : wasSet(false), g(g) {
	const char* pathWithObj = "SARS_CoV_2_Vaccine.obj";
	const char* objPath = "";
	mesh = new MeshFilter(pathWithObj, objPath);
}

int CustomMeshComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {

	GameComponent::initialize(display, device, "VSMain", "PSMain");

	/*D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElements2, 2, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);*/
	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElements, 3, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);

	/*ID3D11Texture2D* texture = (ID3D11Texture2D*)std::malloc(sizeof(ID3D11Texture2D));
	ID3D11ShaderResourceView* texSRV = (ID3D11ShaderResourceView*)std::malloc(sizeof(ID3D11ShaderResourceView));*/
	LPCWSTR filename = L"SARS_CoV_2_Vaccine_Red_Diffuse.png";
	//LPCWSTR filename = L"C:\\Users\\aaa\\Downloads\\OBJ\\Textures\\PalletPlywood_Diffuse.png";
	//LPCWSTR filename = L"C:\\Users\\aaa\\Downloads\\OBJ\\Textures\\SARS_CoV_2_Vaccine_Blue_Diffuse.png";
	//LPCWSTR filename = L"C:\\Users\\aaa\\Downloads\\Fitness_Equipment_Collection_5_obj\\Sport-Water-Bottle-Red-obj\\sport_water_bottle_Diffuse.png";
	//LPCWSTR filename = L"C:\\Users\\aaa\\Downloads\\3634_open3dmodel\\3634_open3dmodel\\Apple\\Maps\\skin.tif";
	g->textureLoader->loadTextureFromFile(filename, texture, texSRV, true, false, 0);

	return 0;
}

int CustomMeshComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) {
	HRESULT res;

	/*D3D11_BUFFER_DESC bd;*/
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleExtendedVertex) * getPointsSize();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	/*ZeroMemory(&bd3, sizeof(bd3));
	bd3.Usage = D3D11_USAGE_DEFAULT;
	bd3.ByteWidth = sizeof(DirectX::XMFLOAT3) * getPointsSize();
	bd3.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd3.CPUAccessFlags = 0;

	ZeroMemory(&bd2, sizeof(bd2));
	bd2.Usage = D3D11_USAGE_DEFAULT;
	bd2.ByteWidth = sizeof(DirectX::XMFLOAT2) * getPointsSize();
	bd2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd2.CPUAccessFlags = 0;*/

	points = (SimpleExtendedVertex*) malloc(sizeof(SimpleExtendedVertex) * getPointsSize());
	for (int i = 0; i < getPointsSize(); i++) {
		points[i] = {
			DirectX::XMFLOAT3(mesh->vertexes[i].x, mesh->vertexes[i].y, mesh->vertexes[i].z),
			DirectX::XMFLOAT2(mesh->textures[i].x, mesh->textures[i].y),
			DirectX::XMFLOAT3(mesh->normales[i].x, mesh->normales[i].y, mesh->normales[i].z)
		};
	}

	//D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = points;

	/*vertexesData = {};
	vertexesData.pSysMem = mesh->vertexes;
	vertexesData.SysMemPitch = 0;
	vertexesData.SysMemSlicePitch = 0;
	texturesData = {};
	texturesData.pSysMem = mesh->textures;
	texturesData.SysMemPitch = 0;
	texturesData.SysMemSlicePitch = 0;

	normalesData = {};
	normalesData.pSysMem = mesh->normales;
	normalesData.SysMemPitch = 0;
	normalesData.SysMemSlicePitch = 0;*/

	//ID3D11Buffer* vertexBuff;
	if (!wasSet) {
		/*res = device->CreateBuffer(&bd3, &vertexesData, &vb); ZCHECK(res);
		res = device->CreateBuffer(&bd2, &texturesData, &tb); ZCHECK(res);
		res = device->CreateBuffer(&bd3, &normalesData, &nb); ZCHECK(res);*/
		res = device->CreateBuffer(&bd, &InitData, &vertexBuff); ZCHECK(res);
	}

	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * getIndexesSize();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = getIndexes();

	/*ID3D11Buffer* indexBuff;*/
	if (!wasSet) {
		res = device->CreateBuffer(&bd, &InitData, &indexBuff); ZCHECK(res);
	}

	UINT stride = sizeof(SimpleExtendedVertex);
	UINT offset = 0;
	/*ID3D11Buffer* vBuffers[] = { vb, tb, nb };
	UINT strides[] = { 12, 8, 12 };
	UINT offsets[] = { 0, 0, 0 };*/
	context->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &offset);
	//context->IASetVertexBuffers(0, 3, vBuffers, strides, offsets);
	context->IASetIndexBuffer(indexBuff, DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;D3D11_PRIMITIVE_TOPOLOGY_LINELIST

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

	//D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	if (!wasSet) {
		res = device->CreateSamplerState(&sampDesc, &samplerLinear); ZCHECK(res);
	}

	context->IASetInputLayout(layout);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);
	context->VSSetConstantBuffers(0, 1, constBuff);
	context->PSSetShaderResources(0, 1, &texSRV);
	context->PSSetSamplers(0, 1, &samplerLinear);

	/*ID3D11ShaderResourceView* textureRV = NULL;
	ID3D11SamplerState* samplerLinear = NULL;

	res = D3DX11CreateShaderResourceViewFromFile(device, L"seafloor.dds", NULL, NULL, &textureRV, NULL); ZCHECK(res);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	res = device->CreateSamplerState(&sampDesc, &samplerLinear); ZCHECK(res);*/

	wasSet = true;
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