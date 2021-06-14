#define TINYOBJLOADER_IMPLEMENTATION
#include "MeshFilter.h"

MeshFilter::MeshFilter() {}

MeshFilter::MeshFilter(SimpleVertex* points, int pointsSize, WORD* indexes, int indexesSize) : pointsSize(pointsSize), indexesSize(indexesSize), indexes(indexes) {
	vertexes = (DirectX::XMFLOAT3*) malloc(sizeof(DirectX::XMFLOAT3) * pointsSize);
	colors = (DirectX::XMFLOAT4*) malloc(sizeof(DirectX::XMFLOAT4) * pointsSize);

	initPoints(points);
}

MeshFilter::MeshFilter(const char* pathWithObj, const char* objPath) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, pathWithObj, objPath, true, true);
	//if (ret) cout << "Model is loaded" << endl;

	pointsSize = attrib.vertices.size() / 3;
	vertexes = (DirectX::XMFLOAT3*) malloc(sizeof(DirectX::XMFLOAT3) * pointsSize);
	textures = (DirectX::XMFLOAT2*) malloc(sizeof(DirectX::XMFLOAT2) * pointsSize);
	normales = (DirectX::XMFLOAT3*) malloc(sizeof(DirectX::XMFLOAT3) * pointsSize);

	initPointsFromObj(&attrib, &shapes);
}

void MeshFilter::initPoints(SimpleVertex* points) {
	for (int i = 0; i < pointsSize; i++, points++) {
		vertexes[i] = points->Pos;
		colors[i] = points->Color;
	}
}

void MeshFilter::initPointsFromObj(tinyobj::attrib_t* attrib, std::vector<tinyobj::shape_t>* shapes) {
	auto sarsIndeces = (*shapes)[0].mesh.indices;
	indexesSize = sarsIndeces.size();
	indexes = (WORD*)std::malloc(sizeof(int) * indexesSize);
	WORD tmpIndex;
	for (int i = 0; i < indexesSize; i++) {
		indexes[i] = sarsIndeces[i].vertex_index;
		if (i % 3 == 1) {
			tmpIndex = sarsIndeces[i].vertex_index;
		} else if (i % 3 == 2) {
			indexes[i] = tmpIndex;
			indexes[i - 1] = sarsIndeces[i].vertex_index;
		}

		int v = indexes[i];
		int tc = sarsIndeces[i].texcoord_index;
		int n = sarsIndeces[i].normal_index;
		vertexes[v] = DirectX::XMFLOAT3(attrib->vertices[v * 3],   attrib->vertices[v * 3 + 1], attrib->vertices[v * 3 + 2]);
		textures[v] = DirectX::XMFLOAT2(attrib->texcoords[tc * 2], attrib->texcoords[tc * 2 + 1]);
		normales[v] = DirectX::XMFLOAT3(attrib->normals[n * 3],    attrib->normals[n * 3 + 1],  attrib->normals[n * 3 + 2]);
	}
}

int* MeshFilter::getIndexes() {
	return (int*) indexes;
}

int MeshFilter::getIndexesSize() {
	return indexesSize;
}

int* MeshFilter::getPoints() {
	return (int*) vertexes;
}

int MeshFilter::getPointsSize() {
	return pointsSize;
}