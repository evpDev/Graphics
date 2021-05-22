#pragma once
//#include "Game.h"

class GameComponent {
	//Game game;
public:
	GameComponent();
	void destroyResources();
	void draw();
	void initialize();
	void reload();
	void update();
};