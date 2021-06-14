#include "InputDevice.h"

using namespace DirectX;

InputDevice::InputDevice(Game* g) : game(g) {};

void InputDevice::onKeyDown(int key) {
	if (key == (int)Keys::R) {
		if (game->isPerspectiveView) {
			game->isPerspectiveView = false;
			game->projection = XMMatrixOrthographicLH(game->orthoScale, game->orthoScale, 0.01f, 1000.0f);
		}
		else {
			game->isPerspectiveView = true;
			game->projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, game->display->screenWidth / (FLOAT)game->display->screenHeight, 0.01f, 100.0f);
		}
	}

	if (key == (int)Keys::A) {
		game->world = game->world * XMMatrixRotationY(0.04);
	}

	if (key == (int)Keys::D) {
		game->world = game->world * XMMatrixRotationY(-0.04);
	}

	if (key == (int)Keys::Q) {
		game->world = game->world * XMMatrixTranslation(0, -1, 0) * XMMatrixRotationZ(0.04) * XMMatrixTranslation(0, 1, 0);
	}

	if (key == (int)Keys::E) {
		game->world = game->world * XMMatrixTranslation(0, -1, 0) * XMMatrixRotationZ(-0.04) * XMMatrixTranslation(0, 1, 0);
	}

	if (key == (int)Keys::W) {
		game->world = game->world * XMMatrixTranslation(0, -1, 0) * XMMatrixRotationX(0.04) * XMMatrixTranslation(0, 1, 0);
	}

	if (key == (int)Keys::S) {
		game->world = game->world * XMMatrixTranslation(0, -1, 0) * XMMatrixRotationX(-0.04) * XMMatrixTranslation(0, 1, 0);
	}
}

void InputDevice::onMouseWheel(int key) {
	if (key == 4287102976 || key == -7864320) {
		if (game->isPerspectiveView) {
			game->perspectScale += 0.5;
			XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, game->perspectScale, 0.0f);
			XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			game->view = XMMatrixLookAtLH(Eye, At, Up);
			game->projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, game->display->screenWidth / (FLOAT)game->display->screenHeight, 0.01f, 100.0f);
		}
		else {
			game->orthoScale += 0.2;
			game->projection = XMMatrixOrthographicLH(game->orthoScale, game->orthoScale, 0.01f, 1000.0f);
		}
	}

	if (key == 7864320) {
		if (game->isPerspectiveView) {
			game->perspectScale -= 0.5;
			XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, game->perspectScale, 0.0f);
			XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			game->view = XMMatrixLookAtLH(Eye, At, Up);
			game->projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, game->display->screenWidth / (FLOAT)game->display->screenHeight, 0.01f, 100.0f);
		}
		else {
			game->orthoScale -= 0.2;
			game->projection = XMMatrixOrthographicLH(game->orthoScale, game->orthoScale, 0.01f, 1000.0f);
		}
	}
}