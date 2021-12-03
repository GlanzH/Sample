#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Slime.h"

int Slime::Update(SimpleMath::Vector3 player, const float deltaTime) {
	EnemyBase::Update(player, deltaTime);

	delta      = deltaTime;
	player_pos = player;

	Action();

   
	return 0;
}

void Slime::Action() {
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
				Rotate();
				Move();
			}
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

void Slime::Rotate() {
	const float rotate = 45.0f;

	if (player_pos.x > position.x)
		anim_model->SetRotation(0.0f, -rotate, 0.0f);
	else
		anim_model->SetRotation(0.0f,  rotate, 0.0f);
}

void Slime::Move() {
	if (player_pos.x < position.x)
		position.x -= move_speed * delta;
	else
		position.x += move_speed * delta;
}

void Slime::EntryExitJump() {

	if (!jump_flag) {
		jump_time = 0;
		jump_flag = true;
	}
	else {
		position.z -= jump_dist * delta;
		jump_time += delta;
		position.y += jump_speed * delta;
		position.y = position.y + (jump_speed * jump_time * jump_power * gravity * jump_time * jump_time * delta);

		if (position.y < 0.0f) {
			position.y = 0.0f;
			jump_flag = false;
		}
	}
}

void Slime::ExitRotate() {
	const float rotate_speed = 1.0f;
	if (anim_model->GetRotation().z > 0)
		anim_model->Rotate(0, -rotate_speed * delta, 0);
	else
		anim_model->Rotate(0, rotate_speed * delta, 0);
	
	if (exit_frame < max_exit)
		exit_frame += delta;
	else
		action = EXIT;
}
