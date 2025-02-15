#include "Material.h"
#include "Object.h"

#include <math.h>
#include <cmath>

Material::Material() {

	/**********************座標関係****************************/
	this->size_ = { 0 };
	this->pos_ = { 0 };
	this->expos_ = { 0, 0 };
	this->scale_ = { 1.0f, 1.0f };
	this->theta_ = 0.0f;
	this->speed_ = 0;
	this->velocity_ = { 0 };
	this->direction_ = { 0 };

	/***********************色関係*****************************/
	this->alpha_ = 255;
	this->blue_ = 255;
	this->green_ = 255;
	this->red_ = 255;
	this->color_ = 0xffffffff;
	this->bright_ = 255;
	this->blendMode_ = kBlendModeNormal;

	/*************************flug関係********************************/
	this->isActive_ = true;
}

Material::~Material() {
}

void Material::AdjustColor() {//明るさの割合を求める
	float ratio = float(this->bright_) / 255;		//オブジェクト固有の明るさ

	if (isBlackout_) {
		ratio *= float(gbright) / 255;				//ワールド全体の明るさ
	}

	//カラーに当てはめる
	this->color_ = (int(roundf(this->red_ * ratio)) << 24) + (int(roundf(this->green_ * ratio)) << 16) + (int(roundf(this->blue_ * ratio)) << 8) + (this->alpha_);
}

//================================
//	アクセサーメソッド
//================================

Vector2 Material::GetPos() const {
	return this->pos_;
}

void Material::SetTheta(float theta) {
	this->theta_ = theta;
}

void Material::SetPos(Vector2 pos) {
	this->pos_ = pos;
}

void Material::SetDirection(Vector2 direction) {
	this->direction_ = direction;
}

void Material::SetSpeed(float speed) {
	this->speed_ = speed;
}

void Material::SetColor(unsigned int color) {
	color_ = color;

	this->alpha_ = color & 0xff;
	color >>= 8;

	this->blue_ = color & 0xff;
	color >>= 8;

	this->green_ = color & 0xff;
	color >>= 8;

	this->red_ = color;
}

void Material::SetBright(int bright) {
	this->bright_ = bright;
}

void Material::SetIsBlackOut(bool isBlackout) {
	this->isBlackout_ = isBlackout;
}

void Material::SetIsActive(bool isActive) {
	this->isActive_ = isActive;
}

void Material::SetExPos(Vector2 exPos) {
	this->expos_ = exPos;
}

void Material::SetScale(Vector2 scale) {
	this->scale_ = scale;
}

Vector2 Material::GetCorner(int type) const {

	Vector2 ans = pos_;

	switch (type) {
	case 0:
		ans += Vector2(-size_.x * scale_.x / 2, size_.y * scale_.y / 2);
		break;

	case 1:
		ans += Vector2(size_.x * scale_.x / 2, size_.y * scale_.y / 2);;
		break;

	case 2:
		ans += Vector2(-size_.x * scale_.x / 2, -size_.y * scale_.y / 2);;
		break;

	case 3:
		ans += Vector2(size_.x * scale_.x / 2, -size_.y * scale_.y / 2);;
		break;
	}

	return ans;

}

unsigned int Material::GetColor() {
	AdjustColor();
	return this->color_;
}

Vector2 Material::GetSize() const {
	return this->size_;
}

Vector2 Material::GetScale() const {
	return this->scale_;
}

float Material::GetTheta() const {
	return this->theta_;
}

bool Material::GetIsActive() const {
	return this->isActive_;
}
