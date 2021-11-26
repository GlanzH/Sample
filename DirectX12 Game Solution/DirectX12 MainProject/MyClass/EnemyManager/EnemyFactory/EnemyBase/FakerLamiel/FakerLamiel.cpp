#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

bool FakerLamiel::Initialize(SimpleMath::Vector3 speed, int hp) {
	EnemyBase::Initialize(speed,hp);
	DX12Effect.Create(L"Effect/thunder/thunder.efk", "thunder");
	attack_method = Lami::WAIT;
	init_pos = position;
	return true;
}

int FakerLamiel::Update( PlayerBase* player, const float deltaTime) {
	Attack(player,deltaTime);

	if (enemy_hp < 0)
		return DEAD;
	return LIVE;
}

void FakerLamiel::Move(PlayerBase* player, const float deltaTime) {
	float player_pos = player->GetModel()->GetPosition().x;

	if (player_pos  < position.x)
		position.x -= move_speed * deltaTime;
	else
		position.x += move_speed * deltaTime;

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}

void FakerLamiel::Attack(PlayerBase*player, const float deltaTime)
{
	float player_pos = player->GetModel()->GetPosition().x;
	
	switch (attack_method)
	{
	case WAIT:
		if (player_pos + 15.0f < position.x || player_pos - 15.0f > position.x)
			Move(player, deltaTime);
		else
			attack_method = ATTACK;
		break;

	case ATTACK:
			attack_method = SPREAD;
		break;
	case SPREAD:
		attack_method = TELEPORT;
		break;
	case TELEPORT:
		//position.x = init_pos.x;
		attack_method = WAIT;
		break;
	}
}


