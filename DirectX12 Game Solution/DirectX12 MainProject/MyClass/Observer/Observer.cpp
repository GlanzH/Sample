#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	CollisionDetection(player, enemy,audience);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetSwordBox().Intersects(enemies_roop->GetAnimBox())) {
				enemy->OnCollisionEnter(enemies_roop);
			}

			if (player->GetSwordBox().Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionEnter(enemies_roop);
			}
		}

		//!vC[SKINNEDMODEL^½θ»θ
		if (player->GetBox().Intersects(enemies_roop->GetAnimBox())) {
				player->OnCollisionEnter();
		}

		//!vC[MODEL^½θ»θ
		if(player->GetBox().Intersects(enemies_roop->GetBox().box)    ||
		   player->GetBox().Intersects(enemies_roop->GetBox().bullet) ||
			player->GetBox().Intersects(enemies_roop->GetBox().fire)) {
			player->OnCollisionEnter();
		}

		//!GEΟqΜU(SKINNEDMODEL)
		if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetAnimBox())) {
			enemy->OnCollisionAudience(enemies_roop);
		}

		//!GEΟqΜU(MODEL)
		if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetBox().box)) {
			enemy->OnCollisionAudience(enemies_roop);
		}
	}
}