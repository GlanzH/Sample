#include "PlayerBase.h"


#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerAttack/PlayerAttack.h"

PlayerBase::PlayerBase() {

	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	//攻撃の時間
	attack_flag = false;
	attack_zeit = 0.0f;
	attack_zeit_max = 0.0f;

	cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;
	canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
	direction_state_mode = Direction_State::RIGHT;

	under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;


	//無敵時間
	invincible_flag = false;
	invincible_time = 0.0f;
	invincible_time_max = 0.2f;

	//ジャンプしてるかのフラグ
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;


	//ジャンプタイミング
	jump_start_flag = false;
	jump_start_time = 0.0f;
	jump_start_time_max = 0.0f;

	jump_end_flag = false;


	//アピール
	appeil_flag = false;

	appeil_time = 0.0f;
	appeil_time_max = 0.0f;

	appeil_cool_time = 0.0f;
	appeil_cool_time_max = 0.0f;

	appeil_cool_flag = false;

	//必殺技
	deathbrow_flag = false;//必殺技発動フラグ

	deathbrow_attack = false;//必殺技の当たり判定

	specialmove_time = 0.0f;
	specialmove_time_max = 0.0f;
	//必殺技
	special_attack_flag = false;


	Transparency = 0;
	Blackout = 0;
	Blackout_max = 0;
	Blackout_flag = false;

	//明転
	bright_flag = false;
	Ming_Turn = 0;

	//パリィ
	parry_count = 0.0f;
	parry_flag = false;


	//ダッシュ攻撃
	assault_attack_flag     = false;
	assault_attack_time     = 0.0f;
	assault_attack_time_max = 0.1f;
	assault_flag            = false;


	player_frip_mode = PLAYER_FRIP::NOMAL_MODE;
	flip_flag_ = false;
	flip_time = 0.0f;
	flip_back_time = 0.0f;

}

void PlayerBase::OnDeviceLost() {
	DX12Effect.Reset();
}

bool PlayerBase::Initialize()
{
	//ジャンプしてるかのフラグ
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;

	//ジャンプタイミング
	jump_start_flag = false;
	jump_start_time = 0.0f;
	jump_start_time_max = 0.133f;
	jump_end_flag = false;

	//必殺技
	special_attack_flag = false;

	//攻撃の時間
	attack_flag = false;
	attack_zeit = 0.0f;
	attack_zeit_max = 0.03309f;

	//無敵時間
	invincible_flag = false;
	invincible_time = 0.0f;

	//アピール
	appeil_flag = false;

	appeil_time = 0.0f;
	appeil_time_max = 5.0f;

	appeil_cool_time = 0.0f;
	appeil_cool_time_max = 1.0f;

	appeil_cool_flag = false;

	//必殺技
	deathbrow_flag = false;//必殺技発動フラグ

	deathbrow_attack = false;//必殺技の当たり判定

	specialmove_time = 0.0f;
	specialmove_time_max = 4.0f;


	//暗転
	Transparency = 0;
	Blackout = 15;
	Blackout_max = 255;
	Blackout_flag = false;

	//明転
	bright_flag = false;
	Ming_Turn = 55;


	direction_state_mode = Direction_State::RIGHT;

	under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;

	canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

	cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;


	player_frip_mode = PLAYER_FRIP::NOMAL_MODE;

	//プレイヤーのSE ファイル読み込み
	//攻撃-SE
	first_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE\\Player\\first_attack_se.wav");
	second_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE\\Player\\second_attack_se.wav");
	third_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE\\Player\\third_attack_se.wav");
	return 0;
}

void PlayerBase::LoadAssets()
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Player\\chara_motion_v1207_.X");
	model->SetScale(model_scale);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);

	//プレイヤーの当たり判定
	col.box = model->GetBoundingBox();
	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.box.Extents.x * player_box_size_x,
		col.box.Extents.y * player_box_size_y,
		col.box.Extents.z * player_box_size_z
	);
	collision->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);

	material.Diffuse  = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient  = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	collision->SetMaterial(material); 


	col.sword_box = model->GetBoundingBox();
	col.sword_box.Extents = SimpleMath::Vector3(col.sword_box.Extents) * 7.0f;
	sword_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.sword_box.Extents.x * box_size_x,
		col.sword_box.Extents.y * box_size_y,
		col.sword_box.Extents.z * box_size_z
	);


	//フォント
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	deathbrow_sprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"DeathBrowBG\\deathbrow_bg.png");

	//エフェクト　ファイル読み込み
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



	//ランバージャック(移動制限)
	Player_limit();

	////パリィ
	//Parry(deltaTime);

	//アピール
	//Appeal(deltaTime);

	//必殺技
	Player_Special_Move(deltaTime);


	//プレイヤーの攻撃(ダッシュ攻撃)
	Player_Attack_Three(deltaTime);

	//無敵時間
	Invincible(deltaTime);

	StatusManager::Instance().Update(deltaTime);



	//攻撃の向き
	if (direction_state_mode == Direction_State::RIGHT) {
		col.sword_box.Center = model->GetPosition() + SimpleMath::Vector3(9.5, 3, 0);
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(6.5, 5, 0));

	}
	else if (direction_state_mode == Direction_State::LEFT) {
		col.sword_box.Center = model->GetPosition() + SimpleMath::Vector3(-9.5, 3, 0);
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-6.5, 5, 0));

	}

	//攻撃判定の時間
	if (attack_flag)
		attack_zeit += deltaTime;
	if (attack_zeit >= attack_zeit_max) {
		attack_flag = false;
		attack_zeit = 0.0f;
	}

	col.box.Center = model->GetPosition();
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
		//無敵
		invincible_flag = true;
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

	if (invincible_flag) {
		SetAnimation(model, DAMAGE);
		if (direction_state_mode == Direction_State::RIGHT) {
			model->Move(0, 0, 30.0f * deltaTime);
		}
		else if (direction_state_mode == Direction_State::LEFT) {
			model->Move(0, 0, 30.0f * deltaTime);
		}
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
	if (!invincible_flag) {
		if(!deathbrow_flag){
			if (!appeil_flag) {
				if (canot_move_state_mode == CANNOT_MOVE_STATE::MOVE) {

					//プレイヤー:移動(キーボード) & ゲームパッド十字キー
					if (DXTK->KeyState->Right || DXTK->GamePadState[0].dpad.right) {
						model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
						model->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);
						col.sword_box.Center = model->GetRotation();
						direction_state_mode = Direction_State::RIGHT;
						SetAnimation(model, RUN);
					}
					if (DXTK->KeyState->Left || DXTK->GamePadState[0].dpad.left) {
						model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
						model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
						col.sword_box.Center = model->GetRotation();
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
	if (!invincible_flag) {
		if (!deathbrow_flag) {
			if (under_attack_state_mode == UNDER_ATTACK_STATE::NOMAL) {
				if (!appeil_flag) {
					if (!jump_flag_) {
						if (DXTK->KeyEvent->pressed.Space || DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
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

		if (model->GetPosition().y <= 0.65f) {
			jump_flag_ = false;
			jump_start_flag = false;
			jump_start_time = 0.0f;
			model->SetTrackPosition(JUMP, 0.0);
		}
	}
}

//プレイヤーの攻撃(弱攻撃・強攻撃・突撃攻撃) 変更(3回目)
void PlayerBase::Player_Attack_Three(const float deltaTime) {

	if (DXTK->KeyState->A||DXTK->GamePadState[0].buttons.b) {
		assault_attack_time += 100.0f * deltaTime;
		assault_attack_flag = true;
		canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
		SetAnimation(model, APPEIL);
	}
	else
	{
		if (assault_attack_flag) {
			SetAnimation(model, ACT3);
			model->Move(0.0f, 0.0f, -100.0f * deltaTime);
			assault_attack_time -= 100.0f * deltaTime;
			assault_flag = true;
		}
	}


	if (assault_attack_time <= 0.0f) {
		assault_attack_flag = false;
		assault_flag = false;
		assault_attack_time = 0.0f;
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
	}

	if (assault_attack_time <= 0.0f) {
		assault_attack_time = 0.0f;
	}
	if (assault_attack_time >= 150.0f) {
		assault_attack_time = 150.0f;
	}

	//弾く(試験用)
	if (DXTK->KeyEvent->pressed.S) {
		player_frip_mode = PLAYER_FRIP::ATTACK_MODE;
	}


	if (player_frip_mode == PLAYER_FRIP::ATTACK_MODE) {
		SetAnimation(model, ACT1);
		attack_flag = true;
	}
	if (IsAttack()) {
		flip_time += deltaTime;
		if (flip_time >= 0.4f) {
			player_frip_mode = PLAYER_FRIP::FRIP;
			model->SetTrackPosition(ACT1, 0.0);
			flip_time = 0.0f;
			damage = 10000;
		}
	}


	if (player_frip_mode == PLAYER_FRIP::FRIP) {
		//SetAnimation(model, DAMAGE);
		//model->Move(0.0f, 0.0f, 50.0f * deltaTime);
		flip_back_time += deltaTime;
		if (flip_back_time >= 0.15f) {
			player_frip_mode = PLAYER_FRIP::NOMAL_MODE;
			flip_back_time = 0.0f;
		}
	}
}

void PlayerBase::Player_Special_Move(const float deltaTime) {
	if (!jump_flag_) {
		if (!appeil_flag ) {
			if (StatusManager::Instance().ReturnHeart() >= 20) {
				if (DXTK->KeyEvent->pressed.L || DXTK->GamePadEvent->rightShoulder == GamePad::ButtonStateTracker::PRESSED) {
					deathbrow_flag = true;
				}
			}
		}
	}

	if (deathbrow_flag) {
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

	if (specialmove_time >= 0.1f) {
		deathbrow_attack = true;

		Blackout_flag = false;
		DX12Effect.PlayOneShot("deathblow_effect", Vector3(player_pos.x, 10, 0));


	}
	//明転
	if (specialmove_time >= 3.666f)
		bright_flag = true;

	if (bright_flag) {
		Transparency -= Ming_Turn;
		if (Transparency <= 0) {
			Transparency = 0;

			bright_flag = false;

		}
	}

	if (specialmove_time >= 3.9f && !special_attack_flag)
		special_attack_flag = true;

	//必殺技終了
	if (specialmove_time >= specialmove_time_max) {
		deathbrow_flag = false;
		special_attack_flag = false;
		specialmove_time = 0.0f;

		deathbrow_attack = false;

		//必殺技ゲージリセット呼び出し
		StatusManager::Instance().HeartReset();
	}

}

bool PlayerBase::IsAttack() {

	if (attack_flag || assault_flag) {


		return true;
	}
	return false;
}

//弾かれるフラグ
bool PlayerBase::IsFlip() {
	if (flip_flag_) {
		return true;
	}
	return false;
}


//弾かれた時の処理
void PlayerBase::OnFlipEnetr() {

}


	//アピール
void PlayerBase::Appeal(const float deltaTime)
{
	//アピール
	if (!jump_flag_) {
		if (!deathbrow_flag) {
			if (!appeil_cool_flag) {
				if (DXTK->KeyState->W || DXTK->GamePadState->triggers.left) {
					appeil_flag = true;
				}
				else
				{
					appeil_flag = false;

					model->SetTrackPosition(APPEIL, 0.0);

					if (!appeil_flag) {
						appeil_cool_flag = true;
					}

					if (direction_state_mode == Direction_State::LEFT) {
						model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
					}

				}
			}
		}
	}

	if (appeil_flag) {
		if (direction_state_mode == Direction_State::RIGHT) {
			SetAnimation(model, APPEIL);
		}
		else if (direction_state_mode == Direction_State::LEFT)
		{
			SetAnimation(model, APPEIL);
			model->SetRotation(Vector3(0.0f, XMConvertToRadians(-90.0f), 0.0f));
		}

		appeil_time += deltaTime;
	}

	if (appeil_time >= appeil_time_max) {//ボタン話したときもNOMALに戻す
		appeil_flag = false;
		model->SetTrackPosition(APPEIL, 0.0);
		appeil_cool_flag = true;


		if (direction_state_mode == Direction_State::LEFT) {
			model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
		}
	}

	if (appeil_cool_flag) {
		appeil_cool_time += deltaTime;
	}

	if (appeil_cool_time >= appeil_cool_time_max) {
		appeil_cool_flag = false;
		appeil_cool_time = 0.0f;
		appeil_time = 0.0f;
	}
}


void PlayerBase::BrackImage() {
	DX9::SpriteBatch->DrawSimple(deathbrow_sprite.Get(),
		SimpleMath::Vector3(0, 0, 0),
		nullptr,
		DX9::Colors::RGBA(0, 0, 0, Transparency)
	);

}

void PlayerBase::_2DRender() {
	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 120.0f),
		DX9::Colors::BlueViolet,
		L"突き攻撃のパワー %f", assault_attack_time
	);

	//if (player_frip_mode == PLAYER_FRIP::NOMAL_MODE) {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 140.0f),
	//		DX9::Colors::WhiteSmoke,
	//		L"NOMAL", player_frip_mode
	//	);
	//}
	//else if (player_frip_mode == PLAYER_FRIP::ATTACK_MODE) {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 140.0f),
	//		DX9::Colors::WhiteSmoke,
	//		L"ATTACK", player_frip_mode
	//	);
	//}
	//else
	//{
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 140.0f),
	//		DX9::Colors::WhiteSmoke,
	//		L"FLIP", player_frip_mode
	//	);
	//}
}
