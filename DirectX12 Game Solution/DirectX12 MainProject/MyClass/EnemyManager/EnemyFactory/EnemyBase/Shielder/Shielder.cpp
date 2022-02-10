#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Shielder.h"

void Shielder::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	EnemyBase::LoadAsset(model_name, initial_position);

	sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);

	col.weapon.Center = sword_pos;
}

int Shielder::Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime) {
	EnemyBase::NormalDeathEffect(max_dead, confetti_effect_flag, death_effect_flag, effect_count);
	EnemyBase::Update(player, destroy_flag, deltaTime);
	EnemyBase::AdjustAnimCollision();
	EnemyBase::TemporaryDeath();

	Freeze();
	IsDamage();
	IsDeath();

	if (!damage_flag && !temporary_death_flag && !die_flag)
		Action();

	if (is_freeze < max_is_damage && is_damage < max_is_damage)
		anim_model->AdvanceTime(delta / 1.0f);

	//sword_col->SetPosition(sword_pos);
	col.weapon.Center = SimpleMath::Vector3(sword_pos.x, 0, sword_pos.z);
	collision->SetPosition(anim_model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
	return 0;
}

void Shielder::Render() {
	anim_model->Draw();
}

void Shielder::Action() {
	switch (action)
	{
	case (int)ActionNum::FIRST_WAIT:
		InitDirect();
		if (init_wait_frame < max_init_wait) {
			init_wait_frame += delta;
			Rotate();
			SetAnimation(anim_model, (int)Motion::RUN, (int)Motion::MAX_MOTION);
		}
		else {
			action = (int)ActionNum::INIT;
		}
		break;

	case (int)ActionNum::INIT:
		Rotate();
		wait_frame = 0.0f;
		move_frame = 0.0f;
		sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
		SetAnimation(anim_model, (int)Motion::RUN, (int)Motion::MAX_MOTION);
		action = (int)ActionNum::RUN;
		break;

	case (int)ActionNum::RUN:
		if (move_frame < max_move) {
			move_frame += delta;
			Move();
			Attack();
		}
		else {
			action = (int)ActionNum::INIT;
		}

		break;
	}
}

void Shielder::InitDirect() {
	if (enemy_direct == "L") {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LEFT;
	}
	else {
		anim_model->SetRotation(0, rotate, 0);
		direct = RIGHT;
	}
}

void Shielder::Move() {
	if (direct == LEFT)
		position.x += move_speed * delta;

	else if (direct == RIGHT)
		position.x -= move_speed * delta;
}

void Shielder::Freeze() {
	if (enemy_hp <= 0 && !die_flag) {
		is_freeze += delta;
		SetAnimation(anim_model, (int)Motion::DAMAGE, (int)Motion::MAX_MOTION);
	}

	if (StatusManager::Instance().GetHitComboTime() == 0.0f) {
		SetAnimation(anim_model, (int)Motion::RUN, (int)Motion::MAX_MOTION);
		is_freeze = 0.0f;
	}
}

void Shielder::IsDamage() {
	EnemyBase::IsDamage();

	if (damage_flag) {
		is_damage += delta;
		SetAnimation(anim_model, (int)Motion::DAMAGE, (int)Motion::MAX_MOTION);
	}
	else {
		is_damage = 0.0f;
	}
}

void Shielder::HitEffect() {
	if (position.x < player_pos.x && direct == RIGHT ||
		position.x > player_pos.x && direct == LEFT) {
		EnemyBase::HitEffect();
	}
}

void Shielder::IsDeath() {
	if (die_flag) {
		SetAnimation(anim_model, (int)Motion::DEATH, (int)Motion::MAX_MOTION);
		is_freeze = 0.0f;

		if (dead_frame >= 0.0f) {
			confetti_effect_flag = true;
			effect_count = CONFINETTI;
		}

		if (dead_frame >= 1.7f) {
			death_effect_flag = true;
			effect_count = DEATH;
		}
	}
}

void Shielder::Rotate() {
	if (direct == LEFT && position.x >= max_range) {
		anim_model->SetRotation(0, rotate, 0);
		direct = RIGHT;
	}

	if (direct == RIGHT && position.x <= -max_range) {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LEFT;
	}
}

void Shielder::Attack() {
	if (direct == RIGHT)
		sword_pos = SimpleMath::Vector3(position.x + 2.5f, fit_collision_y, position.z);

	if (direct == LEFT)
		sword_pos = SimpleMath::Vector3(position.x - 2.5f, fit_collision_y, position.z);
}

bool Shielder::LifeDeathDecision() {
	if (die_flag && dead_frame > max_dead)
		return DEAD;

	if (StatusManager::Instance().GetTime() == 0.0f)
		return AUTO;

	return LIVE;
}