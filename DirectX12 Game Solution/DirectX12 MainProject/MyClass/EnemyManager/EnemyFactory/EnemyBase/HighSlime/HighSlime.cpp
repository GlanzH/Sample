#include "Base/pch.h"
#include "Base/dxtk.h"
#include "HighSlime.h"

int HighSlime::Update(PlayerManager* player, const float deltaTime) 
{
	
	Jump(player,deltaTime);
	//SetAnimesion(model, WAIT);

	//model->AdvanceTime(deltaTime / 1.0f);

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void HighSlime::Jump(PlayerManager* player, const float deltaTime)
{
	
	float player_pos = player->GetModel()->GetPosition().x;
		count++;
		if (count >= 15)
		{
			position.x -= enemy_speed.x * deltaTime;
		}	
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
	if (jump_flag)
	{
		jump_time += deltaTime;
		position.y= jump_start_y + gravity * jump_time - deltaTime * gravity * jump_time * jump_time;
		if (model->GetPosition().y <= 0.5f) 
		{
			jump_flag = false;
		}
	}
	box.Center = model->GetPosition();
	model->SetPosition(position);
}
