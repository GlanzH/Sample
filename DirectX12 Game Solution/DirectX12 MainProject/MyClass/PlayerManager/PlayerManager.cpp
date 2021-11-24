#include "PlayerManager.h"

#include "MyClass/StatusManager/StatusManager.h"


bool PlayerManager::Initialize() 
{
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;

	appeal_state_mode = Appeal_state::NORMAL;

	direction_state_mode = Direction_State::RIGHT;

	return 0;
}

void PlayerManager::LoadAssets() 
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Player\\character_motion_v1122b_.X");
	model->SetScale(model_scale);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);

	//プレイヤーの当たり判定
	box = model->GetBoundingBox();

	box.Extents = SimpleMath::Vector3(box.Extents) * 0.01f;

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * player_box_size,
		box.Extents.y * player_box_size,
		box.Extents.z * player_box_size
	);
	collision->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);

	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	collision->SetMaterial(material);

	box.Center = player_pos;


	sword_box = model->GetBoundingBox();

	sword_box.Extents = SimpleMath::Vector3(sword_box.Extents) * 0.001f;

	sword_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		sword_box.Extents.x * box_size,
		sword_box.Extents.y * box_size,
		sword_box.Extents.z * box_size
	);


	sword_collision->SetScale(10, 10, 1);
	sword_box.Center = model->GetPosition() + SimpleMath::Vector3(15, 0, 0);


	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	//攻撃エフェクト
	DX12Effect.Initialize();
	//1
	Sword_Effect_1 = DX12Effect.Create(L"Effect\\SwordEffect\\one\\first_attack.efk");
	//2
	Sword_Effect_2 = DX12Effect.Create(L"Effect\\SwordEffect\\two\\second_attack.efk");
	//3
	Sword_Effect_3 = DX12Effect.Create(L"Effect\\SwordEffect\\three\\third_attack.efk");


}

int PlayerManager::Update(const float deltaTime)
{

	//モデル　アニメーション
	SetAnimation(model, STAND);

	//プレイヤー:移動
	Player_move(deltaTime);

	//プレイヤー:ジャンプ
	Player_jump(deltaTime);


	//プレイヤー:攻撃
	Player_attack(deltaTime);

	//ランバージャック(移動制限)
	Player_limit();

	//パリィ
	Parry(deltaTime);

	//アピール
	Appeal(deltaTime);


	//無敵時間
	Invincible(deltaTime);

	StatusManager::Instance().Update(deltaTime);



	//攻撃の向き
	if (direction_state_mode == Direction_State::RIGHT) {
		sword_box.Center = model->GetPosition() + SimpleMath::Vector3(7, 0, 0);
	}
	else if (direction_state_mode == Direction_State::LEFT) {
		sword_box.Center = model->GetPosition() + SimpleMath::Vector3(-5, 0, 0);
	}

	//攻撃判定の時間
	if (attack_flag)
		attack_zeit += deltaTime;
	if (attack_zeit > attack_zeit_max) {
		attack_flag = false;
		attack_zeit = 0.0f;
	}
	//if(DXTK->KeyState->Left)
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-8, 6, 0));
	//else if(DXTK->KeyState->Right)

	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-0.5, 4, 0));

	model->AdvanceTime(deltaTime);

	//auto pos_1 = model->GetTrackPosition(ACT1);
	//if (pos_1 > 0.5f)
	//	model->SetTrackPosition(ACT1, 0.0f);
	//auto pos_2 = model->GetTrackPosition(ACT2);
	//if (pos_2 > 0.5f)
	//	model->SetTrackPosition(ACT2, 0.0f);
	//auto pos_3 = model->GetTrackPosition(ACT3);
	//if (pos_3 > 0.5f)
	//	model->SetTrackPosition(ACT3, 0.0f);


	return 0;
}

void PlayerManager::Render() 
{
	//プレイヤーの描画
	model->Draw();

	//collision->Draw();
	//sword_collision->Draw();
}

void PlayerManager::OnCollisionEnter() {

	//敵に当たったときの処理
	if (!invincible_flag) {
		model->SetPosition(player_pos.x -= 2.0f, player_pos.y, player_pos.z);
		
		//無敵
		invincible_flag = true;

		sword_box.Center = model->GetPosition() + SimpleMath::Vector3(6, 0, 0);
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(8, 6, 0));

		box.Center = model->GetPosition();
		model->SetPosition(player_pos);
		collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
		//SetAnimation(model, Damage);
		//float dist = 0;
		//if (ground->IntersectRay(
		//	model->GetPosition() + SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		//	SimpleMath::Vector3::Up,
		//	&dist
		//)) {
		//	model->Move(0.0f, dist, 0.0f);
		//}
	}
}

void PlayerManager::Invincible(const float deltaTime)
{
	if (invincible_flag)
		invincible_time += deltaTime;

	if (invincible_time >= invincible_time_max) {
		invincible_flag = false;
		invincible_time = 0.0f;
	}
}


void PlayerManager::OnParryArea() {
	//パリィ成功時の処理

}

void PlayerManager::Parry(const float deltaTime) {
	if (!parry_flag) {
		if (DXTK->KeyEvent->pressed.P || DXTK->GamePadEvent[0].b) {
			parry_flag = true;
		}
	}
	else {
		parry_count += deltaTime;
		SetAnimation(model, PARRY);

	}
	if (parry_count >= max_parry_count) {
		parry_flag = false;
		parry_count = 0.0f;
	}
}

//指定されたモーションはTRUE,それ以外はFALSE
void PlayerManager::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}



void PlayerManager::_2DRender()
{
	//コンボ確認用
	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 0.0f),
		DX9::Colors::Black,
		L"%d",StatusManager::Instance().GetCombo()
	);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 40.0f),
	//	DX9::Colors::Red,
	//	L"%f", cool_time_zwei
	//);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 60.0f),
	//	DX9::Colors::Brown,
	//	L"%d", damage
	//);

	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 80.0f),
		DX9::Colors::DarkGreen,
		L"%f", animation_time
	);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 100.0f),
	//	DX9::Colors::DarkGreen,
	//	L"%d", damage
	//);


}

void PlayerManager::Player_move(const float deltaTime)
{
	if (!parry_flag) {
		if (appeal_state_mode == Appeal_state::NORMAL|| appeal_state_mode == Appeal_state::FOCUS) {
				//プレイヤー:移動(キーボード)
			if (DXTK->KeyState->Right || DXTK->KeyState->D || DXTK->GamePadState[0].dpad.right) {
				model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
				model->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);
				sword_box.Center = model->GetRotation();
				direction_state_mode = Direction_State::RIGHT;
				SetAnimation(model, RUN);

			}
			if (DXTK->KeyState->Left || DXTK->KeyState->A || DXTK->GamePadState[0].dpad.left) {
				model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
				model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
				sword_box.Center = model->GetRotation();
				direction_state_mode = Direction_State::LEFT;
				SetAnimation(model, RUN);
			}
		}
	}
}

void PlayerManager::Player_limit()
{
	//ランバージャック(移動制限)
	auto p_pos = model->GetPosition();
	p_pos = SimpleMath::Vector3(
		std::clamp(p_pos.x, -model_collision_detection_X,     model_collision_detection_X),
		std::clamp(p_pos.y,  model_collision_detection_Y_MIN, model_collision_detection_Y_MAX),
		std::clamp(p_pos.z, -model_collision_detection_Z,     model_collision_detection_Z)
	);
	model->SetPosition(p_pos);
}

void PlayerManager::Player_jump(const float deltaTime)
{
	//ジャンプ
	if (!parry_flag) {
		if (appeal_state_mode == Appeal_state::NORMAL || appeal_state_mode == Appeal_state::FOCUS) {
			if (!jump_flag_) {
				if (DXTK->KeyEvent->pressed.Space || DXTK->GamePadEvent[0].a) {
					jump_flag_ = true;
					jump_time_ = 0;
					jump_start_v_ = model->Position.y;

				}
			}
		}
	}

	if (jump_flag_) {

		jump_time_ += deltaTime;
		auto pos = model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time_ - 0.5f * gravity_ * jump_time_ * jump_time_;
		model->SetPosition(pos);

		if (model->GetPosition().y <= 0.5f) {
			jump_flag_ = false;
		}
	}
}


void PlayerManager::Player_attack(const float deltaTime) {
	////プレイヤー:攻撃
	//if (!cool_time_flag_zwei) {
	//	if (appeal_state_mode == Appeal_state::NORMAL || appeal_state_mode == Appeal_state::FOCUS) {
	//		if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
	//			StatusManager::Instance().AddCombo(deltaTime);
	//			count_time = 0.0f;
	//			attack_flag = true;
	//			if (IsAttack()) {
	//				if (StatusManager::Instance().GetCombo() == 1) {
	//					cool_time_flag_zwei = true;
	//					if (appeal_state_mode != Appeal_state::FOCUS)
	//						damage = 2;
	//					else
	//						damage = 2 * 2;

	//				}
	//				else if (StatusManager::Instance().GetCombo() == 2) {
	//					//SetAnimation(model, ACT2);

	//					cool_time_flag_zwei = true;
	//					if (appeal_state_mode != Appeal_state::FOCUS)
	//						damage = 3;
	//					else
	//						damage = 3 * 2;


	//					if (direction_state_mode == Direction_State::RIGHT) {
	//						handle_2 = DX12Effect.Play(Sword_Effect_2);
	//						DX12Effect.SetPosition(handle_2, Vector3(6, -7, 0));
	//						DX12Effect.SetSpeed(handle_2, 1.0f);
	//					}

	//					if (direction_state_mode == Direction_State::LEFT) {
	//						handle_2 = DX12Effect.Play(Sword_Effect_2);
	//						DX12Effect.SetPosition(handle_2, Vector3(-7, -9, -2));
	//						DX12Effect.SetSpeed(handle_2, 1.0f);
	//						DX12Effect.SetRotation(handle_2, Vector3(0, XMConvertToRadians(180), 0));
	//						DX12Effect.SetScale(handle_2, Vector3(1.5, 1.5, 1.5));

	//					}

	//				}
	//				else if (StatusManager::Instance().GetCombo() == 3) {
	//					//SetAnimation(model, ACT3);
	//					cool_time_flag_zwei = true;
	//					if (appeal_state_mode != Appeal_state::FOCUS)
	//						damage = 5;
	//					else
	//						damage = 5 * 2;

	//					if (direction_state_mode == Direction_State::RIGHT) {
	//						handle_3 = DX12Effect.Play(Sword_Effect_3);
	//						DX12Effect.SetPosition(handle_3, Vector3(6, -7, 0));
	//						DX12Effect.SetSpeed(handle_3, 1.5f);
	//					}

	//					if (direction_state_mode == Direction_State::LEFT) {
	//						handle_3 = DX12Effect.Play(Sword_Effect_3);
	//						DX12Effect.SetPosition(handle_3, Vector3(-7, -9, -2));
	//						DX12Effect.SetSpeed(handle_3, 1.5f);
	//						DX12Effect.SetRotation(handle_3, Vector3(0, XMConvertToRadians(180), 0));
	//						DX12Effect.SetScale(handle_3, Vector3(1.5, 1.5, 1.5));

	//					}

	//				}
	//			}
	//		}
	//	}
	//}
	//if (cool_time_flag_zwei) {
	//	cool_time_zwei += deltaTime;
	//	if (cool_time_zwei >= cool_time_max_zwei[count]) {
	//		cool_time_zwei = 0.0f;
	//		count++;
	//		cool_time_flag_zwei = false;
	//	}
	//}

	//count_time += deltaTime;
	//if (count >= 3 || count_time > count_time_max) {
	//	count = 0;
	//	count_time = 0.0f;
	//}
	if (!animation_flag) {
		if (appeal_state_mode == Appeal_state::NORMAL || appeal_state_mode == Appeal_state::FOCUS) {
			if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
				if (!first_attack_flag || attack_next_flag) {
					StatusManager::Instance().AddCombo(deltaTime);
					first_attack_flag = true;
				}
				     if (StatusManager::Instance().GetCombo() == 1 && animation_count == 0);
				else if (StatusManager::Instance().GetCombo() == 2 && animation_count == 1);
				else if (StatusManager::Instance().GetCombo() == 3 && animation_count == 2);

			}
		}
	}

	if (StatusManager::Instance().GetCombo() == 1 && animation_count == 0) {
		SetAnimation(model, ACT1);
		animation_flag = true;
		input_flag = true;

		auto pos = model->GetTrackPosition(ACT1);
		if (animation_flag) {
			if (pos > 0.617f)
				model->SetTrackPosition(ACT1, 0.0f);
		}


	}

	if (StatusManager::Instance().GetCombo() == 2 && animation_count == 1) {
		SetAnimation(model, ACT2);
		animation_flag = true;
		input_flag = true;

		auto pos = model->GetTrackPosition(ACT2);
		if (animation_flag) {
			if (pos > 0.517f)
				model->SetTrackPosition(ACT2, 0.0f);
		}

	}

	if (StatusManager::Instance().GetCombo() == 3&& animation_count == 2) {
		SetAnimation(model, ACT3);
		animation_flag = true;
		input_flag = true;
	}


	//アニメーション関係
	if (animation_flag) {
		animation_time += deltaTime;
		if (animation_time >= animation_time_max[animation_count]) {
			animation_time = 0.0f;
			animation_count++;
			animation_flag = false;
		}
	}

	if (animation_count >= 3) {
		animation_count = 0;
	}

	if (input_flag) {
		input_time += deltaTime;
		if (input_time < animation_time_max[animation_count]) {

			attack_next_flag = true;

		}

		if (input_time >= animation_time_max[animation_count]) {
			attack_next_flag = false;
			input_flag = false;
			input_time = 0.0f;
			animation_count++;
		}
	}


	////入力受付時間までの時間 & エフェクト表示までの時間
	//if (input_wait_flag) {
	//	input_wait_time += deltaTime;
	//	if (input_wait_time >= input_wait_time_max[input_wait_count]) {
	//		input_flag = true;
	//		input_wait_time = 0.0f;
	//		input_wait_count++;
	//		input_wait_flag = false;
	//	}
	//}

	//if (input_wait_count >= 3) {
	//	input_wait_count = 0;
	//}

	////入力受付時間 & エフェクト表示
	//if (input_flag) {
	//	input_time += deltaTime;
	//	effect_flag = true;
	//	if (input_time <= animation_time_max[input_count]) {
	//		if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
	//			StatusManager::Instance().AddCombo(deltaTime);
	//			
	//		}
	//	}
	//	if (input_time >= animation_time_max[input_count]) {
	//		input_time = 0.0f;
	//		input_count++;
	//		input_flag = false;
	//	}
	//}

	//if (input_count <= 2) {
	//	input_count = 0;
	//}

	if (effect_flag) {
		attack_flag = true;
		if (IsAttack()) {
			if (StatusManager::Instance().GetCombo() == 1 && animation_count == 0) {
				if (direction_state_mode == Direction_State::RIGHT) {
					handle_1 = DX12Effect.Play(Sword_Effect_1);
					DX12Effect.SetPosition(handle_1, Vector3(6, -7, 0));
					DX12Effect.SetSpeed(handle_1, 1.0f);
				}

				if (direction_state_mode == Direction_State::LEFT) {
					handle_1 = DX12Effect.Play(Sword_Effect_1);
					DX12Effect.SetPosition(handle_1, Vector3(-7, -9, -2));
					DX12Effect.SetSpeed(handle_1, 1.0f);
					DX12Effect.SetRotation(handle_1, Vector3(0, XMConvertToRadians(180), 0));
					DX12Effect.SetScale(handle_1, Vector3(1.5, 1.5, 1.5));

				}

				effect_flag = false;
			}
			else if (StatusManager::Instance().GetCombo() == 2 && animation_count == 1) {
				if (direction_state_mode == Direction_State::RIGHT) {
					handle_2 = DX12Effect.Play(Sword_Effect_2);
					DX12Effect.SetPosition(handle_2, Vector3(6, -7, 0));
					DX12Effect.SetSpeed(handle_2, 1.0f);
				}

				if (direction_state_mode == Direction_State::LEFT) {
					handle_2 = DX12Effect.Play(Sword_Effect_2);
					DX12Effect.SetPosition(handle_2, Vector3(-7, -9, -2));
					DX12Effect.SetSpeed(handle_2, 1.0f);
					DX12Effect.SetRotation(handle_2, Vector3(0, XMConvertToRadians(180), 0));
					DX12Effect.SetScale(handle_2, Vector3(1.5, 1.5, 1.5));

				}
				effect_flag = false;
			}
			else if (StatusManager::Instance().GetCombo() == 3 && animation_count == 2) {
				if (direction_state_mode == Direction_State::RIGHT) {
					handle_3 = DX12Effect.Play(Sword_Effect_3);
					DX12Effect.SetPosition(handle_3, Vector3(6, -7, 0));
					DX12Effect.SetSpeed(handle_3, 1.5f);
				}

				if (direction_state_mode == Direction_State::LEFT) {
					handle_3 = DX12Effect.Play(Sword_Effect_3);
					DX12Effect.SetPosition(handle_3, Vector3(-7, -9, -2));
					DX12Effect.SetSpeed(handle_3, 1.5f);
					DX12Effect.SetRotation(handle_3, Vector3(0, XMConvertToRadians(180), 0));
					DX12Effect.SetScale(handle_3, Vector3(1.5, 1.5, 1.5));
				}
				effect_flag = false;
			}
		}
	}
}


bool PlayerManager::IsAttack() {

	if (attack_flag) {
		return true;
	}
	return false;
}

void PlayerManager::Appeal(const float deltaTime)
{
	//アピール
	if (!jump_flag_) {
		if (DXTK->KeyEvent->pressed.W) {
			appeal_state_mode = Appeal_state::APPEAL;

		}
	}
	if (appeal_state_mode == Appeal_state::APPEAL) {
		SetAnimation(model, APPEIL);

		appeal_time += deltaTime;
		if (appeal_time >= appeal_time_max) {
			appeal_time = 0.0f;
			appeal_state_mode = Appeal_state::FOCUS;
		}
	}

	//ステータスアップ
	if (appeal_state_mode == Appeal_state::FOCUS) {
		focus_time += deltaTime;
		if (focus_time >= focus_time_max) {
			focus_time = 0.0f;
			appeal_state_mode = Appeal_state::NORMAL;
		}
	}

}