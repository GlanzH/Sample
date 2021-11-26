#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

bool FakerLamiel::Initialize(SimpleMath::Vector3 speed, int hp) {
	EnemyBase::Initialize(speed,hp);
	DX12Effect.Create(L"Effect/thunder/thunder.efk", "thunder");
	attack_method = DOWN;
	init_pos = position;
	count = 0;
	return true;
}

int FakerLamiel::Update( PlayerBase* player, const float deltaTime) {
	Attack(player,deltaTime);

	if (enemy_hp < 0)
		return DEAD;
	return LIVE;
}

void FakerLamiel::Move(PlayerBase* player, const float deltaTime) {
	float player_pos = player->GetModel()->GetPosition().y;

	//if (player_pos  > position.y)
		position.y -= move_speed * deltaTime;

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}

int FakerLamiel::Counter() {
	if (count < 300)
		count++;
	else
		count = 0;

	return count;
}

void FakerLamiel::Attack(PlayerBase*player, const float deltaTime)
{
	float player_pos = player->GetModel()->GetPosition().y;
	
	switch (attack_method)
	{
	case DOWN:
		if (player_pos + 15.0f < position.y)
			Move(player, deltaTime);
		else
			attack_method = TELEPORT;
		break;

	case TELEPORT:
	//	if()
		//attack_method = WAIT;
		break;

	case ATTACK:
			//attack_method = TELEPORT;
		break;
	}
}


