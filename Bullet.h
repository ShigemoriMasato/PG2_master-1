#pragma once
#include "Object.h"

enum BulletType {
	kPlayer,
	kEnemy
};

class Bullet : public Object {
public:
	Bullet(BulletType type);
	~Bullet();

	void Move();

	void CollitionChecker(Object obj);

private:

	BulletType type_;

};

