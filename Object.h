#pragma once
#include "Material.h"
#include "Camera.h"
#include "GameManager.h"
#include <vector>

extern Camera* gcamera;

extern char keys[256];			//現在のキー入力
extern char preKeys[256];		//1フレーム前のキー入力

extern int gbright;				//ワールド全体の明るさ
extern BrightSetting bSet;		//明るさ設定

enum class ObjectType {
	kCircle,
	kLine,
	kTriangle,
	kQuad,
	kCostom
};

enum class MatrixType {
	kSRT,
	kSTR,
	kscSRT,
	kscSTR
};

class Object : public Material {
public:

	Object();

	/// <summary>
	/// ローカル座標構築用
	/// </summary>
	/// <param name="lPos">カスタムのときのみ入力。内部で正規化</param>
	Object(Vector2 size, FillMode fillmode, ObjectType type = ObjectType::kQuad, std::vector<Vector2> lPos = std::vector<Vector2>(0));
	~Object();

	/// <summary>
	/// アフィン行列作成
	/// </summary>
	void Ready(MatrixType type, Camera* camera = new Camera());

	/// <summary>
	/// 描画用関数
	/// </summary>
	virtual void Draw();

private:

	void Initialize(Vector2 size, FillMode fillmode, ObjectType type, std::vector<Vector2> lPos);

	std::vector<Vector2> nPos_;			//正規化したローカル座標
	std::vector<Vector2> sPos_;			//スクリーン座標
	Vector2 screenMidPos_;				//スクリーンの中心座標

	ObjectType type_;
	FillMode fillmode_;
};

