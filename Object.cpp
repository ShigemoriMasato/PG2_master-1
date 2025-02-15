#include "Object.h"
#include "Useful.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Useful;
using namespace MatrixCalc;
using MT = MatrixType;

namespace {
	/// <summary>
	/// Shape型の初期化に使用する
	/// </summary>
	Vector2 GetShapePoint(float x, float y, float length) {
		Vector2 buffer = { Normalize(x, length), Normalize(y, length) };
		return buffer;
	}

	/// <summary>
	/// 一番長い正規化した時の長さを返す
	/// </summary>
	float SearchLength(float x, float y, float length) {
		float buffer = (x * x + y * y);
		if (length < buffer) {
			return buffer;
		} else {
			return length;
		}
	}
}

void Object::Initialize(Vector2 size, FillMode fillmode, ObjectType type, std::vector<Vector2> lPos) {

	float buffer = 0;

	switch (type) {
	case ObjectType::kCircle:

		nPos_.push_back({ 0, 0 });

		size_ = size;

		break;

	case ObjectType::kLine:

		nPos_.push_back({ 1.0f, 0.0f });
		nPos_.push_back({ -1.0f, 0.0f });

		size_ = size;

		break;

	case ObjectType::kTriangle:

		nPos_.push_back({ 0, 1 });
		nPos_.push_back({ -1.0f, -1.0f });
		nPos_.push_back({ 1.0f, -1.0f });

		size_ = size;

		break;

	case ObjectType::kQuad:

		nPos_.push_back({ 1.0f, 1.0f });
		nPos_.push_back({ -1.0f, 1.0f });
		nPos_.push_back({ -1.0f, -1.0f });
		nPos_.push_back({ 1.0f, -1.0f });

		size_ = size;

		break;

	case ObjectType::kCostom:

		for (int i = 0; i < lPos.size(); i++) {
			buffer = SearchLength(lPos[i].x, lPos[i].y, buffer);
		}

		for (int i = 0; i < lPos.size(); i++) {
			nPos_.push_back(GetShapePoint(lPos[i].x, lPos[i].y, buffer));
		}

		size_ = size;

		break;
	}

	type_ = type;

	sPos_.resize(nPos_.size());

	fillmode_ = fillmode;
}

Object::Object() : Material() {
	Initialize({ 32, 32 }, kFillModeSolid, ObjectType::kLine, std::vector<Vector2>(0));
}

Object::Object(Vector2 size, FillMode fillmode, ObjectType type, std::vector<Vector2> lPos) : Material() {
	Initialize(size, fillmode, type, lPos);
}

Object::~Object() {}

void Object::Ready(MatrixType type, Camera* camera) {
	
	switch (type) {
	case MT::kSRT:
		matrix_ = MakeScaleMatrix(scale_) * MakeRotateMatrix(theta_) * MakeTranslateMatrix(pos_) * camera->GetMatrix();
		break;
	case MT::kSTR:
		matrix_ = MakeTranslateMatrix(pos_) * MakeScaleMatrix(scale_) * MakeRotateMatrix(theta_) * camera->GetMatrix();
		break;
	case MT::kscSRT:
		matrix_ = MakeScaleMatrix(scale_) * MakeRotateMatrix(theta_) * MakeTranslateMatrix(pos_);
		break;
	case MT::kscSTR:
		matrix_ = MakeTranslateMatrix(pos_) * MakeScaleMatrix(scale_) * MakeRotateMatrix(theta_);
		break;
	}

	for (int i = 0; i < nPos_.size(); i++) {
		sPos_[i] = Vector2(nPos_[i].x * size_.x, nPos_[i].y * size_.y) * matrix_;
	}

	screenMidPos_ = Vector2(0, 0) * matrix_;

	AdjustColor();

}

void Object::Draw() {

	Novice::SetBlendMode(blendMode_);

	switch (type_) {
	case ObjectType::kCircle:

		Novice::DrawEllipse(static_cast<int>(screenMidPos_.x), static_cast<int>(screenMidPos_.y),
			static_cast<int>(size_.x), static_cast<int>(size_.y), theta_,
			color_, fillmode_);

		break;

	case ObjectType::kLine:

		Novice::DrawLine(static_cast<int>(sPos_[0].x), static_cast<int>(sPos_[0].y),
			static_cast<int>(sPos_[1].x), static_cast<int>(sPos_[1].y),
			color_);
		
		break;

	default:

		if (fillmode_ == kFillModeSolid) {
			for (int i = 1; i < sPos_.size(); i++) {

				Novice::DrawTriangle(static_cast<int>(screenMidPos_.x), static_cast<int>(screenMidPos_.y),
					static_cast<int>(sPos_[i - 1].x), static_cast<int>(sPos_[i - 1].y),
					static_cast<int>(sPos_[i].x), static_cast<int>(sPos_[i].y),
					color_, kFillModeSolid);

			}

			Novice::DrawTriangle(static_cast<int>(screenMidPos_.x), static_cast<int>(screenMidPos_.y),
				static_cast<int>(sPos_[sPos_.size() - 1].x), static_cast<int>(sPos_[sPos_.size() - 1].y),
				static_cast<int>(sPos_[0].x), static_cast<int>(sPos_[0].y),
				color_, kFillModeSolid);

		} else {
			for (int i = 1; i < sPos_.size(); i++) {

				Novice::DrawLine(static_cast<int>(sPos_[i - 1].x), static_cast<int>(sPos_[i - 1].y),
					static_cast<int>(sPos_[i].x), static_cast<int>(sPos_[i].y),
					color_);

			}

			Novice::DrawLine(static_cast<int>(sPos_[sPos_.size() - 1].x), static_cast<int>(sPos_[sPos_.size() - 1].y),
				static_cast<int>(sPos_[0].x), static_cast<int>(sPos_[0].y),
				color_);
		}

		break;

	}

}
