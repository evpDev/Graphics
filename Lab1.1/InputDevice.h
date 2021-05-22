#pragma once
//#include "Game.h"

class InputDevice {
	//Game game;
	int keys;
	int mouseMove;
	int mouseOffset;
	int mousePosition;
	int mouseWheelDistance;//?? distance ??
public:
	void addPressedKey();
	void isKeyDown();
	void onKeyDown();
	void onMouseMove();
	void removePressedKeys();
};