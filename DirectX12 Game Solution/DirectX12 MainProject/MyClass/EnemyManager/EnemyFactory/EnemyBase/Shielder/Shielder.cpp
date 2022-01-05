#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Shielder.h"

bool Shielder::Initialize(std::string tag, bool time_stop_flag, int hp) {
	EnemyBase::Initialize(tag, time_stop_flag, hp);

	return true;
}

int Shielder::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player, special_attack_flag, thorow_things_flag, deltaTime);

	if (!special_attack_flag && !thorow_things_flag)
		Action();

	return 0;
}

void Shielder::Action() {
	switch (action)
	{
	case (int)ActionNum::INIT:
		Rotate();
		SetAnimation(anim_model, (int)Motion::RUN, (int)Motion::MAX_MOTION);
		wait_frame = 0.0f;
		move_frame = 0.0f;
		action = (int)ActionNum::RUN;
		break;

	case (int)ActionNum::RUN:
		if (move_frame < max_move) {
			move_frame += delta;
			Move();
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
		break;
	}
}

void Shielder::Move() {
	if (direct == LIGHT)
		position.x += 40.0f * delta;
	else
		position.x -= 40.0f * delta;
}

void Shielder::Rotate() {
	if (player_pos.x > position.x) {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LIGHT;
	}
	else {
		anim_model->SetRotation(0, rotate, 0);
		direct = LEFT;
	}
}

void Shielder::LimitRange() {
	if (position.x <= -limit_x)
		position.x  = -limit_x;

	if (position.x >= limit_x)
		position.x  = limit_x;
}