#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerManager* player, EnemyManager* enemy) {
	CollisionDetection(player, enemy);
	return 0;
}

void Observer::CollisionDetection(PlayerManager* player, EnemyManager* enemy) {
	//�v���C���[�E�G�����蔻��
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetSwordBox().Intersects(enemies_roop->GetBox()))
				enemy->OnCollisionEnter(enemies_roop);
		}

		if (player->GetBox().Intersects(enemies_roop->GetBox())) {
			if (!player->GetParryFlag()) {
				player->OnCollisionEnter();
			}
			else if (player->GetModel()->GetPosition().x < enemies_roop->GetModel()->GetPosition().x) {
				player->OnParryArea();
				enemy->OnParryArea(enemies_roop);
			}
		}
	}
}