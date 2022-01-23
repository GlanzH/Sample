#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Shielder.h"

void Shielder::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	EnemyBase::LoadAsset(model_name, initial_position);

	col.weapon = col.box;

	//コリジョンモデルの作成
	sword_col = DX9::Model::CreateBox(
		DXTK->Device9,
		col.weapon.Extents.x * 1.5,
		col.weapon.Extents.y * 10,
		col.weapon.Extents.z * 5
	);

	sword_col->SetMaterial(material);
	sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);

	col.weapon.Center = sword_pos;
}

int Shielder::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player, special_attack_flag, thorow_things_flag, deltaTime);

	if (!temporary_death_flag)
		Action();

	//if (Stun() && !LifeDeathDecision())
	//	SetAnimation(anim_model, (int)Motion::CONFUSE, (int)Motion::MAX_MOTION);

	IsDeath();
	AdjustAnimCollision();
	TemporaryDeath(max_death);

	sword_col->SetPosition(sword_pos);
	col.weapon.Center = SimpleMath::Vector3(sword_pos.x, 0, sword_pos.z);
	return 0;
}

void Shielder::Render() {
	anim_model->Draw();
	//collision->Draw();
	//sword_col->Draw();
}

void Shielder::Action() {
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
			Rotate();
			wait_frame = 0.0f;
			move_frame = 0.0f;
			SetAnimation(anim_model, (int)Motion::RUN, (int)Motion::MAX_MOTION);
			action = (int)ActionNum::RUN;
		break;

	case (int)ActionNum::RUN:
		if (move_frame < max_move) {
			move_frame += delta;
			Move();
			Attack();
			LimitRange();
		}
		else {
			action = (int)ActionNum::WAIT;
		}

		break;

	case (int)ActionNum::WAIT:
		if (wait_frame < max_wait) {
			SetAnimation(anim_model, (int)Motion::WAIT, (int)Motion::MAX_MOTION);
			wait_frame += delta;
		}
		else {
			action = (int)ActionNum::INIT;
		}

		sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);

		break;
	}
}

void Shielder::Move() {
	if (direct == RIGHT)
		position.x += move_speed * delta;
	else
		position.x -= move_speed * delta;
}

void Shielder::IsDeath() {
	if (enemy_hp <= 0 && death_frame < max_death) {
		SetAnimation(anim_model, (int)Motion::CONFUSE, (int)Motion::MAX_MOTION);
		death_frame += delta;
	}
}

void Shielder::Rotate() {
	if (player_pos.x > position.x) {
		anim_model->SetRotation(0, -rotate, 0);
		direct = RIGHT;
	}
	else {
		anim_model->SetRotation(0, rotate, 0);
		direct = LEFT;
	}
}

void Shielder::Attack() {
	if (direct == RIGHT)
		sword_pos = SimpleMath::Vector3(position.x + 2.5f, fit_collision_y, position.z);

	if (direct == LEFT)
		sword_pos = SimpleMath::Vector3(position.x - 2.5f, fit_collision_y, position.z);
}

void Shielder::LimitRange() {
	if (position.x <= -limit_x)
		position.x  = -limit_x;

	if (position.x >= limit_x)
		position.x  = limit_x;
}

bool Shielder::LifeDeathDecision() {
	if (temporary_death_flag && DXTK->KeyEvent->pressed.C) {
		return DEAD;
	}

	return LIVE;
}