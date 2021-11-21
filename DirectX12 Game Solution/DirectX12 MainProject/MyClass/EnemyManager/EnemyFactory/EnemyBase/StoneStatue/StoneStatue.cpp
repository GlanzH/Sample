#include "Base/pch.h"
#include "Base/dxtk.h"
#include "StoneStatue.h"

int StoneStatue::Update(PlayerManager* player, const float deltaTime) {
	Move(player,deltaTime);
	SetAnimesion(model, WAIT);

	model->AdvanceTime(deltaTime / 1.0f);

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void StoneStatue::Move(PlayerManager* player, const float deltaTime) {
	float player_pos = player->GetModel()->GetPosition().x;

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}
