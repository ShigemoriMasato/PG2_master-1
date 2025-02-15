#pragma once

struct Matrix3x3 final {
	float m[3][3];

	Matrix3x3 operator*(const Matrix3x3& other) const;
	Matrix3x3 operator*=(const Matrix3x3& other);
};


struct Vector2 final {
	float x;
	float y;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;
	Vector2 operator*(const Matrix3x3& matrix) const;

	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*=(float scalar);
	Vector2 operator/=(float scalar);
	Vector2 operator*=(const Matrix3x3& matrix);
};

namespace MatrixCalc {
	/// <summary>
	/// T行列を作成する
	/// </summary>
	Matrix3x3 MakeTranslateMatrix(Vector2 pos);

	/// <summary>
	/// S行列を作成する
	/// </summary>
	Matrix3x3 MakeScaleMatrix(Vector2 scale);

	/// <summary>
	/// R行列を作成する
	/// </summary>
	Matrix3x3 MakeRotateMatrix(float theta);

	/// <summary>
	/// 逆行列を作成する
	/// </summary>
	Matrix3x3 Inverse(const Matrix3x3& matrix);
}
