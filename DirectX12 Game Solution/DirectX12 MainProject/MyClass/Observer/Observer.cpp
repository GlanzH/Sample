#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerManager* player, EnemyManager* enemy) {
	CollisionDetection(player, enemy);
	return 0;
}

void Observer::CollisionDetection(PlayerManager* player, EnemyManager* enemy) {
	if (DXTK->KeyEvent->pressed.F || DXTK->KeyEvent->pressed.J) {
		for (auto enemies_roop : enemy->GetEnemy()) {
			if (player->GetBox().Intersects(enemies_roop->GetBox())) {
				enemy->OnCollisionEnter(enemies_roop);
			}
		}
	}
}