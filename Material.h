#pragma once
#include "Vector.h"
#include <Novice.h>

class Material {
public:

	Material();
	~Material();

	void AdjustColor();

	/// <summary>
	/// LT, RT, LB, RBを呼び出す(matrixを使用するため、当たり判定の前にReadyを唱えるべし)
	/// </summary>
	/// <param name="type">上の順番で0~3で呼び出す</param>
	/// <returns>指定された角　エラー時はpos</returns>
	Vector2 GetCorner(int type) const;

	Vector2 GetPos() const;
	unsigned int GetColor();
	Vector2 GetSize() const;
	Vector2 GetScale() const;
	float GetTheta() const;
	bool GetIsActive() const;

	void SetTheta(float theta);
	void SetPos(Vector2 pos);
	void SetDirection(Vector2 direction);
	void SetSpeed(float speed);
	void SetColor(unsigned int color);
	void SetBright(int bright);
	void SetIsBlackOut(bool isBlackout);
	void SetIsActive(bool isActive);
	void SetScale(Vector2 scale);
	void SetExPos(Vector2 exPos);

protected:


	//座標系
	Vector2 size_;
	Vector2 pos_;			//ワールド座標系のプレイヤーの中心
	Vector2 expos_;			//微調整用のポジション()
	Vector2 scale_;			//プレイヤーの大きさの倍率
	Vector2 rotatePos_;		//kSTR行列の中心
	Vector2 velocity_;		//速度
	Vector2 direction_;		//向いている方向
	float speed_;			//速さ
	float theta_;			//回転角度(radian)
	Matrix3x3 matrix_;		//あらゆるパラメータをもとに作成する行列

	//色関係
	int red_;				//赤(0 ~ 255)
	int green_;				//緑(0 ~ 255)
	int blue_;				//青(0 ~ 255)
	int alpha_;				//透明度(0 ~ 255)
	int bright_;			//明るさ(0 ~ 255)
	unsigned int color_;	//計算後の色

	//フラグ系
	bool isActive_;			//有効かどうか
	bool isBlackout_;		//暗転させるか

	BlendMode blendMode_ = kBlendModeNormal;	//ブレンドモード

};

