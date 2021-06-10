#pragma once
#include "wincodec.h"
#include "Game.h"
#include "ProjectUtils.h"

class Game;

class TextureLoader {
	IWICImagingFactory2* factory;
	Game* game;

public:
	TextureLoader(Game* game);
	~TextureLoader();

	HRESULT loadTextureFromFile(LPCWSTR fileName, ID3D11Texture2D*& texture, ID3D11ShaderResourceView*& textureView, bool generateMips, bool useSrgb, UINT frameIndex);
};