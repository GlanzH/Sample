#include "MyClass/Observer/Observer.h"

int Observer::Update(PlayerBase* player, EnemyManager* enemy, CoinManager coin) {
	CollisionDetection(player, enemy,coin);
	return 0;
}

void Observer::CollisionDetection(PlayerBase* player, EnemyManager* enemy, CoinManager coin) {
	for (auto coins_roop : coin.GetCoin()) {
		if (player->GetBox().box.Intersects(coins_roop->GetBox())) {
			coins_roop->OnCollisionEnter();
		}
	}
	
	
	for (auto enemies_roop : enemy->GetEnemy()) {
		if (player->IsAttack()) {
			if (player->GetBox().sword_box.Intersects(enemies_roop->GetBox().box)) {
				if (enemies_roop->GetAttackFlag() && enemies_roop->GetPostune() == "U" &&
					player->GetAttackTag() == 1 && enemies_roop->FrontFlag()
					) {
					//�͂������t���O��true�ɂ���֐����Ăяo��
					//true�Ȃ�e���ꂽ���̏������s���֐��͕ʂɍ��

					player->GetFripFlag();

				}
				else if (enemies_roop->GetAttackFlag() && enemies_roop->GetPostune() == "D" &&
					player->GetAttackTag() == 2 && enemies_roop->FrontFlag()
					) {
					//�͂������t���O��true�ɂ���֐����Ăяo��
					//true�Ȃ�e���ꂽ���̏������s���֐��͕ʂɍ��
					player->GetFripFlag();

				}
				else if (enemies_roop->GetTag() == "SH" && enemies_roop->GetTag() != "SW" &&
					enemies_roop->FrontFlag()
					) {
					if (player->GetAttackTag() == 1 || player->GetAttackTag() == 2) {
						player->GetFripFlag();
					}
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

		//!������Ԃ̔��肪�Ȃ��Ƃ�
		if (!enemies_roop->GetTemporaryDeathFlag() && !enemies_roop->GetDieFlag()) {
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
			
			//�E�����̓G�ɓ��������獶�Ƀm�b�N�o�b�N
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


			//�E�����̓G�ɓ��������獶�Ƀm�b�N�o�b�N
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