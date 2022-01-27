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
				else {
					enemy->OnCollisionEnter(enemies_roop);
					//hit_stop_flag = true;
				}
			}
		}

		//!������Ԃ̔��肪�Ȃ��Ƃ�
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
	}
	if (hit_stop_start >= hit_stop_end) {
		hit_stop_flag = false;
		hit_stop_start = 0.0f;
	}
}