#include "Base/pch.h"
#include "Base/dxtk.h"
#include "StoneStatue.h"

int StoneStatue::Update(DX9::MODEL& ground, PlayerManager* player, const float deltaTime) {
	Move(ground,player,deltaTime);
	SetAnimesion(model, WAIT);

	model->AdvanceTime(deltaTime / 1.0f);
	float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() + SimpleMath::Vector3(0, ground_collision_y, 0), SimpleMath::Vector3::Down, &dist)) {
		model->Move(0.0f, ground_collision_y - dist, 0.0f);
		collision->Move(0.0f, ground_collision_y - dist, 0.0f);
	}

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void StoneStatue::Move(DX9::MODEL& ground, PlayerManager* player, const float deltaTime) {
	float player_pos = player->GetModel()->GetPosition().x;


	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}
