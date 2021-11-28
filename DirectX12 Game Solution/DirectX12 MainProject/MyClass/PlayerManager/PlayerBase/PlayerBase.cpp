#include "PlayerBase.h"

#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerAttack/PlayerAttack.h"


bool PlayerBase::Initialize()
{
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;

	appeal_state_mode = Appeal_state::NORMAL;

	direction_state_mode = Direction_State::RIGHT;

	under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;

	return 0;
}

void PlayerBase::LoadAssets()
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Player\\character_motion_v1122b_.X");
	model->SetScale(model_scale);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);

	//プレイヤーの当たり判定
	box = model->GetBoundingBox();

	box.Extents = SimpleMath::Vector3(box.Extents);

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * player_box_size_x,
		box.Extents.y * player_box_size_y,
		box.Extents.z * player_box_size_z
	);
	collision->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);

	material.Diffuse  = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient  = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	collision->SetMaterial(material);

	collision->SetScale(0.05f);


	sword_box = model->GetBoundingBox();

	sword_box.Extents = SimpleMath::Vector3(sword_box.Extents);

	sword_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		sword_box.Extents.x * box_size_x,
		sword_box.Extents.y * box_size_y,
		sword_box.Extents.z * box_size_z
	);


	sword_collision->SetScale(3, 3, 5);
	sword_box.Center = model->GetPosition() + SimpleMath::Vector3(15, 0, 0);


	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	DX12Effect.Initialize();
	DX12Effect.Create(L"Effect\\SwordEffect\\one\\first_attack.efk","first");
	DX12Effect.Create(L"Effect\\SwordEffect\\two\\second_attack.efk","second");
	DX12Effect.Create(L"Effect\\SwordEffect\\three\\third_attack.efk","third");

}

int PlayerBase::Update(const float deltaTime)
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

	//必殺技
	SpecialMove();


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

	sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(8, 6, 0));

	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 6, 0));

	model->AdvanceTime(deltaTime);



	return 0;
}

void PlayerBase::Render()
{
	//プレイヤーの描画
	model->Draw();

	//collision->Draw();
	//sword_collision->Draw();
}

void PlayerBase::OnCollisionEnter() {

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
	}
}

void PlayerBase::Invincible(const float deltaTime)
{
	if (invincible_flag)
		invincible_time += deltaTime;

	if (invincible_time >= invincible_time_max) {
		invincible_flag = false;
		invincible_time = 0.0f;
	}
}

void PlayerBase::OnParryArea() {
	//パリィ成功時の処理

}

void PlayerBase::Parry(const float deltaTime) {
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
void PlayerBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}

void PlayerBase::Player_move(const float deltaTime)
{
	if (!parry_flag) {
		if (appeal_state_mode == Appeal_state::NORMAL|| appeal_state_mode == Appeal_state::FOCUS) {
				//プレイヤー:移動(キーボード) & ゲームパッド十字キー
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

void PlayerBase::Player_limit()
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

void PlayerBase::Player_jump(const float deltaTime)
{
	//ジャンプ
	if (!parry_flag) {
		if(under_attack_state_mode==UNDER_ATTACK_STATE::NOMAL){
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

void PlayerBase::Player_attack(const float deltaTime) {
	//プレイヤー:攻撃
	if (!cool_time_flag_zwei) {
		if (appeal_state_mode == Appeal_state::NORMAL || appeal_state_mode == Appeal_state::FOCUS) {
			if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
				if (!first_attaack_flag) {
					StatusManager::Instance().AddCombo(deltaTime);
					first_attaack_flag = true;
				}
				under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;

				     if (StatusManager::Instance().GetCombo() == 1);
				else if (StatusManager::Instance().GetCombo() == 2);
				else if (StatusManager::Instance().GetCombo() == 3);
			}
		}
	}
	if (StatusManager::Instance().GetCombo() == 1) {
		motion_time_start_flag = true;
		effect_generation      = true;
		SetAnimation(model, ACT1);
	}
	if (StatusManager::Instance().GetCombo() == 2) {
		motion_time_start_flag = true;
		effect_generation      = true;
		SetAnimation(model, ACT2);
	}
	if (StatusManager::Instance().GetCombo() == 3) {
		motion_time_start_flag = true;
		effect_generation      = true;
		SetAnimation(model, ACT3);
	}
	if (motion_time_start_flag == true) {
		motion_time += deltaTime;
	}
	if (!motion_attack_flag) {
		if (motion_time >= 0.1f && motion_time < motion_time_max[motion_count]) {
			if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
				motion_attack_flag = true;
			}
		}
	} else {
		if (motion_time >= motion_time_max[motion_count]) {
			StatusManager::Instance().AddCombo(deltaTime);
			motion_time = 0.0f;
			motion_time_start_flag = false;
			motion_attack_flag = false;
			motion_count++;
			if (StatusManager::Instance().GetCombo() == 3) {
				cool_time_flag_zwei = true;
			}
		}
	}
	if (cool_time_flag_zwei == true) {
		cool_time_zwei += deltaTime;
	}
	if (cool_time_zwei >= cool_time_max_zwei) {
		first_attaack_flag = false;
		cool_time_flag_zwei = false;
		cool_time_zwei = 0.0f;
	}
	if (motion_count >= 3) {
		motion_count = 0;
		effect_generation_time = 0.0f;
		effect_generation = false;
		first_attaack_flag = false;
		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;

	}
	if (motion_time >= motion_time_max[motion_count] || StatusManager::Instance().GetCombo() == 0) {
		motion_time = 0.0f;
		effect_generation_time = 0.0f;
		effect_generation = false;
		motion_count = 0;
		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
		first_attaack_flag = false;
	}

	//エフェクト表示関係
	if (effect_generation == true) {
		effect_generation_time += deltaTime;
	}

	if (effect_generation_time >= effect_generation_time_max[motion_count]) {
		attack_flag = true;
		if (IsAttack()) {
			if (StatusManager::Instance().GetCombo() == 1 && motion_count == 0) {
				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("first");
					DX12Effect.SetPosition("first", Vector3(6, -5, 50));
					DX12Effect.SetScale("first", Vector3(1.5f, 1.5f, 1.5f));
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("first");
					DX12Effect.SetRotation("first", Vector3(0.0f, 180.0f, 0.0f));
				}
				if (appeal_state_mode != Appeal_state::FOCUS)
					damage = 2;
				if (appeal_state_mode == Appeal_state::FOCUS)
					damage = 2 * 2;
			}
			else if (StatusManager::Instance().GetCombo() == 2 && motion_count == 1) {

				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("second");
					DX12Effect.SetPosition("second", Vector3(6, -2, 50));
					DX12Effect.SetScale("second", Vector3(2.0f, 2.0f, 2.0f));
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("second");
					DX12Effect.SetRotation("second", Vector3(0.0f, 180.0f, 0.0f));

				}

				if (appeal_state_mode != Appeal_state::FOCUS)
					damage = 3;
				if (appeal_state_mode == Appeal_state::FOCUS)
					damage = 3 * 2;

			}
			else if (StatusManager::Instance().GetCombo() == 3 && motion_count == 2) {
				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("third");
					DX12Effect.SetPosition("third", Vector3(9, -5, 0));
					DX12Effect.SetScale("third", Vector3(1.5f, 1.5f, 1.5f));

				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("third");
					DX12Effect.SetRotation("third", Vector3(0.0f, 180.0f, 0.0f));

				}
				if (appeal_state_mode != Appeal_state::FOCUS)
					damage = 5;
				if (appeal_state_mode == Appeal_state::FOCUS)
					damage = 5 * 2;

			}
		}
	}


	//auto motion_1 = model->GetTrackPosition(ACT1);
	//if (motion_1 >= 0.617f) {
	//	model->SetTrackPosition(ACT1, 0.0f);
	//}

	//auto motion_2 = model->GetTrackPosition(ACT2);
	//if (motion_2 >= 0.517f) {
	//	model->SetTrackPosition(ACT2, 0.0f);
	//}

	//auto motion_3 = model->GetTrackPosition(ACT3);
	//if (motion_3 >= 0.583f) {
	//	model->SetTrackPosition(ACT3, 0.0f);
	//}

}

void PlayerBase::SpecialMove() {
	if (!jump_flag_) {
		if (DXTK->KeyEvent->pressed.L ||
			DXTK->GamePadEvent[0].rightShoulder ||
			DXTK->GamePadEvent[0].leftShoulder) {

		}
	}
}


bool PlayerBase::IsAttack() {

	if (attack_flag) {
		return true;
	}
	return false;
}

void PlayerBase::Appeal(const float deltaTime)
{
	//アピール
	if (!jump_flag_) {
		if (DXTK->KeyEvent->pressed.W||DXTK->GamePadEvent[0].y) {
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

void PlayerBase::_2DRender()
{
	if (!invincible_flag) {
		DX9::SpriteBatch->DrawString(font.Get(),
			SimpleMath::Vector2(1000.0f, 70.0f),
			DX9::Colors::BlueViolet,
			L"OFF"
		);
	}
	else {
		DX9::SpriteBatch->DrawString(font.Get(),
			SimpleMath::Vector2(1000.0f, 70.0f),
			DX9::Colors::BlueViolet,
			L"ON"
		);
	}

	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 90.0f),
		DX9::Colors::BlueViolet,
		L"%f", invincible_time
	);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 190.0f),
	//	DX9::Colors::BlueViolet,
	//	L"%d",motion_count
	//);

	//if (effect_generation){
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 130.0f),
	//		DX9::Colors::BlueViolet,
	//		L"ON"
	//	);
	//} else {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 130.0f),
	//		DX9::Colors::BlueViolet,
	//		L"OFF"
	//	);
	//}

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 150.0f),
	//	DX9::Colors::BlueViolet,
	//	L"%d", StatusManager::Instance().GetCombo()
	//);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 170.0f),
	//	DX9::Colors::BlueViolet,
	//	L"%f", StatusManager::Instance().GetTime()
	//);

}