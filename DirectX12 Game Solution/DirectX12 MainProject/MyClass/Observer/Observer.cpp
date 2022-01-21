#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	CollisionDetection(player, enemy,audience);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetBox().sword_box.Intersects(enemies_roop->GetBox().box)) {
				if (enemies_roop->GetAttackFlag() && enemies_roop->GetPostune() == "U" &&
					DXTK->KeyEvent->pressed.A
				){
					//はじかれるフラグをtrueにする関数を呼び出す
					//trueなら弾かれた時の処理を行う関数は別に作る

				}
				else {
					enemy->OnCollisionEnter(enemies_roop);
				}
			}
		}

		//!突き攻撃の判定がないとき
		if (!enemies_roop->GetTemporaryDeathFlag()) {
			if (player->GetBox().box.Intersects(enemies_roop->GetBox().box) && !player->IsInvincibleFlag()) {
				player->OnCollisionEnter(enemies_roop->GetTag());
			}

			if (player->GetBox().box.Intersects(enemies_roop->GetBox().box) &&
				player->IsInvincibleFlag() && enemies_roop->GetTag() == "AR") {
				player->OnCollisionEnter(enemies_roop->GetTag());
			}


			if (player->GetBox().box.Intersects(enemies_roop->GetBox().weapon)) {
				player->OnCollisionEnter(enemies_roop->GetTag());
			}
		}

		//if (player->GetSpecialAttackFlag()) {
		//	if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetBox().box)) {
		//		enemy->OnCollisionSpecialMove(enemies_roop);
		//	}

		//}
		else {
			if (audience->GetBox().lv2_box.Intersects(enemies_roop->GetBox().box)) {
				enemy->OnCollisionAudience(enemies_roop);
			}
		}
	}
}