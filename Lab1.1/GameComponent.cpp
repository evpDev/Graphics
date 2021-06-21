#include "GameComponent.h"

Transform::Transform() {
	position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale	 = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
}

GameComponent::GameComponent() {}

int GameComponent::initialize(DisplayWin32* display, Microsoft::WRL::ComPtr<ID3D11Device> device, LPCSTR vertexShaderName, LPCSTR pixelShaderName) {
	return 0;
}

int* GameComponent::getPoints() {
	return nullptr;
}

int GameComponent::getPointsSize() {
	return 0;
}

void GameComponent::release() {
}