#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/MyAlgorithm/MyAlgorithm.h"
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
			EntryJump();
		}
		else
			action = MOVE;
		break;

	case MOVE:
		action = EXIT;
		//Rotate();
		//Move();
		break;

	case EXIT:
		if (position.z > EXIT_POS) {
			jump_dist = EXIT_DIST;
			EntryJump();
		}
		break;
	}
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

		if (position.y < 0.0f) {
			position.y = 0.0f;
			jump_flag = false;
		}
	}
}

void Slime::Rotate() {
	 if(player_pos.x > position.x)
		 anim_model->SetRotation(0.0f, -45.0f, 0.0f);
	 else
		 anim_model->SetRotation(0.0f,  45.0f, 0.0f);
}

void Slime::Move() {
	if (player_pos.x < position.x)
		position.x -= move_speed * delta;
	else
		position.x += move_speed * delta;
}
