#include "Base/pch.h"
#include "Base/dxtk.h"
#include "HighSlime.h"

HighSlime::HighSlime()
{
}

int HighSlime::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime)
{
    EnemyBase::Update(player,special_attack_flag,thorow_things_flag, deltaTime);

	delta = deltaTime;
	player_pos = player;

	if (!special_attack_flag && !thorow_things_flag)
	Action();

	return 0;
}

void HighSlime::Action() {
	switch (action) {
	case ENTRY:
		if (position.z > ENTRY_POS) {
			jump_dist = ENTRY_DIST;
			EntryExitJump();
		}
		else
			action = MOVE;
		break;

	case MOVE:
		is_move_frame += delta;

		if (is_move_frame < max_is_move) {
			if (!EnemyBase::IsDamage()) {
				InitDirection();
				ChangeDirection();
				Move();
				Rotate();
			}
			Jump();
		}
		else {
			ExitRotate();
		}
		break;

	case EXIT:
		if (position.z >= EXIT_POS) {
			jump_dist = EXIT_DIST;
			EntryExitJump();
		}
		break;
	}
}

void HighSlime::Move() {
	if (move_direct == MOVE_LEFT)
		position.x -= move_speed * delta;
	else
		position.x += move_speed * delta;
}

void HighSlime::InitDirection() {
	if (!init_direct_flag) {
		if (position.x > 0)
			move_direct = MOVE_LEFT;
		else
			move_direct = MOVE_RIGHT;

		init_direct_flag = true;
	}
}

void HighSlime::ChangeDirection() {
	 if (position.x >= 60)
		move_direct = MOVE_LEFT;
else if (position.x <= -60)
		move_direct = MOVE_RIGHT;
}

void HighSlime::Rotate() {
	const float rotate = 45.0f;

	if (move_direct == MOVE_LEFT)
		anim_model->SetRotation(0.0f, rotate, 0.0f);
	else
		anim_model->SetRotation(0.0f, -rotate, 0.0f);
}

void HighSlime::EntryExitJump() {

	if (!jump_flag) {
		jump_time = 0;
		jump_flag = true;
	}
	else {
		position.z -= jump_dist * delta;
		jump_time += delta;
		position.y += exit_jump_speed * delta;
		position.y = position.y + (exit_jump_speed * jump_time * exit_jump_power * gravity * jump_time * jump_time * delta);

		switch (action) {
		case ENTRY:
			if (position.y < 0.0f) {
				position.y = 0.0f;
				jump_flag = false;
			}
			break;

		case EXIT:
			if (position.y < -20.0f) {
				position.y = -20.0f;
				jump_flag = false;
			}
			break;
		}
	}
}

void HighSlime::ExitRotate() {
	position.y = 0.0f;
	const float rotate_speed = 1.0f;

	//SetAnimation(anim_model, EXIT_JUMP);
	anim_model->AdvanceTime(delta / 1.0f);

	if (anim_model->GetRotation().z > 0)
		anim_model->Rotate(0, -rotate_speed * delta, 0);
	else
		anim_model->Rotate(0, rotate_speed * delta, 0);

	if (exit_frame < max_exit)
		exit_frame += delta;
	else
		action = EXIT;
}

void HighSlime::Jump()
{
    if (!jump_flag) {
        jump_time = 0;
        jump_flag = true;
    }
    else{
        jump_time  += delta;
        position.y += jump_speed * delta;
        position.y  = position.y + (jump_speed * jump_time * jump_power * gravity * jump_time * jump_time * delta);
    }

	if (position.y < 0.0f || EnemyBase::IsDamage()) {
		position.y = 0.0f;
		jump_flag = false;
	}
}
