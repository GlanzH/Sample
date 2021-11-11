#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerManager* player,EnemyManager* enemy,Sword* sword) {
	CollisionDetection(player, enemy,sword);
	return 0;
}

void Observer::CollisionDetection(PlayerManager* player, EnemyManager* enemy, Sword* sword) {
	//プレイヤー・敵当たり判定
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetSwordBox().Intersects(enemies_roop->GetBox()))
				enemy->OnCollisionEnter(enemies_roop);
		}

		if (player->GetBox().Intersects(enemies_roop->GetBox())) {
			if (!player->GetParryFlag()) {
				player->OnCollisionEnter();
			}
			else if(player->GetModel()->GetPosition().x < enemies_roop->GetModel()->GetPosition().x) {
				player->OnParryArea();
				enemy->OnParryArea(enemies_roop);
			}
		}
	}
}