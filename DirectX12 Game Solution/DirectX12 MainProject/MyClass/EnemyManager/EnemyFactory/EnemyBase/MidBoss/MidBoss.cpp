#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MidBoss.h"

bool MidBoss::Initialize(std::string tag, bool time_stop_flag, int hp) {
	EnemyBase::Initialize(tag, time_stop_flag, hp);

	return true;
}

int MidBoss::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player, special_attack_flag, thorow_things_flag, deltaTime);

	//!通常時処理
	auto normal_state = !special_attack_flag && !thorow_things_flag && !Stun() && !IsDamage() && !LifeDeathDecision();

	if (normal_state)
		Action();

	if (Stun() && !LifeDeathDecision())
		SetAnimation(anim_model, (int)Motion::CONFUSE, (int)Motion::MAX_MOTION);


	IsDamage();
	IsDeath();

	AdjustAnimCollision();
	return 0;
}
void MidBoss::Action() {

	switch (action)
	{
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
			position.x < player_pos.x&& position.x + 0.5f > move_pos_x;

		if (end_move)
			action = (int)ActionNum::ATTACK;
		else {
			Move();
			Rotate();
		}
		break;

	case (int)ActionNum::ATTACK:
		Rotate();

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
			SetAnimation(anim_model, (int)Motion::WAIT, (int)Motion::MAX_MOTION);
			wait_frame += delta;
		}
		else {
			action = (int)ActionNum::INIT;
		}

		break;
	}
}

void MidBoss::Move() {
	if (move_pos_x < position.x)
		position.x -= 35.0f * delta;

	if (move_pos_x > position.x)
		position.x += 35.0f * delta;
}

void MidBoss::Rotate() {
	if (player_pos.x > position.x) {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LIGHT;
	}
	else {
		anim_model->SetRotation(0, rotate, 0);
		direct = LEFT;
	}
}

void MidBoss::Damage() {
	EnemyBase::Damage();
	damage_flag = true;
}

bool MidBoss::IsDamage() {
	if (damage_flag && enemy_hp > 1 && damage_frame < max_damage) {
		SetAnimation(anim_model, (int)Motion::DAMAGE, (int)Motion::MAX_MOTION);
		damage_frame += delta;
		return true;
	}
	else {
		damage_frame = 0.0f;
		damage_flag = false;
		return false;
	}
}

void MidBoss::IsDeath() {
	if (enemy_hp <= 0 && death_frame < max_death) {
		SetAnimation(anim_model, (int)Motion::DEATH, (int)Motion::MAX_MOTION);
		death_frame += delta;
	}
}

bool MidBoss::LifeDeathDecision() {
  if (enemy_hp <= 0 && death_frame > max_death)
  		return DEAD;

	return LIVE;
}