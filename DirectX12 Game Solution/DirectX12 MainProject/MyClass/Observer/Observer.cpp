#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	CollisionDetection(player, enemy,audience);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetBox().sword_box.Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionEnter(enemies_roop);
			}
		}

		//!ƒvƒŒƒCƒ„[SKINNEDMODELŒ^“–‚½‚è”»’è
		if (player->GetBox().box.Intersects(enemies_roop->GetBox().box)) {
				player->OnCollisionEnter();
		}


		if (player->GetSpecialAttackFlag()) {
			if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionSpecialMove(enemies_roop);
			}

		}
		else {
			if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionAudience(enemies_roop);
			}
		}
	}
}