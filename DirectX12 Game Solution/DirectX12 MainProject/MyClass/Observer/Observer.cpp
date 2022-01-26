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
					player->GetAttackTag() == 1 && enemies_roop->FrontFlag()
					) {
					//はじかれるフラグをtrueにする関数を呼び出す
					//trueなら弾かれた時の処理を行う関数は別に作る

					player->GetFripFlag();

				}
				else if (enemies_roop->GetAttackFlag() && enemies_roop->GetPostune() == "D" &&
					player->GetAttackTag() == 2 && enemies_roop->FrontFlag()
					) {
					//はじかれるフラグをtrueにする関数を呼び出す
					//trueなら弾かれた時の処理を行う関数は別に作る
					player->GetFripFlag();

				}
				else {
					enemy->OnCollisionEnter(enemies_roop);
				}
			}
		}

		//!仮死状態の判定がないとき
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
	}
}