#pragma once
#include "Player.h"
#include "Enemy.h"

class PlayScene {
public:

	PlayScene();
	~PlayScene();

	void Update();
	void Draw();

private:

	Player player;
	std::vector<Enemy> enemies;

};
