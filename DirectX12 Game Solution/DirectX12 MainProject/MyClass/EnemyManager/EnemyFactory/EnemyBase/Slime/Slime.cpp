#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Slime.h"

int Slime::Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime) {
	EnemyBase::Update(player,destroy_flag, deltaTime);

	delta      = deltaTime;
	player_pos = player;

	if (!die_flag)
		Action();

	return 0;
}

void Slime::Action() {
	switch (action) {
	case ENTRY:
		if (position.z > ENTRY_POS) {
			jump_dist = ENTRY_DIST;
			EntryJump();
		}
		else
			action = MOVE;
		break;

	case MOVE:
		is_move_frame += delta;

		if (is_move_frame < max_is_move) {
			InitDirection();
			ChangeDirection();
			Rotate();
			Move();
		}
		break;
	}
}

void Slime::InitDirection() {
	if (!init_direct_flag) {
		if (position.x > 0)
			move_direct = MOVE_LEFT;
		else
			move_direct = MOVE_RIGHT;

		init_direct_flag = true;
	}
}

void Slime::ChangeDirection() {
	if (position.x >=  60)
		move_direct = MOVE_LEFT;
else if(position.x <= -60)
		move_direct = MOVE_RIGHT;
}

void Slime::Rotate() {
	const float rotate = 45.0f;

	if (move_direct == MOVE_LEFT)
		anim_model->SetRotation(0.0f,rotate, 0.0f);
	else
		anim_model->SetRotation(0.0f,-rotate, 0.0f);
}

void Slime::Move() {
	if (move_direct == MOVE_LEFT)
		position.x -= move_speed * delta;
	else
		position.x += move_speed * delta;
}

void Slime::EntryJump() {

	if (!jump_flag) {
		jump_time = 0;
		jump_flag = true;
	}
	else {
		position.z -= jump_dist * delta;
		jump_time += delta;
		position.y += jump_speed * delta;
		position.y = position.y + (jump_speed * jump_time * jump_power * gravity * jump_time * jump_time * delta);

		switch (action) {
		case ENTRY:
			if (position.y < 0.0f) {
				position.y = 0.0f;
				jump_flag = false;
			}
			break;
		}
	}
}
