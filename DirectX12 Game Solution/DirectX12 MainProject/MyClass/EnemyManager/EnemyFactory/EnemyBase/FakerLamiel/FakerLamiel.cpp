#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

bool FakerLamiel::Initialize(SimpleMath::Vector3 speed, int hp) {
	EnemyBase::Initialize(speed,hp);
	DX12Effect.Create(L"Effect/thunder/thunder.efk", "thunder");
	attack_method = DOWN;
	init_pos = position;
	count = 100;
	return true;
}

int FakerLamiel::Update( PlayerBase* player, const float deltaTime) {
	Attack(player,deltaTime);

	if (enemy_hp < 0)
		return DEAD;
	return LIVE;
}

int FakerLamiel::Counter() {
	if (count < 600)
		count++;
	else
		count = 0;

	return count;
}

void FakerLamiel::Attack(PlayerBase*player, const float deltaTime)
{
	SimpleMath::Vector3 player_pos = player->GetModel()->GetPosition();
	
	//if (attack_method == DOWN) {
	//	if (player_pos.y + 15.0f < position.y)
	//		position.y -= move_speed * deltaTime;
	//	else
	//		attack_method = TELEPORT;
	//}
	//else if (attack_method == TELEPORT) {
	//	position.x = player_pos.x;
	//}

	switch (attack_method)
	{
	case DOWN:
		if (player_pos.y + 10.0f < position.y)
			position.y -= move_speed * deltaTime;
		else
			attack_method = TELEPORT;
		break;

	case TELEPORT:
		if (Counter() == 0) {
			position.x = player_pos.x;
			attack_method = ATTACK;
		}
		break;

	case ATTACK:
			attack_method = TELEPORT;
		break;
	}

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}


