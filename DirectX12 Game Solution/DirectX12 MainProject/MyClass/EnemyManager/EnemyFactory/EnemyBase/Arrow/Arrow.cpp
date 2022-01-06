#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Arrow.h"

bool Arrow::Initialize(std::string tag, bool time_stop_flag, int hp) {
	EnemyBase::Initialize(tag, time_stop_flag, hp);

	return true;
}

int Arrow::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player, special_attack_flag, thorow_things_flag, deltaTime);

	if (!special_attack_flag && !thorow_things_flag)
		Action();

	col.box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition());

	return 0;
}

void Arrow::Action() {
	switch (action)
	{
	case WAIT:
		Rotate();
		shot_pos = player_pos;
		action = SHOT;
		break;

	case SHOT:
		if (init_pos.x == 0.0f)
			init_pos.x = 0.0000001f;

		float dist  = SimpleMath::Vector3::Distance(SimpleMath::Vector3(shot_pos.x,0,0), position);
		float speed = init_pos.x * distance_adjust_speed;

		position.x -= (dist / (init_pos.y * distance_adjust_y)) * speed * delta;
		position.y -= (dist / (init_pos.x * distance_adjust_y)) * speed * delta;

		break;
	}
}

void Arrow::Move() {

}

void Arrow::Rotate() {
	float rot = (Atan2((-player_pos.y - position.y),(player_pos.x - position.x)) / 57.0f);

	model->SetRotation(0,0,rot);
	collision->SetRotation(0, 0, rot);
}

float Arrow::Atan2(float y,float x) {
     float arc_tan2 = atan2f(y, x) * (180.0f / pi);
	return arc_tan2;
}
