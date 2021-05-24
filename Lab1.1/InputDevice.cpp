#include "InputDevice.h"

//InputDevice::InputDevice(Game* g) : game(g) {};

//void InputDevice::onKeyDown(int key) {
//	if (key == ((int) Keys::A)) {
//		game->projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, game->display->screenWidth / (FLOAT) game->display->screenHeight, 0.01f, 100.0f);
//	}
//
//	if (key == ((int) Keys::D)) {
//		game->projection = XMMatrixOrthographicLH((float)5, (float)5, 0.01f, 1000.0f);
//	}
//
//	if (key == ((int) Keys::Escape)) PostQuitMessage(0);
//}