#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerManager* player, EnemyManager* enemy) {
	CollisionDetection(player, enemy);
	return 0;
}

void Observer::CollisionDetection(PlayerManager* player, EnemyManager* enemy) {
	//プレイヤー・敵当たり判定
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (DXTK->KeyEvent->pressed.F || DXTK->KeyEvent->pressed.J) {
			if (player->GetBox().Intersects(enemies_roop->GetBox())) {
				enemy->OnCollisionEnter(enemies_roop);
			}
		}
	}
}