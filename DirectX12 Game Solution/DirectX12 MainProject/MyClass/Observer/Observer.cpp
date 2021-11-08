#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerManager* player,EnemyManager* enemy,Sword* sword) {
	CollisionDetection(player, enemy,sword);
	return 0;
}

void Observer::CollisionDetection(PlayerManager* player, EnemyManager* enemy, Sword* sword) {
	//�v���C���[�E�G�����蔻��
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (DXTK->KeyEvent->pressed.F || DXTK->KeyEvent->pressed.J || DXTK->GamePadEvent->b) {
			if (sword->GetBox().Intersects(enemies_roop->GetBox())) {
				enemy->OnCollisionEnter(enemies_roop);
			}
		}

		if (player->GetBox().Intersects(enemies_roop->GetBox())) {
			player->OnCollisionEnter();
		}
	}
}