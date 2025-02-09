#include "Enemy.h"
#include "Collition.h"
#define _USE_MATH_DEFINES
#include <math.h>

Enemy::Enemy(EnemyType type) {

	EnemyVisual visual{};
	float buffer;

	switch (type) {
	case EnemyType::kNormal:

		buffer = float(rand() % 3141592) / 1000.0f;

		visual = EnemyVisual(kframe);
		visual.SetTheta(buffer);
		visual.SetColor(0x803010ff);
		visual_.push_back(visual);
		visual = EnemyVisual(kframe);
		visual.SetTheta(buffer + float(rand() % 3141592) / 1000.0f);
		visual.SetColor(0x202020ff);
		visual_.push_back(visual);
		visual = EnemyVisual(kcircle);
		visual.SetColor(0x000000ff);
		visual_.push_back(visual);

		direction_ = { 1, 0 };

		buffer = sqrtf(32.0f * 32.0f + 32.0f * 32.0f);
		size_ = { buffer, buffer };

		speed_ = 3.0f;

		break;

	case EnemyType::kBoss:
		
		break;
	}

	type_ = type;

}

Enemy::~Enemy() {
}

void Enemy::Move() {
	pos_ += direction_ * speed_;

	if (pos_.x < 0 || pos_.x > 1280) {
		direction_.x *= -1;
	}

	if (pos_.y < 0 || pos_.y > 720) {
		isActive_ = false;
	}

	Ready(MatrixType::kSRT, gcamera);

	for (auto& visual : visual_) {
		visual.SetPos(pos_);
		visual.SetScale(scale_);
		visual.Update();
	}
}

void Enemy::CollitionChecker(std::vector<Bullet> bullet) {
	for (auto& b : bullet) {
		if (Collition::CtC(this, &b)) {
			isActive_ = false;
			b.SetIsActive(false);
		}
	}
}

void Enemy::Draw() {
	for (auto& visual : visual_) {
		visual.Draw();
	}
}

EnemyVisual::EnemyVisual(EVisuType type) {
	switch (type) {
	case EVisuType::kframe:
		*this = EnemyVisual({ 32, 32 }, kFillModeWireFrame, ObjectType::kQuad);
		break;
	case EVisuType::kcircle:
		*this = EnemyVisual({ 12, 12 }, kFillModeSolid, ObjectType::kCircle);
		break;
	}

	type_ = type;
	t_ = 0.0f;
}

EnemyVisual::EnemyVisual(Vector2 size, FillMode fillmode, ObjectType type, std::vector<Vector2> lPos) : Object(size, fillmode, type, lPos) {
	type_ = EVisuType::kframe;
	t_ = 0.0f;
}

void EnemyVisual::Update() {

	switch (type_) {
	case kframe:

		theta_ += 0.05f;

		break;

	case kcircle:

		t_ += 0.05f;

		scale_ = { 1.0f + cosf(t_) * 0.4f, 1.0f };

		size_ = Vector2(12 * scale_.x, 12 * scale_.y);

		theta_ += 0.04123f;

		break;
	}

	Ready(MatrixType::kSRT, gcamera);
}
