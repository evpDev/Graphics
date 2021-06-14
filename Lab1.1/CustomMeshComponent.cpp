#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"
#include "CustomMeshComponent.h"

using namespace DirectX;

CustomMeshComponent::CustomMeshComponent() : wasSet(false) {}

CustomMeshComponent::CustomMeshComponent(Game* g) : wasSet(false), g(g) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;
	const char* pathWithObj = "SARS_CoV_2_Vaccine.obj";
	const char* objPath = "";
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, pathWithObj, objPath, true, true);
	if (ret) std::cout << "Model is loaded" << std::endl;

	pointsSize = attrib.vertices.size()/3;
	points2 = (SimpleExtendedVertex*) std::malloc(sizeof(SimpleExtendedVertex) * pointsSize);

	initPoints(&attrib, &shapes);
}

void CustomMeshComponent::initPoints(tinyobj::attrib_t* attrib, std::vector<tinyobj::shape_t>* shapes) {
	auto sarsIndeces = (*shapes)[0].mesh.indices;
	indexesSize = sarsIndeces.size();
	indexes = (WORD*)std::malloc(sizeof(int) * indexesSize);
	WORD tmpIndex;
	for (int i = 0; i < indexesSize; i++) {
		indexes[i] = sarsIndeces[i].vertex_index;
		if (i % 3 == 1) {
			tmpIndex = sarsIndeces[i].vertex_index;
		}
		else if (i % 3 == 2) {
			indexes[i] = tmpIndex;
			indexes[i - 1] = sarsIndeces[i].vertex_index;
		}
		int v = indexes[i];
		int tc = sarsIndeces[i].texcoord_index;
		int n = sarsIndeces[i].normal_index;
		points2[v] = {
			XMFLOAT3(attrib->vertices[v * 3], attrib->vertices[v * 3 + 1], attrib->vertices[v * 3 + 2]),
			XMFLOAT2(attrib->texcoords[tc * 2], attrib->texcoords[tc * 2 + 1]),
			XMFLOAT3(attrib->normals[n * 3],   attrib->normals[n * 3 + 1],  attrib->normals[n * 3 + 2])
		};
	}
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

	//D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = getPoints();

	//ID3D11Buffer* vertexBuff;
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

	UINT stride = sizeof(SimpleExtendedVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &offset);
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
	return (int*)indexes;
}

int CustomMeshComponent::getIndexesSize() {
	//return std::size(indexes);
	return indexesSize;
}

int* CustomMeshComponent::getPoints() {
	return (int*)points2;
}

int CustomMeshComponent::getPointsSize() {
	//return std::size(points);
	return pointsSize;
}