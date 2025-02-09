#pragma once
#include "Object.h"
#include "GameManager.h"
#include "Bullet.h"
#include <vector>

class Player : public Object {
public:

	Player();
	~Player();

	void Move();

	void ShotBullets();

	std::vector<Bullet> GetBullets() const;

private:

	std::vector<Bullet> bullets_;

	int bulletCooltime_;

};

