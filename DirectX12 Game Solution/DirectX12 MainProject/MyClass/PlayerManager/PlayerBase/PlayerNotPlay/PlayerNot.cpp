#include "PlayerNot.h"

void PlayerNot::Initialize() {
	//�U���̃N�[���^�C��
	cool_time_flag_zwei = false;
	cool_time_zwei = 0.0f;
	cool_time_max_zwei = 1.0f;
	count = 0;

	count_flag = false;
	count_time = 0.0f;
	count_time_max = 0.4f;

	//�U��-����
	first_attaack_flag = false;

	//�U��-�J�E���g-�t���O
	//���[�V����
	motion_time_start_flag = false;

	motion_attack_flag = false;
	motion_time = 0.0f;

	motion_count = 0;

	//�G�t�F�N�g�̔����^�C�~���O��
	effect_generation = false;
	effect_generation_time = 0.1f;


	effect_end_flag = false;


	first_attack_hit = false;
	first_attack_time = 0.0f;
	first_attack_time_max = 0.333f;

	//�ύX*2
	motion_flag = 0;

	motion_flag_1 = false;
	motion_flag_2 = false;
	motion_flag_3 = false;

	motion_start_time_1 = false;
	motion_start_time_2 = false;
	motion_start_time_3 = false;


	motion_time_1 = 0.0f;
	motion_time_2 = 0.0f;
	motion_time_3 = 0.0f;

	motion_time_max_1 = 0.6f;
	motion_time_max_2 = 0.26f;
	motion_time_max_3 = 0.583f;

	//���͎�t���Ԃ܂ł̎��� & �G�t�F�N�g�\���܂ł̎���
	input_wait_flag = false;
	input_wait_time = 0.0f;
	input_wait_count = 0;

	//���͎�t����
	input_flag = false;
	input_time = 0.0f;
	input_count = 0;

	//�G�t�F�N�g�\��
	effect_flag = false;

	//�A�j���[�V�������o������
	animation_flag = false;
	animation_time = 0.0f;

	animation_count = 0;


}


void PlayerNot::Player_attack(const float deltaTime) {
	//�v���C���[:�U��
	if (!cool_time_flag_zwei) {
		if (!deathbrow_flag) {
			if (!appeil_flag) {
				if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
					//�ړ��s��
					canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;

					//����U��
					if (!first_attaack_flag) {
						//StatusManager::Instance().AddCombo(deltaTime);
						first_attaack_flag = true;
					}
					under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;

					//if (StatusManager::Instance().GetCombo() == 1);
					//else if (StatusManager::Instance().GetCombo() == 2);
					//else if (StatusManager::Instance().GetCombo() == 3);
				}
			}
		}

	}
	//if (StatusManager::Instance().GetCombo() == 1) {
	//	motion_time_start_flag = true;
	//	effect_generation = true;
	//	SetAnimation(model, ACT1);
	//}
	//if (StatusManager::Instance().GetCombo() == 2) {
	//	motion_time_start_flag = true;
	//	effect_generation = true;
	//	SetAnimation(model, ACT2);
	//}
	//if (StatusManager::Instance().GetCombo() == 3) {
	//	motion_time_start_flag = true;
	//	effect_generation = true;
	//	SetAnimation(model, ACT3);
	//}
	//if (motion_time_start_flag == true) {
	//	motion_time += deltaTime;
	//}
	//if (!motion_attack_flag) {
	//	if (motion_time >= 0.1f && motion_time < motion_time_max[motion_count]) {
	//		if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
	//			motion_attack_flag = true;
	//		}
	//	}
	//}
	//else {
	//	if (motion_time >= motion_time_max[motion_count]) {
	//		StatusManager::Instance().AddCombo(deltaTime);
	//		motion_time = 0.0f;
	//		motion_time_start_flag = false;
	//		motion_attack_flag = false;
	//		motion_count++;
	//		if (StatusManager::Instance().GetCombo() == 3) {
	//			cool_time_flag_zwei = true;
	//		}
	//	}
	//}
	//if (cool_time_flag_zwei == true) {
	//	cool_time_zwei += deltaTime;
	//}
	//if (cool_time_zwei >= cool_time_max_zwei) {
	//	first_attaack_flag = false;
	//	cool_time_flag_zwei = false;
	//	cool_time_zwei = 0.0f;
	//}


	//if (motion_count >= 3) {
	//	motion_count = 0;
	//	effect_generation_time = 0.0f;
	//	effect_generation = false;
	//	first_attaack_flag = false;
	//	under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
	//	canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

	//}
	//if (motion_time >= motion_time_max[motion_count] || StatusManager::Instance().GetCombo() == 0) {
	//	motion_time = 0.0f;
	//	effect_generation_time = 0.0f;
	//	effect_generation = false;
	//	motion_count = 0;
	//	under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
	//	canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
	//	first_attaack_flag = false;
	//}

	////�G�t�F�N�g�\���֌W
	//if (effect_generation == true) {
	//	effect_generation_time += deltaTime;
	//}

	//if (effect_generation_time >= effect_generation_time_max[motion_count]) {
	//	attack_flag = true;
	//	if (IsAttack()) {
	//		if (StatusManager::Instance().GetCombo() == 1 && motion_count == 0) {
	//			if (direction_state_mode == Direction_State::RIGHT) {
	//				DX12Effect.PlayOneShot("first");
	//				DX12Effect.SetPosition("first", Vector3(player_pos.x + 5.0f, player_pos.y + 2.0f, player_pos.z));

	//			}
	//			else if (direction_state_mode == Direction_State::LEFT) {
	//				DX12Effect.PlayOneShot("first");
	//				DX12Effect.SetPosition("first", Vector3(player_pos.x - 7.0f, player_pos.y + 2.0f, player_pos.z));
	//				DX12Effect.SetRotation("first", Vector3(0.0f, 180.0f, 0.0f));
	//			}
	//			damage = 2;
	//		}
	//		else if (StatusManager::Instance().GetCombo() == 2 && motion_count == 1) {

	//			if (direction_state_mode == Direction_State::RIGHT) {
	//				DX12Effect.PlayOneShot("second");
	//				DX12Effect.SetPosition("second", Vector3(player_pos.x + 4.0f, player_pos.y + 6.0f, player_pos.z));
	//			}
	//			else if (direction_state_mode == Direction_State::LEFT) {
	//				DX12Effect.PlayOneShot("second");
	//				DX12Effect.SetPosition("second", Vector3(player_pos.x - 4.0f, player_pos.y + 6.0f, player_pos.z));
	//				DX12Effect.SetRotation("second", Vector3(0.0f, 180.0f, 0.0f));

	//			}
	//			damage = 3;

	//		}
	//		else if (StatusManager::Instance().GetCombo() == 3 && motion_count == 2) {
	//			if (direction_state_mode == Direction_State::RIGHT) {
	//				DX12Effect.PlayOneShot("third");
	//				DX12Effect.SetPosition("third", Vector3(player_pos.x + 7.0f, player_pos.y + 5.0f, player_pos.z));
	//			}
	//			else if (direction_state_mode == Direction_State::LEFT) {
	//				DX12Effect.PlayOneShot("third");
	//				DX12Effect.SetPosition("third", Vector3(player_pos.x - 7.0f, player_pos.y + 5.0f, player_pos.z));
	//				DX12Effect.SetRotation("third", Vector3(0.0f, 180.0f, 0.0f));

	//			}
	//			damage = 5;

	//		}
	//	}
	//}
}

//�v���C���[�̍U��(�{�^���z�u�ύXver)
void PlayerNot::Player_Attack_two(const float deltaTime) {
//	if (!cool_time_flag_zwei) {
//		if (!parry_flag) {
//			if (!deathbrow_flag) {
//				if (!appeil_flag) {
//
//					//1����
//					if (DXTK->KeyEvent->pressed.A || DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
//						motion_flag_1 = true;
//						//�ړ��s��
//						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
//
//						//�W�����v�s��
//						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;
//
//						//�U�����@���̍U���s��
//						if (cannot_other == CANNOT_OTHER_ATTACK::NOMAL_STATE && cannot_other != CANNOT_OTHER_ATTACK::SECOND && cannot_other != CANNOT_OTHER_ATTACK::THIRD) {
//							cannot_other = CANNOT_OTHER_ATTACK::FIRST;
//
//							Attack(deltaTime);
//
//						}
//					}
//
//					//2����
//					if (DXTK->KeyEvent->pressed.S || DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
//						motion_flag_2 = true;
//						//�ړ��s��
//						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
//						//�W�����v�s��
//						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;
//
//						//�U�����@���̍U���s��
//						if (cannot_other == CANNOT_OTHER_ATTACK::NOMAL_STATE && cannot_other != CANNOT_OTHER_ATTACK::FIRST && cannot_other != CANNOT_OTHER_ATTACK::THIRD) {
//							cannot_other = CANNOT_OTHER_ATTACK::SECOND;
//
//							Attack(deltaTime);
//
//						}
//
//					}
//
//					//3����
//					if (DXTK->KeyEvent->pressed.D || DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED) {
//						motion_flag_3 = true;
//						//�ړ��s��
//						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
//						//�W�����v�s��
//						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;
//
//						if (cannot_other == CANNOT_OTHER_ATTACK::NOMAL_STATE && cannot_other != CANNOT_OTHER_ATTACK::FIRST && cannot_other != CANNOT_OTHER_ATTACK::SECOND) {
//							cannot_other = CANNOT_OTHER_ATTACK::THIRD;
//
//
//							Attack(deltaTime);
//
//						}
//					}
//
//				}
//			}
//		}
//	}
//
//
//	if (motion_flag_1) {
//		if (cannot_other == CANNOT_OTHER_ATTACK::FIRST) {
//			effect_generation = true;
//			motion_start_time_1 = true;
//			motion_count = 0;
//			SetAnimation(model, ACT1);
//		}
//	}
//
//	if (motion_start_time_1) {
//		motion_time_1 += deltaTime;
//	}
//
//	if (motion_time_1 >= motion_time_max_1) {
//
//
//		motion_start_time_1 = false;
//		motion_time_1 = 0.0f;
//		motion_flag_1 = false;
//
//		model->SetTrackPosition(ACT1, 0.0);
//
//		//�ړ���
//		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
//		//�W�����v��
//		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
//		//�U�����@���̍U���s��->����
//		cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;
//	}
//
//	if (motion_flag_2) {
//		if (cannot_other == CANNOT_OTHER_ATTACK::SECOND) {
//			effect_generation = true;
//			motion_start_time_2 = true;
//			motion_count = 1;
//			SetAnimation(model, ACT2);
//		}
//	}
//
//	if (motion_start_time_2) {
//		motion_time_2 += deltaTime;
//	}
//
//	if (motion_time_2 >= motion_time_max_2) {
//
//
//		motion_start_time_2 = false;
//		motion_time_2 = 0.0f;
//		motion_flag_2 = false;
//		model->SetTrackPosition(ACT2, 0.0);
//
//		//�ړ��s��
//		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
//
//		//�W�����v��
//		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
//
//		//���̍U���s��_����
//		cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;
//	}
//
//
//	if (motion_flag_3) {
//		effect_generation = true;
//		motion_start_time_3 = true;
//		motion_count = 2;
//		SetAnimation(model, ACT3);
//	}
//
//	if (motion_start_time_3) {
//		motion_time_3 += deltaTime;
//	}
//
//	if (motion_time_3 >= motion_time_max_3) {
//		motion_start_time_3 = false;
//		motion_time_3 = 0.0f;
//		motion_flag_3 = false;
//
//		model->SetTrackPosition(ACT3, 0.0);
//
//		//�ړ��s��
//		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
//
//		//�W�����v��
//		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
//
//		//���̍U���s��_����
//		cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;
//	}
//
//	//�G�t�F�N�g�\���֌W
//	if (effect_generation) {
//		effect_generation_time += deltaTime;
//		//effect_generation = false;
//	}
//
//	if (effect_generation_time >= 1.0f) {
//		effect_generation_time = 0.0f;
//	}
//
//
//
//	if (first_attack_hit) {
//		first_attack_time += deltaTime;
//		if (first_attack_time >= first_attack_time_max) {
//			attack_flag = true;
//			if (IsAttack()) {
//				//�G�l�~�[�ɗ^����_���[�W
//				damage = 2;
//				first_attack_hit = false;
//				first_attack_time = 0.0f;
//
//				//SE
//				first_attack_se->Play();
//			}
//		}
//	}
//
//}
//
//void PlayerBase::Attack(const float deltaTime)
//{
//	if (cannot_other == CANNOT_OTHER_ATTACK::FIRST) {
//		if (effect_generation_time >= 0.0f) {
//			if (motion_flag_1) {
//				first_attack_hit = true;
//				Attack_First(deltaTime);
//			}
//		}
//	}
//
//	if (cannot_other == CANNOT_OTHER_ATTACK::SECOND) {
//		if (effect_generation_time >= 0.033f) {
//			attack_flag = true;
//			if (IsAttack()) {
//				if (motion_flag_2) {
//					//�G�l�~�[�ɗ^����_���[�W
//					damage = 3;
//					Attack_Secnod(deltaTime);
//					second_attack_se->Play();
//				}
//			}
//		}
//	}
//
//	if (cannot_other == CANNOT_OTHER_ATTACK::THIRD) {
//		if (effect_generation_time >= 0.005f) {
//			attack_flag = true;
//			if (IsAttack()) {
//				if (motion_flag_3) {
//					//�G�l�~�[�ɗ^����_���[�W
//					damage = 5;
//					Attack_Third(deltaTime);
//					third_attack_se->Play();
//				}
//			}
//		}
//	}
}

//�G�t�F�N�g1����
void PlayerNot::Attack_First(const float deltaTime) {
	//if (direction_state_mode == Direction_State::RIGHT) {
	//	if (DX12Effect.CheckAlive("first")) {
	//		DX12Effect.Stop("first");
	//		DX12Effect.PlayOneShot("first", Vector3(player_pos.x + 2.0f, player_pos.y + 5.0f, player_pos.z));

	//	}
	//	else
	//	{
	//		DX12Effect.PlayOneShot("first", Vector3(player_pos.x + 2.0f, player_pos.y + 5.0f, player_pos.z));

	//	}
	//	DX12Effect.SetRotation("first", Vector3(0.0f, 0.0f, 0.0f));
	//}
	//else if (direction_state_mode == Direction_State::LEFT) {
	//	if (DX12Effect.CheckAlive("first")) {
	//		DX12Effect.Stop("first");
	//		DX12Effect.PlayOneShot("first", Vector3(player_pos.x - 7.0f, player_pos.y + 4.0f, player_pos.z));
	//	}
	//	else
	//	{
	//		DX12Effect.PlayOneShot("first", Vector3(player_pos.x - 7.0f, player_pos.y + 4.0f, player_pos.z));
	//	}
	//	DX12Effect.SetRotation("first", Vector3(0.0f, 180.0f, 0.0f));
	//}


}
//�G�t�F�N�g2����
void PlayerNot::Attack_Secnod(const float deltaTime) {
	//if (direction_state_mode == Direction_State::RIGHT) {
	//	if (DX12Effect.CheckAlive("second")) {
	//		DX12Effect.Stop("second");
	//		DX12Effect.PlayOneShot("second", Vector3(player_pos.x + 3.0f, player_pos.y + 6.0f, player_pos.z));
	//	}
	//	else
	//	{
	//		DX12Effect.PlayOneShot("second", Vector3(player_pos.x + 3.0f, player_pos.y + 6.0f, player_pos.z));
	//	}

	//	DX12Effect.SetScale("second", Vector3(1.5f, 1.5f, 1.5f));

	//}
	//else if (direction_state_mode == Direction_State::LEFT) {
	//	if (DX12Effect.CheckAlive("second")) {
	//		DX12Effect.Stop("second");
	//		DX12Effect.PlayOneShot("second", Vector3(player_pos.x - 3.0f, player_pos.y + 6.0f, player_pos.z));
	//	}
	//	else
	//	{
	//		DX12Effect.PlayOneShot("second", Vector3(player_pos.x - 3.0f, player_pos.y + 6.0f, player_pos.z));
	//	}
	//	DX12Effect.SetScale("second", Vector3(1.5f, 1.5f, 1.5f));
	//	DX12Effect.SetRotation("second", Vector3(0.0f, 180.0f, 0.0f));

	//}

}
//�G�t�F�N�g3����
void PlayerNot::Attack_Third(const float deltaTime) {
	//if (direction_state_mode == Direction_State::RIGHT) {
	//	if (DX12Effect.CheckAlive("third")) {
	//		DX12Effect.Stop("third");
	//		DX12Effect.PlayOneShot("third", Vector3(player_pos.x + 7.0f, player_pos.y + 5.0f, player_pos.z));
	//	}
	//	else
	//	{
	//		DX12Effect.PlayOneShot("third", Vector3(player_pos.x + 7.0f, player_pos.y + 5.0f, player_pos.z));
	//	}
	//}
	//else if (direction_state_mode == Direction_State::LEFT) {
	//	if (DX12Effect.CheckAlive("third")) {
	//		DX12Effect.Stop("third");
	//		DX12Effect.PlayOneShot("third", Vector3(player_pos.x - 7.0f, player_pos.y + 5.0f, player_pos.z));
	//	}
	//	else
	//	{
	//		DX12Effect.PlayOneShot("third", Vector3(player_pos.x - 7.0f, player_pos.y + 5.0f, player_pos.z));
	//	}
	//	DX12Effect.SetRotation("third", Vector3(0.0f, 180.0f, 0.0f));
	//}

}
