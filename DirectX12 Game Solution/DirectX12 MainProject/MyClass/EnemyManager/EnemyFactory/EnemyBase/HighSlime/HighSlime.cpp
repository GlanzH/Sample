#include "Base/pch.h"
#include "Base/dxtk.h"
#include "HighSlime.h"

HighSlime::HighSlime()
{
}

bool HighSlime::Initialize()
{
   
    return false;
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

void HighSlime::Move() {
    if (player_pos.x < position.x)
        position.x -= move_speed * delta;
    else
        position.x += move_speed * delta;
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
		if (position.z > EXIT_POS) {
			jump_dist = EXIT_DIST;
			EntryExitJump();
		}
		break;
	}
}

void HighSlime::Rotate() {
	const float rotate = 45.0f;

	if (player_pos.x > position.x)
		anim_model->SetRotation(0.0f, -rotate, 0.0f);
	else
		anim_model->SetRotation(0.0f, rotate, 0.0f);
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
		position.y = position.y + (exit_jump_speed * jump_time * jump_power * gravity * jump_time * jump_time * delta);

		if (position.y < 0.0f) {
			position.y = 0.0f;
			jump_flag = false;
		}
	}
}

void HighSlime::ExitRotate() {
	position.y = 0.0f;
	const float rotate_speed = 1.0f;

	SetAnimation(anim_model, EXIT_JUMP);
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
