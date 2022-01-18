#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SwordMan.h"

void SwordMan::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	EnemyBase::LoadAsset(model_name, initial_position);

	col.weapon = col.box;

	//コリジョンモデルの作成
	sword_col = DX9::Model::CreateBox(
		DXTK->Device9,
		col.weapon.Extents.x * 3,
		col.weapon.Extents.y * 5,
		col.weapon.Extents.z * 5
	);

	sword_col->SetMaterial(material);
	sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);

	col.weapon.Center = sword_pos;
}

int SwordMan::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player, special_attack_flag, thorow_things_flag, deltaTime);

	if (!temporary_death_flag)
		Action();

	//if (Stun() && !LifeDeathDecision())
	//	SetAnimation(anim_model, (int)Motion::CONFUSE, (int)Motion::MAX_MOTION);

	IsDeath();
	AdjustAnimCollision();
	TemporaryDeath(max_death);

	sword_col->SetPosition(sword_pos);
	col.weapon.Center = SimpleMath::Vector3(sword_pos.x,0,sword_pos.z);
	return 0;
}

void SwordMan::Render() {
	anim_model->Draw();
	//collision->Draw();
	//sword_col->Draw();
}

void SwordMan::Action() {

	switch (action)
	{
	case (int)ActionNum::FIRST_WAIT:
		if (init_wait_frame < max_init_wait) {
			init_wait_frame += delta;
			Rotate();
			SetAnimation(anim_model, (int)Motion::WAIT, (int)Motion::MAX_MOTION);
		}
		else {
			action = (int)ActionNum::INIT;
		}
		break;

	case (int)ActionNum::INIT:
			wait_frame = 0.0f;
			attack_frame = 0.0f;
			move_pos_x = player_pos.x;
			SetAnimation(anim_model, (int)Motion::WALK, (int)Motion::MAX_MOTION);
			action = (int)ActionNum::MOVE;
		break;

	case (int)ActionNum::MOVE:

		//!移動終了条件(プレイヤーがいた座標に到着したら)
		end_move = position.x > player_pos.x && position.x - 0.5f < move_pos_x ||
			       position.x < player_pos.x && position.x + 0.5f > move_pos_x;

		if(end_move)
			action = (int)ActionNum::ATTACK;
		else {
			Move();
			Rotate();
		}
		break;

	case (int)ActionNum::ATTACK:
		Rotate();
		Attack();

		if (attack_frame < max_attack) {
			SetAnimation(anim_model, (int)Motion::ATTACK, (int)Motion::MAX_MOTION);
			attack_frame += delta;
		}
		else {
			action = (int)ActionNum::WAIT;
		}
		break;

	case (int)ActionNum::WAIT:
		if (wait_frame < max_wait) {
			SetAnimation(anim_model, (int)Motion::WAIT,(int)Motion::MAX_MOTION);
			wait_frame += delta;
		}
		else {
			action = (int)ActionNum::INIT;
		}

		break;
	}
}

void SwordMan::Move() {
	if (move_pos_x < position.x)
		position.x -= move_speed * delta;

	if (move_pos_x > position.x)
		position.x += move_speed * delta;
}

void SwordMan::IsDeath() {
	if (enemy_hp <= 0 && death_frame < max_death) {
		SetAnimation(anim_model, (int)Motion::CONFUSE, (int)Motion::MAX_MOTION);
		death_frame += delta;
	}
}

void SwordMan::Rotate() {
	if (player_pos.x > position.x) {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LIGHT;
	}
	else {
		anim_model->SetRotation(0, rotate, 0);
		direct = LEFT;
	}
}

void SwordMan::Attack() {
	if (direct == LIGHT && attack_frame >= 0.8f)
		sword_pos = SimpleMath::Vector3(position.x + 3.5f,fit_collision_y,position.z);

	if (direct == LEFT && attack_frame >= 0.8f)
		sword_pos = SimpleMath::Vector3(position.x - 3.5f, fit_collision_y, position.z);

	if(attack_frame >= max_attack)
		sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
}

bool SwordMan::LifeDeathDecision() {
	if (temporary_death_flag && DXTK->KeyEvent->pressed.C) {
		return DEAD;
	}
    
	return LIVE;
}