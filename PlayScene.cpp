#include "PlayScene.h"

PlayScene::PlayScene() {
	for (int i = 0; i < 1; i++) {
		enemies.push_back(Enemy(EnemyType::kNormal));
		enemies[i].SetPos({ float(100 * i), 500 });
	}
}

PlayScene::~PlayScene() {
}

void PlayScene::Update() {
	player.Move();

	player.ShotBullets();

	for (auto& enemy : enemies) {
		enemy.Move();
		enemy.CollitionChecker(player.GetBullets());

		if (!enemy.GetIsActive()) {
			enemies.erase(enemies.begin());
		}
	}

	player.Ready(MatrixType::kSRT, gcamera);
}

void PlayScene::Draw() {
	player.Draw();
	
	for (auto& enemy : enemies) {
		enemy.Draw();
	}

	for (auto& bullet : player.GetBullets()) {
		bullet.Draw();
	}
}
