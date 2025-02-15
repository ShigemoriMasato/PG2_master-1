#include "Vector.h"
#include <math.h>

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const {
	Matrix3x3 result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			result.m[i][j] = this->m[i][0] * other.m[0][j] + this->m[i][1] * other.m[1][j] + this->m[i][2] * other.m[2][j];

		}
	}

	return result;
}

Matrix3x3 Matrix3x3::operator*=(const Matrix3x3& other) {
	Matrix3x3 result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			result.m[i][j] = this->m[i][0] * other.m[0][j] + this->m[i][1] * other.m[1][j] + this->m[i][2] * other.m[2][j];

		}
	}

	*this = result;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const {
	return Vector2{ x + other.x, y + other.y };
}

Vector2 Vector2::operator-(const Vector2& other) const {
	return Vector2{ x - other.x, y - other.y };
}

Vector2 Vector2::operator*(float scalar) const {
	return Vector2{ x * scalar, y * scalar };
}

Vector2 Vector2::operator/(float scalar) const {
	return Vector2{ x / scalar, y / scalar };
}

Vector2 Vector2::operator*(const Matrix3x3& matrix) const {
	return Vector2{
		x * matrix.m[0][0] + y * matrix.m[1][0] + matrix.m[2][0],
		x * matrix.m[0][1] + y * matrix.m[1][1] + matrix.m[2][1]
	};
}


Vector2 Vector2::operator+=(const Vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 Vector2::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2 Vector2::operator*=(const Matrix3x3& matrix) {
	float tempX = x;
	x = x * matrix.m[0][0] + y * matrix.m[1][0] + matrix.m[2][0];
	y = tempX * matrix.m[0][1] + y * matrix.m[1][1] + matrix.m[2][1];
	return *this;
}

Matrix3x3 MatrixCalc::MakeTranslateMatrix(Vector2 pos) {
	return Matrix3x3{
		{
			{1, 0, 0},
			{0, 1, 0},
			{pos.x, pos.y, 1}
		}
	};
}

Matrix3x3 MatrixCalc::MakeScaleMatrix(Vector2 scale) {
	return Matrix3x3{
		{
			{scale.x, 0, 0},
			{0, scale.y, 0},
			{0, 0, 1}
		}
	};
}

Matrix3x3 MatrixCalc::MakeRotateMatrix(float theta) {
	return Matrix3x3{
		{
			{cosf(theta), sinf(theta), 0},
			{-sinf(theta), cosf(theta), 0},
			{0, 0, 1}
		}
	};
}

Matrix3x3 MatrixCalc::Inverse(const Matrix3x3& matrix) {
	float det = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];
	if (det == 0) {
		return Matrix3x3{
			{
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0}
			}
		};
	}
	float invDet = 1.0f / det;
	return Matrix3x3{
		{
			{matrix.m[1][1] * invDet, -matrix.m[0][1] * invDet, 0},
			{-matrix.m[1][0] * invDet, matrix.m[0][0] * invDet, 0},
			{-(matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * invDet, (matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) * invDet, 1}
		}
	};
}
