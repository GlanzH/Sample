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
	position.x -= enemy_speed.x * deltaTime;

	//’nŒ`‚Ì“–‚½‚è”»’è
	float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() + SimpleMath::Vector3(0, 100, 0), SimpleMath::Vector3::Down, &dist)) {
		model->Move(0.0f, 100 - dist, 0.0f);
	}

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
}