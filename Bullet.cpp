#include "Bullet.h"

Bullet::Bullet(BulletType type) : Object({ 2, 8 }, kFillModeSolid, ObjectType::kQuad) {
	switch (type) {
	case kPlayer:

		speed_ = 20.0f;

		break;
	case kEnemy:

		speed_ = 5.0f;

		break;
	}

	type_ = type;

}

Bullet::~Bullet() {
}

void Bullet::Move() {
	pos_ += direction_ * speed_;

	if (pos_.x < 0 || pos_.x > 1280 || pos_.y > 720) {
		isActive_ = false;
	}

	Ready(MatrixType::kSRT, gcamera);
}

void Bullet::CollitionChecker(Object obj) {
}
