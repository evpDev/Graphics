#pragma once
//#include "Game.h"

class InputDevice {
	//Game* game;
	int keys;
	int mouseMove;
	int mouseOffset;
	int mousePosition;
	int mouseWheelDelta;
public:
	InputDevice();
	//InputDevice(Game* g);
	void addPressedKey();
	void isKeyDown();
	void onKeyDown(int key);
	void onMouseMove();
	void removePressedKeys();
};