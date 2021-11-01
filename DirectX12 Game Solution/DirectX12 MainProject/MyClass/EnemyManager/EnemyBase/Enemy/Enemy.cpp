#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Enemy.h"

int Enemy::Update(DX9::MODEL& ground, const float deltaTime) {
	Move(ground, deltaTime);

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void Enemy::Move(DX9::MODEL& ground, const float deltaTime) {
	float player_pos = PlayerManager::Instance().GetModel()->GetPosition().x;

	float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() + SimpleMath::Vector3(0, ground_collision_y, 0), SimpleMath::Vector3::Down, &dist)) {
		model->Move(0.0f, ground_collision_y - dist, 0.0f);
	}

	if (player_pos < position.x - stop_enemy_pos || player_pos > position.x + stop_enemy_pos) {
		count = 0;
		position.x -= enemy_speed.x * deltaTime;
	}
	else {
		if (count > stop_count) {
			position.x -= enemy_speed.x * accel_num * deltaTime;
		}
		else
			count++;
	}

	model->SetPosition(position);
	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));

}