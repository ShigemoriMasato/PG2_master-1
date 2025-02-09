#pragma once
#include "Object.h"

enum class EnemyType {
	kNormal,
	kBoss
};
enum EVisuType {
	kframe,
	kcircle
};

class EnemyVisual : public Object {
public:

	EnemyVisual() {};

	EnemyVisual(EVisuType type);

	void Update();

private:

	EnemyVisual(Vector2 size, FillMode fillmode, ObjectType type = ObjectType::kQuad, std::vector<Vector2> lPos = std::vector<Vector2>(0));

	float t_;
	
	EVisuType type_;

};

class Enemy : public Object {
public:
	Enemy(EnemyType type = EnemyType::kNormal);
	~Enemy();
	void Move();

	void Draw() override;

private:
	
	std::vector<EnemyVisual> visual_;

	EnemyType type_;

};
