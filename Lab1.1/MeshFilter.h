#pragma once
#include "tiny_obj_loader.h"
#include <directxmath.h>
#include <d3d11.h>

struct SimpleVertex {
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};

struct SimpleExtendedVertex {
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT2 Tex;
	DirectX::XMFLOAT3 Normal;
};

class MeshFilter {
public:
	//SimpleExtendedVertex* points;
	DirectX::XMFLOAT3* vertexes;
	DirectX::XMFLOAT2* textures;
	DirectX::XMFLOAT3* normales;
	DirectX::XMFLOAT4* colors;
	int pointsSize;
	WORD* indexes;
	int indexesSize;

	MeshFilter();
	MeshFilter(SimpleVertex* points, int pointsSize, WORD* indexes, int indexesSize);
	MeshFilter(const char* pathWithObj, const char* objPath);
	void initPointsFromObj(tinyobj::attrib_t* attrib, std::vector<tinyobj::shape_t>* shapes);
	void initPoints(SimpleVertex* points);
	int* getIndexes();
	int getIndexesSize();
	int* getPoints();
	int getPointsSize();
};