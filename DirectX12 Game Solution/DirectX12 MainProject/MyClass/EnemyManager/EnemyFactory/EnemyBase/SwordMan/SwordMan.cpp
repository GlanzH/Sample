#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SwordMan.h"

void SwordMan::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	EnemyBase::LoadAsset(model_name, initial_position);

	col.weapon = col.box;

	//�R���W�������f���̍쐬
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
	sword_col->Draw();
}

void SwordMan::Action() {

	switch (action)
	{
	case (int)ActionNum::FIRST_WAIT:
		InitDirect();

		if (init_wait_frame < max_init_wait) {
			init_wait_frame += delta;
			SetAnimation(anim_model, (int)Motion::WAIT, (int)Motion::MAX_MOTION);
		}
		else {
			action = (int)ActionNum::INIT;
		}
		break;

	case (int)ActionNum::INIT:
		attack_frame = 0.0f;
		move_pos_x = player_pos.x;
		SetAnimation(anim_model, (int)Motion::WALK, (int)Motion::MAX_MOTION);
		action = (int)ActionNum::MOVE;
		break;

	case (int)ActionNum::MOVE:

		//!�ړ��I������(�v���C���[���������W�ɓ���������)
		end_move = position.x > player_pos.x && position.x - 0.5f < move_pos_x ||
			position.x < player_pos.x&& position.x + 0.5f > move_pos_x;

		if (end_move)
			action = (int)ActionNum::ATTACK;
		else {
			Move();
			Rotate();
		}
		break;

	case (int)ActionNum::ATTACK:
		Attack();

		if (attack_frame < max_attack) {
			SetAnimation(anim_model, (int)Motion::ATTACK, (int)Motion::MAX_MOTION);
			attack_frame += delta;
			attack_flag = true;
		}
		else {
			attack_flag = false;
			action = (int)ActionNum::INIT;
		}
		break;
	}
}

void SwordMan::InitDirect() {
	if (enemy_direct == "L") {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LEFT;
	}
	else {
		anim_model->SetRotation(0, rotate, 0);
		direct = RIGHT;
	}
}

void SwordMan::Move() {
	if (direct == LEFT)
		position.x += move_speed * delta;

	else if(direct == RIGHT)
		position.x -= move_speed * delta;
}

void SwordMan::Rotate() {
	if (direct == LEFT && position.x >= max_range) {
		anim_model->SetRotation(0, rotate, 0);
		direct = RIGHT;
	}

	if (direct == RIGHT && position.x <= -max_range) {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LEFT;
	}
}

void SwordMan::IsRetreat() {
	EnemyBase::IsRetreat();

	if(enemy_hp > 0 && retreat_flag)
	SetAnimation(anim_model, (int)Motion::DAMAGE, (int)Motion::MAX_MOTION);
}

void SwordMan::IsDeath() {
	if (enemy_hp <= 0 && death_frame < max_death || DXTK->KeyEvent->pressed.A) {
		SetAnimation(anim_model, (int)Motion::CONFUSE, (int)Motion::MAX_MOTION);
		death_frame += delta;
		enemy_hp = 0;
	}
}

void SwordMan::Attack() {
	if (direct == LEFT) {
		if (attack_frame >= 0.8f)
			sword_pos = SimpleMath::Vector3(position.x + 5.0f, fit_collision_y, position.z);
	}
	else {
		if (attack_frame >= 0.8f)
			sword_pos = SimpleMath::Vector3(position.x - 5.0f, fit_collision_y, position.z);
	}

	if(attack_frame >= max_attack)
		sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
}

bool SwordMan::LifeDeathDecision() {
	if (temporary_death_flag && death_frame > max_death)
		return DEAD;

	if (StatusManager::Instance().GetTime() == 0.0f)
		return AUTO;
    
	return LIVE;
}