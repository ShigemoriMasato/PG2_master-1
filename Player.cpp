#include "Player.h"

Player::Player() : Object({ 48, 64 }, kFillModeSolid, ObjectType::kCostom, { {0, 1},{1, -1},{0, -0.4f},{-1, -1} }) {
	pos_ = { 640, 100 };
	speed_ = 5;
	bulletCooltime_ = 0;
}

Player::~Player() {
}

void Player::Move() {

	direction_ = { 0, 0 };

	if (keys[DIK_W]) {
		direction_.y += 1;
	}

	if (keys[DIK_S]) {
		direction_.y -= 1;
	}

	if (keys[DIK_A]) {
		direction_.x -= 1;
	}

	if (keys[DIK_D]) {
		direction_.x += 1;
	}

	if (direction_.x != 0 || direction_.y != 0) {
		direction_ *= 0.71f;
	}

	velocity_ = direction_ * speed_;

	pos_ += velocity_;

	for (auto& bullet : bullets_) {
		bullet.Move();

		if (!bullet.GetIsActive()) {
			bullets_.erase(bullets_.begin());
		}
	}

}

void Player::ShotBullets() {

	if (bulletCooltime_ < 4) {
		bulletCooltime_++;
	} else if (keys[DIK_SPACE]) {

		bullets_.push_back(Bullet(BulletType::kPlayer));
		bullets_[bullets_.size() - 1].SetPos(pos_ + Vector2(0, size_.y / 2) * scale_.y);
		bullets_[bullets_.size() - 1].SetDirection({0, 1});
		bulletCooltime_ = 0;

	}

}

std::vector<Bullet> Player::GetBullets() const {
	return bullets_;
}
