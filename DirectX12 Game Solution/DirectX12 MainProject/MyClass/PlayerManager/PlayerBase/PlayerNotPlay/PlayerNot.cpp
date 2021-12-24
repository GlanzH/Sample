#include "PlayerNot.h"

void PlayerNot::Initialize() {
	//攻撃のクールタイム
	cool_time_flag_zwei = false;
	cool_time_zwei = 0.0f;
	cool_time_max_zwei = 1.0f;
	count = 0;

	count_flag = false;
	count_time = 0.0f;
	count_time_max = 0.4f;

	//攻撃-初回
	first_attaack_flag = false;

	//攻撃-カウント-フラグ
	//モーション
	motion_time_start_flag = false;

	motion_attack_flag = false;
	motion_time = 0.0f;

	motion_count = 0;

	//エフェクトの発生タイミング等
	effect_generation = false;
	effect_generation_time = 0.1f;


	effect_end_flag = false;


	first_attack_hit = false;
	first_attack_time = 0.0f;
	first_attack_time_max = 0.333f;

	//変更*2
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

	//入力受付時間までの時間 & エフェクト表示までの時間
	input_wait_flag = false;
	input_wait_time = 0.0f;
	input_wait_count = 0;

	//入力受付時間
	input_flag = false;
	input_time = 0.0f;
	input_count = 0;

	//エフェクト表示
	effect_flag = false;

	//アニメーションを出す時間
	animation_flag = false;
	animation_time = 0.0f;

	animation_count = 0;


}


void PlayerNot::Player_attack(const float deltaTime) {
	//プレイヤー:攻撃
	if (!cool_time_flag_zwei) {
		if (!deathbrow_flag) {
			if (!appeil_flag) {
				if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
					//移動不可
					canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;

					//初回攻撃
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

	////エフェクト表示関係
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

//プレイヤーの攻撃(ボタン配置変更ver)
void PlayerNot::Player_Attack_two(const float deltaTime) {
//	if (!cool_time_flag_zwei) {
//		if (!parry_flag) {
//			if (!deathbrow_flag) {
//				if (!appeil_flag) {
//
//					//1撃目
//					if (DXTK->KeyEvent->pressed.A || DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
//						motion_flag_1 = true;
//						//移動不可
//						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
//
//						//ジャンプ不可
//						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;
//
//						//攻撃中　他の攻撃不可
//						if (cannot_other == CANNOT_OTHER_ATTACK::NOMAL_STATE && cannot_other != CANNOT_OTHER_ATTACK::SECOND && cannot_other != CANNOT_OTHER_ATTACK::THIRD) {
//							cannot_other = CANNOT_OTHER_ATTACK::FIRST;
//
//							Attack(deltaTime);
//
//						}
//					}
//
//					//2撃目
//					if (DXTK->KeyEvent->pressed.S || DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
//						motion_flag_2 = true;
//						//移動不可
//						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
//						//ジャンプ不可
//						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;
//
//						//攻撃中　他の攻撃不可
//						if (cannot_other == CANNOT_OTHER_ATTACK::NOMAL_STATE && cannot_other != CANNOT_OTHER_ATTACK::FIRST && cannot_other != CANNOT_OTHER_ATTACK::THIRD) {
//							cannot_other = CANNOT_OTHER_ATTACK::SECOND;
//
//							Attack(deltaTime);
//
//						}
//
//					}
//
//					//3撃目
//					if (DXTK->KeyEvent->pressed.D || DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED) {
//						motion_flag_3 = true;
//						//移動不可
//						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
//						//ジャンプ不可
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
//		//移動可
//		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
//		//ジャンプ可
//		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
//		//攻撃中　他の攻撃不可->解除
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
//		//移動不可
//		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
//
//		//ジャンプ可
//		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
//
//		//他の攻撃不可_解除
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
//		//移動不可
//		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
//
//		//ジャンプ可
//		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
//
//		//他の攻撃不可_解除
//		cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;
//	}
//
//	//エフェクト表示関係
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
//				//エネミーに与えるダメージ
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
//					//エネミーに与えるダメージ
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
//					//エネミーに与えるダメージ
//					damage = 5;
//					Attack_Third(deltaTime);
//					third_attack_se->Play();
//				}
//			}
//		}
//	}
}

//エフェクト1撃目
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
//エフェクト2撃目
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
//エフェクト3撃目
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
