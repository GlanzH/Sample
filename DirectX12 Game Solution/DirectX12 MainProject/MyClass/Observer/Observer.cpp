#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	CollisionDetection(player, enemy,audience);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience) {
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetBox().sword_box.Intersects(enemies_roop->GetBox().box)) {
				if (enemies_roop->GetPostune() == "U" && player->GetAttackTag() == 1 && enemies_roop->FrontFlag()) {
					//はじかれるフラグをtrueにする関数を呼び出す
					//trueなら弾かれた時の処理を行う関数は別に作る

					player->GetFripFlag();

				}
				else if (enemies_roop->GetPostune() == "D" && player->GetAttackTag() == 2 && enemies_roop->FrontFlag()) {
					//はじかれるフラグをtrueにする関数を呼び出す
					//trueなら弾かれた時の処理を行う関数は別に作る
					player->GetFripFlag();

				}
				else {
					enemy->OnCollisionEnter(enemies_roop);
					if (hit_stop_count == 0 && player->GetHitFlag()) {
						hit_stop_flag = true;
						hit_attack_flag = true;
						hit_stop_count++;
					}
				}
			}
		}

		//!仮死状態の判定がないとき
		if (!enemies_roop->GetTemporaryDeathFlag()) {
			//if (player->GetBox().box.Intersects(enemies_roop->GetBox().box) && !player->IsInvincibleFlag()) {
			//	player->OnCollisionEnter(enemies_roop->GetTag());
			//}

			//if (player->GetBox().box.Intersects(enemies_roop->GetBox().box) &&
			//	player->IsInvincibleFlag() && enemies_roop->GetTag() == "AR") {
			//	player->OnCollisionEnter(enemies_roop->GetTag());
			//}


			//if (player->GetBox().box.Intersects(enemies_roop->GetBox().weapon)) {
			//	player->OnCollisionEnter(enemies_roop->GetTag());
			//}
			
			//右方向の敵に当たったら左にノックバック
			if (player->GetRightBox().right_box.Intersects(enemies_roop->GetBox().box) && !player->IsInvincibleFlag()) {
				player->OnRightCollisionEnter(enemies_roop->GetTag());
			}

			if (player->GetRightBox().right_box.Intersects(enemies_roop->GetBox().box) &&
				player->IsInvincibleFlag() && enemies_roop->GetTag() == "AR") {
				player->OnRightCollisionEnter(enemies_roop->GetTag());
			}

			if (player->GetRightBox().right_box.Intersects(enemies_roop->GetBox().weapon)) {
				player->OnRightCollisionEnter(enemies_roop->GetTag());
			}


			//右方向の敵に当たったら左にノックバック
			if (player->GetLeftBox().left_box.Intersects(enemies_roop->GetBox().box) && !player->IsInvincibleFlag()) {
				player->OnLeftCollisionEnter(enemies_roop->GetTag());
			}

			if (player->GetRightBox().right_box.Intersects(enemies_roop->GetBox().box) &&
				player->IsInvincibleFlag() && enemies_roop->GetTag() == "AR") {
				player->OnLeftCollisionEnter(enemies_roop->GetTag());
			}


			if (player->GetRightBox().right_box.Intersects(enemies_roop->GetBox().weapon)) {
				player->OnLeftCollisionEnter(enemies_roop->GetTag());
				
			}			
		}
	}
}

void Observer::Hit_Stop(const float deltaTime) {
	if (hit_stop_flag) {
		hit_stop_start += deltaTime;
		if (hit_stop_start >= hit_stop_end) {
			hit_stop_flag = false;
			hit_stop_start = 0.0f;
		}
	}

	if (hit_attack_flag) {
		hit_attack_start += deltaTime;
		if (hit_attack_start >= hit_attack_end) {
			hit_stop_count = 0;
			hit_attack_flag = false;
			hit_attack_start = 0.0f;
		}
	}
}