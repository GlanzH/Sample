#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy) {
	CollisionDetection(player, enemy);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy) {
	//プレイヤー・敵当たり判定
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetSwordBox().Intersects(enemies_roop->GetAnimBox()) ||
				player->GetSwordBox().Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionEnter(enemies_roop);
			}
		}

		if (player->GetBox().Intersects(enemies_roop->GetAnimBox()) ||
			player->GetBox().Intersects(enemies_roop->GetBox().box)) {
			if (!player->GetParryFlag()) {
				player->OnCollisionEnter();
			}
			else if (player->GetModel()->GetPosition().x < enemies_roop->GetAnimModel()->GetPosition().x ||
				player->GetModel()->GetPosition().x < enemies_roop->GetModel()->GetPosition().x) {
				player->OnParryArea();
				enemy->OnParryArea(enemies_roop);
			}
		}

		if (player->GetBox().Intersects(enemies_roop->GetBox().fire)) {
			player->OnCollisionEnter();
		}
	}
}