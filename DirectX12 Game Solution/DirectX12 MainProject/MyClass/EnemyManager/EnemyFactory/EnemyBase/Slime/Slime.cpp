#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Slime.h"




bool Slime::Initialize()
{
	/*Damage(deleteTime/damage):*/
	return true;
}

int Slime::Update(PlayerManager* player, const float deltaTime) {
	Move(player,deltaTime);
	/*SetAnimesion(model, WAIT);*/

	/*model->AdvanceTime(deltaTime / 1.0f);*/

	if (enemy_hp < 0)
		return DEAD;
   
	return LIVE;
}

void Slime::Move(PlayerManager* player, const float deltaTime) {
	float player_pos = player->GetModel()->GetPosition().x;

	/*if (player_pos < position.x - stop_enemy_pos || player_pos > position.x + stop_enemy_pos) {
		count = 0;
		position.x -= enemy_speed.x * deltaTime;
	}
	else {
		if (count > stop_count) {
			position.x -= enemy_speed.x * accel_num * deltaTime;
		}
		else
			count++;
	}*/
	
		count++;
		if (count >= 15)
		{
			position.x -= enemy_speed.x * deltaTime;

		}	
	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}
