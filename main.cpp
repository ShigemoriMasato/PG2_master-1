#include <Novice.h>
#include "PlayScene.h"

const char kWindowTitle[] = "LC1A_10_シゲモリ_マサト";

Camera* gcamera;

char keys[256];
char preKeys[256];

int gbright;
BrightSetting bSet;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WinSizeWidth, WinSizeHeight);

	gcamera = new Camera();

	PlayScene* playScene = new PlayScene();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		switch (bSet) {
		case kBright:

			if (gbright < 255) {
				gbright += 3;
			}

			if (gbright > 255) {
				gbright = 255;
			}

			break;

		case kDark:

			if (gbright < 100) {
				gbright += 3;
			} else if (gbright > 100) {
				gbright -= 3;
			}

			if (gbright < 103 && gbright > 97) {
				gbright = 100;
			}

			break;

		case kBlack:

			if (gbright > 0) {
				gbright -= 3;
			}

			if (gbright < 0) {
				gbright = 0;
			}

			break;
		}

		///
		/// ↓更新処理ここから
		///

		playScene->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		playScene->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (false) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
