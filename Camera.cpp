#include "Camera.h"
#include "Object.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace MatrixCalc;

Camera::Camera() {

	pos_ = { 0.0f, 0.0f };
	scale_ = { 1.0f, 1.0f };
	theta_ = 0.0f;
	isShake_ = false;
	timer = 0;
	shakePos_ = { 0, 0 };
	Update();

}

Matrix3x3 Camera::MakeOrthographicProjectionMatirx(Vector2 LT, Vector2 RB) {
	//正射影行列を作成
	Matrix3x3 ans = {
		{
			{2.0f / (RB.x - LT.x), 0, 0},
			{0, 2.0f / (LT.y - RB.y), 0},
			{(LT.x + RB.x) / (LT.x - RB.x), (LT.y + RB.y) / (RB.x - LT.y), 1}
		}
	};

	return ans;
}

Matrix3x3 Camera::MakeViewportMatrix(Vector2 winSize, Vector2 localLT) {
	//ビューポート変換用行列を作成
	Matrix3x3 ans = {
		{
			{winSize.x / 2, 0, 0},
			{0, -winSize.y / 2, 0},
			{localLT.x + winSize.x / 2, localLT.y + winSize.y / 2, 1}
		}
	};

	return ans;
}

void Camera::Shake() {
	if (isShake_) {
		timer++;

		shakePos_ = { float(rand() % 20 - 10), float(rand() % 20 - 10) };

		if (timer > 10) {
			timer = 0;
			isShake_ = false;
		}
	} else {
		shakePos_ = { 0, 0 };
	}
}

Matrix3x3 Camera::MakeCameraMatrix() const {

	return MakeScaleMatrix(scale_) * MakeRotateMatrix(theta_) * Inverse(MakeTranslateMatrix(pos_ + shakePos_));

}

void Camera::Update() {
	//各々のパラメータをVector2に代入
	Vector2 LT = { -WinSizeWidth / 2, WinSizeHeight / 2 };
	Vector2 RB = { WinSizeWidth / 2, -WinSizeHeight / 2 };

	Shake();

	//カメラのマトリックスを作成
	matrix_ = MakeCameraMatrix() * MakeOrthographicProjectionMatirx(LT, RB) * MakeViewportMatrix({ WinSizeWidth, WinSizeHeight }, LT);

}

Matrix3x3 Camera::GetMatrix() const {
	return this->matrix_;
}
