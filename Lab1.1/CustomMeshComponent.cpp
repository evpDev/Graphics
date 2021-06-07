#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "CustomMeshComponent.h"

using namespace DirectX;

CustomMeshComponent::CustomMeshComponent() : wasSet(false) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "C:/Users/aaa/Downloads/OBJ/SARS_CoV_2_Vaccine.obj",
		"C:/Users/aaa/Downloads/OBJ", true, true);
	if (ret) {
		std::cout << "Model is loaded" << std::endl;
	}
	pointsSize = attrib.vertices.size()/3;
	points2 = (SimpleVertex*) std::malloc(sizeof(SimpleVertex) * pointsSize);
	for (int i = 0, j = 0; i < attrib.vertices.size(); i += 3, j++) {
		points2[j] = {
			XMFLOAT3(attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2]),
			XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
		};
	}
	if (ret) {
		SimpleVertex tmp = points2[1];
		SimpleVertex tmp2 = points2[2];
		std::cout << "Model is loaded" << std::endl;
	}

	indexesSize = shapes[0].mesh.indices.size();
	indexes = (WORD*)std::malloc(sizeof(int) * indexesSize);
	for (int i = 0; i < indexesSize; i++) {
		indexes[i] = shapes[0].mesh.indices[i].vertex_index;
	}
	if (ret) {
		WORD tmp = indexes[1];
		WORD tmp2 = indexes[2];
		std::cout << "Model is loaded" << std::endl;
	}
}

int CustomMeshComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device) {

	GameComponent::initialize(display, device);

	D3D11_INPUT_ELEMENT_DESC inputElements2[] = {
		D3D11_INPUT_ELEMENT_DESC {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC {"COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElements2, 2, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &this->layout);

	return 0;
}

int CustomMeshComponent::draw(ID3D11DeviceContext* context, Microsoft::WRL::ComPtr<ID3D11Device> device, ID3D11Buffer** constBuff) {
	HRESULT res;

	/*D3D11_BUFFER_DESC bd;*/
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * getPointsSize();
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

	UINT stride = sizeof(SimpleVertex);
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

	context->IASetInputLayout(layout);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);
	context->VSSetConstantBuffers(0, 1, constBuff);

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