#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	CollisionDetection(player, enemy,audience);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetBox().sword_box.Intersects(enemies_roop->GetAnimBox())) {
				enemy->OnCollisionEnter(enemies_roop);
			}

			if (player->GetBox().sword_box.Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionEnter(enemies_roop);
			}
		}

		//!プレイヤーSKINNEDMODEL型当たり判定
		if (player->GetBox().box.Intersects(enemies_roop->GetAnimBox())) {
				player->OnCollisionEnter();
		}

		//!プレイヤーMODEL型当たり判定
		if(player->GetBox().box.Intersects(enemies_roop->GetBox().box)    ||
		   player->GetBox().box.Intersects(enemies_roop->GetBox().bullet) ||
			player->GetBox().box.Intersects(enemies_roop->GetBox().fire)) {
			player->OnCollisionEnter();
		}

		if (player->GetSpecialAttackFlag()) {
			if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetAnimBox())) {
				enemy->OnCollisionSpecialMove(enemies_roop);
			}

			if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionSpecialMove(enemies_roop);
			}
		}
		else {
			if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetAnimBox())) {
				enemy->OnCollisionAudience(enemies_roop);
			}

			if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionAudience(enemies_roop);
			}
		}
	}
}