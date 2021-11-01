#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerManager* player, EnemyManager* enemy) {
	CollisionDetection(player, enemy);
	return 0;
}

void Observer::CollisionDetection(PlayerManager* player, EnemyManager* enemy) {
	if (DXTK->KeyEvent->pressed.F || DXTK->KeyEvent->pressed.F) {
		for (auto enemy : enemy->GetEnemy()) {
			if (player->GetBox().Intersects(enemy->GetBox())) {
				enemy->Damage();
			}
		}
	}
}