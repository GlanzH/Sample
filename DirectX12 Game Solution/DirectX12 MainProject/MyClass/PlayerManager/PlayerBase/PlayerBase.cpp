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

	canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

	specialmove_state = SPECIALMOVE::NOMAL_MOVE;

	return 0;
}

void PlayerBase::LoadAssets()
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Player\\chara_motion_v1201_.X");
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

	parry_box = model->GetBoundingBox();

	parry_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		parry_box.Extents.x * parry_box_size_x,
		parry_box.Extents.y * parry_box_size_y,
		parry_box.Extents.z * parry_box_size_z
	);

	parry_box.Center = model->GetPosition();

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	deathbrow_sprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"DeathBrowBG\\deathbrow_bg.png");

	DX12Effect.Initialize();
	DX12Effect.Create(L"Effect\\SwordEffect\\one\\first_attack.efk","first");
	DX12Effect.Create(L"Effect\\SwordEffect\\two\\second_attack.efk","second");
	DX12Effect.Create(L"Effect\\SwordEffect\\three\\third_attack.efk","third");

	//必殺技のエフェクト
	DX12Effect.Create(L"Effect\\DeathBlow_Effect\\deathblow\\deathblow.efk", "deathblow_effect");

	//パリィのエフェクト
	DX12Effect.Create(L"Effect\\Parry_Effect\\parry\\parry.efk", "parry_effect");

}

int PlayerBase::Update(const float deltaTime)
{

	//モデル　アニメーション
	SetAnimation(model, STAND);

	//プレイヤー:移動
	Player_move(deltaTime);

	//プレイヤー:ジャンプ
	Player_jump(deltaTime);


	////プレイヤー:攻撃
	//Player_attack(deltaTime);

	//ランバージャック(移動制限)
	Player_limit();

	//パリィ
	Parry(deltaTime);

	//アピール
	Appeal(deltaTime);

	////必殺技
	//Player_Special_Move(deltaTime);

		//プレイヤーの攻撃(修正)
	Player_Attack_two(deltaTime);




	//無敵時間
	Invincible(deltaTime);

	StatusManager::Instance().Update(deltaTime);



	//攻撃の向き
	if (direction_state_mode == Direction_State::RIGHT) {
		sword_box.Center = model->GetPosition() + SimpleMath::Vector3(7, 0, 0);
		parry_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(3, 6, 0));

	}
	else if (direction_state_mode == Direction_State::LEFT) {
		sword_box.Center = model->GetPosition() + SimpleMath::Vector3(-5, 0, 0);
		parry_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-3, 6, 0));

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
	player_pos = model->GetPosition();
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
	//parry_collision->Draw();
}

void PlayerBase::OnCollisionEnter() {

	//敵に当たったときの処理
	if (!invincible_flag) {
		//model->SetPosition(player_pos.x -= 2.0f, player_pos.y, player_pos.z);
		if (direction_state_mode == Direction_State::RIGHT) {
			model->Move(0, 0, 2.0f);
		}
		else if (direction_state_mode == Direction_State::LEFT) {
			model->Move(0, 0, 2.0f);
		}

		
		//無敵
		invincible_flag = true;

		//sword_box.Center = model->GetPosition() + SimpleMath::Vector3(6, 0, 0);
		//sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(8, 6, 0));

		//box.Center = model->GetPosition();
		//model->SetPosition(player_pos);
		//collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
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
	//パリィカウントを増やす

}

void PlayerBase::Parry(const float deltaTime) {
	if (!parry_flag) {
		if (DXTK->KeyEvent->pressed.P || DXTK->GamePadEvent[0].leftShoulder) {
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
		if(specialmove_state == SPECIALMOVE::NOMAL_MOVE){
			if (appeal_state_mode == Appeal_state::NORMAL || appeal_state_mode == Appeal_state::FOCUS) {
				if (canot_move_state_mode == CANNOT_MOVE_STATE::MOVE) {
					//プレイヤー:移動(キーボード) & ゲームパッド十字キー
					if (DXTK->KeyState->Right || DXTK->GamePadState[0].dpad.right) {
						model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
						model->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);
						sword_box.Center = model->GetRotation();
						direction_state_mode = Direction_State::RIGHT;
						SetAnimation(model, RUN);

					}
					if (DXTK->KeyState->Left || DXTK->GamePadState[0].dpad.left) {
						model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
						model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
						sword_box.Center = model->GetRotation();
						direction_state_mode = Direction_State::LEFT;
						SetAnimation(model, RUN);
					}
				}
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

void PlayerBase::Player_jump(const float deltaTime) {
	//ジャンプ
	if (!parry_flag) {
		if (specialmove_state == SPECIALMOVE::NOMAL_MOVE) {
			if (under_attack_state_mode == UNDER_ATTACK_STATE::NOMAL) {
				if (appeal_state_mode == Appeal_state::NORMAL || appeal_state_mode == Appeal_state::FOCUS) {
					if (!jump_flag_) {
						if (DXTK->KeyEvent->pressed.Space || DXTK->GamePadEvent[0].a) {
							jump_start_flag = true;
							jump_flag_ = true;
							jump_time_ = 0;
							jump_start_v_ = model->Position.y;
						}
					}
				}
			}
		}
	}

	if (jump_start_flag) {
		SetAnimation(model, JUMP);
		jump_start_time += deltaTime;
	}

	if (jump_flag_ && jump_start_time >= jump_start_time_max) {

		jump_time_ += deltaTime;
		auto pos = model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time_ - 0.5f * gravity_ * jump_time_ * jump_time_;
		model->SetPosition(pos);

		if (model->GetPosition().y <= 0.5f) {
			jump_flag_ = false;
			jump_start_flag = false;
			jump_start_time = 0.0f;

		}
	}
}

void PlayerBase::Player_attack(const float deltaTime) {
	//プレイヤー:攻撃
	if (!cool_time_flag_zwei) {
		if (!parry_flag) {
			if (specialmove_state == SPECIALMOVE::NOMAL_MOVE) {
				if (appeal_state_mode == Appeal_state::NORMAL || appeal_state_mode == Appeal_state::FOCUS) {
					if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
						//移動不可
						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;

						//初回攻撃
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
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

	}
	if (motion_time >= motion_time_max[motion_count] || StatusManager::Instance().GetCombo() == 0) {
		motion_time = 0.0f;
		effect_generation_time = 0.0f;
		effect_generation = false;
		motion_count = 0;
		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
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
					DX12Effect.SetPosition("first", Vector3(player_pos.x + 5.0f, player_pos.y + 2.0f, player_pos.z));
					
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("first");
					DX12Effect.SetPosition("first", Vector3(player_pos.x - 7.0f, player_pos.y + 2.0f, player_pos.z));
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
					DX12Effect.SetPosition("second", Vector3(player_pos.x + 4.0f, player_pos.y + 6.0f, player_pos.z));
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("second");
					DX12Effect.SetPosition("second", Vector3(player_pos.x - 4.0f, player_pos.y + 6.0f, player_pos.z));
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
					DX12Effect.SetPosition("third", Vector3(player_pos.x + 7.0f, player_pos.y + 5.0f, player_pos.z));
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("third");
					DX12Effect.SetPosition("third", Vector3(player_pos.x - 7.0f, player_pos.y + 5.0f, player_pos.z));
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

	//if (motion_time >= motion_time_max[motion_count = 1]) {
	//	model->SetTrackPosition(ACT2, 0.0f);
	//}
	//if(motion_time >= motion_time_max[motion_count = 2]){
	//	model->SetTrackPosition(ACT3, 0.0f);

	//}

}

//プレイヤーの攻撃(修正)
void PlayerBase::Player_Attack_two(const float deltaTime) {
	if (!cool_time_flag_zwei) {
		if (!parry_flag) {
			if (specialmove_state == SPECIALMOVE::NOMAL_MOVE) {
				if (appeal_state_mode == Appeal_state::NORMAL || appeal_state_mode == Appeal_state::FOCUS) {

					//1撃目
					if (DXTK->KeyEvent->pressed.J || DXTK->GamePadEvent[0].x) {
						motion_flag_1 = true;
						//移動不可
						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;

					}


					//2撃目
					if (DXTK->KeyEvent->pressed.K || DXTK->GamePadEvent[0].y) {
						motion_flag_2 = true;
						//移動不可
						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;

					}

					//3撃目
					if (DXTK->KeyEvent->pressed.L || DXTK->GamePadEvent[0].b) {
						motion_flag_3 = true;
						//移動不可
						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;

					}

				}
			}
		}
	}


	if (motion_flag_1) {
		effect_generation = true;
		motion_start_time_1 = true;
		motion_count = 0;
		SetAnimation(model, ACT1);
	}

	if (motion_start_time_1) {
		motion_time_1 += deltaTime;
	}

	if (motion_time_1 >= motion_time_max_1) {
		motion_start_time_1 = false;
		motion_time_1 = 0.0f;
		motion_flag_1 = false;

	}



	if (motion_flag_2) {
		effect_generation = true;
		motion_start_time_2 = true;
		motion_count = 1;
		SetAnimation(model, ACT2);
	}

	if (motion_start_time_2) {
		motion_time_2 += deltaTime;
	}

	if (motion_time_2 >= motion_time_max_2) {
		motion_start_time_2 = false;
		motion_time_2 = 0.0f;
		motion_flag_2 = false;
	}


	if (motion_flag_3) {
		effect_generation = true;
		motion_start_time_3 = true;
		motion_count = 2;
		SetAnimation(model, ACT3);
	}

	if (motion_start_time_3) {
		motion_time_3 += deltaTime;
	}

	if (motion_time_3 >= motion_time_max_3) {
		motion_start_time_3 = false;
		motion_time_3 = 0.0f;
		motion_flag_3 = false;

	}



	//エフェクト表示関係
	if (effect_generation == true) {
		effect_generation_time += deltaTime;
	}

	if (effect_generation_time >= effect_generation_time_max[motion_count]) {
		attack_flag = true;
		if (IsAttack()) {
			if (motion_flag_1) {
				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("first");
					DX12Effect.SetPosition("first", Vector3(player_pos.x + 5.0f, player_pos.y + 2.0f, player_pos.z));

				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("first");
					DX12Effect.SetPosition("first", Vector3(player_pos.x - 7.0f, player_pos.y + 2.0f, player_pos.z));
					DX12Effect.SetRotation("first", Vector3(0.0f, 180.0f, 0.0f));
				}
				if (appeal_state_mode != Appeal_state::FOCUS)
					damage = 2;
				if (appeal_state_mode == Appeal_state::FOCUS)
					damage = 2 * 2;
			}
		}
	}


	if (effect_generation_time >= effect_generation_time_max[motion_count]) {
		attack_flag = true;
		if (IsAttack()) {
			if (motion_flag_2) {
				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("second");
					DX12Effect.SetPosition("second", Vector3(player_pos.x + 4.0f, player_pos.y + 6.0f, player_pos.z));
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("second");
					DX12Effect.SetPosition("second", Vector3(player_pos.x - 4.0f, player_pos.y + 6.0f, player_pos.z));
					DX12Effect.SetRotation("second", Vector3(0.0f, 180.0f, 0.0f));

				}

				if (appeal_state_mode != Appeal_state::FOCUS)
					damage = 3;
				if (appeal_state_mode == Appeal_state::FOCUS)
					damage = 3 * 2;
			}
		}
	}

	if (effect_generation_time >= effect_generation_time_max[motion_count]) {
		attack_flag = true;
		if (IsAttack()) {
			if (motion_flag_3) {
				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("third");
					DX12Effect.SetPosition("third", Vector3(player_pos.x + 7.0f, player_pos.y + 5.0f, player_pos.z));
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("third");
					DX12Effect.SetPosition("third", Vector3(player_pos.x - 7.0f, player_pos.y + 5.0f, player_pos.z));
					DX12Effect.SetRotation("third", Vector3(0.0f, 180.0f, 0.0f));

				}
				if (appeal_state_mode != Appeal_state::FOCUS)
					damage = 5;
				if (appeal_state_mode == Appeal_state::FOCUS)
					damage = 5 * 2;
			}
		}
	}

	if (effect_generation_time >= motion_time_max_1 ||
		effect_generation_time >= motion_time_max_2 ||
		effect_generation_time >= motion_time_max_3) {
		effect_generation = false;
		effect_generation_time = 0.0f;
		//移動不可
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

	}
}



void PlayerBase::Player_Special_Move(const float deltaTime) {
	if (!jump_flag_) {
		if (DXTK->KeyEvent->pressed.L || DXTK->GamePadEvent[0].rightShoulder || DXTK->GamePadEvent[0].leftShoulder) {
			specialmove_state = SPECIALMOVE::DEATHBLOW;
		}
	}

	if (specialmove_state == SPECIALMOVE::DEATHBLOW) {
		specialmove_time += deltaTime;
		Blackout_flag = true;

	}

	//暗転
	if (Blackout_flag) {
		Transparency += Blackout;
		if (Transparency >= Blackout_max) {
			Transparency = Blackout_max;
			
		}
	}

	if (specialmove_time >= 2.0f) {
		//attack_flag = true;
		//if (IsAttack()) {
		Blackout_flag = false;
		DX12Effect.PlayOneShot("deathblow_effect");
		DX12Effect.SetPosition("deathblow_effect", Vector3(0, 0, player_pos.z));
		damage = 20;

	}
	//明転
	if (specialmove_time >= 4.0f)
		bright_flag = true;

	if (bright_flag) {
		Transparency -= Ming_Turn;
		if (Transparency <= 0) {
			Transparency = 0;
			bright_flag = false;
		}
	}

	//必殺技終了
	if (specialmove_time >= specialmove_time_max) {
		specialmove_state = SPECIALMOVE::NOMAL_MOVE;
		specialmove_time = 0.0f;
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
		if (DXTK->KeyEvent->pressed.W||DXTK->GamePadEvent[0].leftTrigger) {
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

	DX9::SpriteBatch->DrawSimple(deathbrow_sprite.Get(),
		SimpleMath::Vector3(0, 0, 0),
		nullptr,
		DX9::Colors::RGBA(0, 0, 0, Transparency)
	);

	//if (canot_move_state_mode == CANNOT_MOVE_STATE::MOVE){
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 0.0f),
	//		DX9::Colors::BlueViolet,
	//		L"ON"
	//	);
	//} else {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 0.0f),
	//		DX9::Colors::BlueViolet,
	//		L"OFF"
	//	);
	//}

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 20.0f),
	//	DX9::Colors::BlueViolet,
	//	L"%d", StatusManager::Instance().GetCombo()
	//);

	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 40.0f),
		DX9::Colors::BlueViolet,
		L"%f ", effect_generation_time
	);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 80.0f),
	//	DX9::Colors::BlueViolet,
	//	L"%d", motion_count
	//);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 100.0f),
	//	DX9::Colors::BlueViolet,
	//	L"%f", specialmove_time
	//);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 120.0f),
	//	DX9::Colors::BlueViolet,
	//	L"%d", Transparency
	//);
}