#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy) {
	CollisionDetection(player, enemy);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy) {
	//�v���C���[�E�G�����蔻��
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetSwordBox().Intersects(enemies_roop->GetAnimBox()))
				enemy->OnCollisionEnter(enemies_roop);
		}

		if (player->GetBox().Intersects(enemies_roop->GetAnimBox())) {
			if (!player->GetParryFlag()) {
				player->OnCollisionEnter();
			}
			else if (player->GetModel()->GetPosition().x < enemies_roop->GetAnimModel()->GetPosition().x) {
				player->OnParryArea();
				enemy->OnParryArea(enemies_roop);
			}
		}
	}
}