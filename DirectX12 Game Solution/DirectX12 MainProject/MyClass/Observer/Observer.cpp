#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy) {
	CollisionDetection(player, enemy);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy) {
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			//!
			if (player->GetSwordBox().Intersects(enemies_roop->GetAnimBox())) {
				enemy->OnCollisionEnter(enemies_roop);
			}

			if (player->GetSwordBox().Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionEnter(enemies_roop);
			}
		}


		//!プレイヤーSKINNEDMODEL型当たり判定
		if (player->GetBox().Intersects(enemies_roop->GetAnimBox())) {
			if (player->GetParryFlag()) {
				player->OnParryArea();
				enemy->OnParryArea(enemies_roop);
			}
			else  {
				player->OnCollisionEnter();
			}
		}

		//!プレイヤーMODEL型当たり判定
		if(player->GetBox().Intersects(enemies_roop->GetBox().box) ||
			player->GetBox().Intersects(enemies_roop->GetBox().box)) {
			if (player->GetParryFlag()) {
				player->OnParryArea();
				enemy->OnParryArea(enemies_roop);
			}
			else {
				player->OnCollisionEnter();
			}
		}

		//!炎の当たり判定
		if (player->GetBox().Intersects(enemies_roop->GetBox().fire)) {
			player->OnCollisionEnter();
		}
	}
}