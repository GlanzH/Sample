#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

bool FakerLamiel::Initialize(std::string tag,SimpleMath::Vector3 speed, int hp) {
	EnemyBase::Initialize(tag,speed,hp);
	DX12Effect.Create(L"Effect/thunder/thunder.efk", "thunder");
	attack_method = DOWN;
	init_pos = position;
	count = 100;
	return true;
}

int FakerLamiel::Update(SimpleMath::Vector3 player, const float deltaTime) {
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

void FakerLamiel::Attack(SimpleMath::Vector3 player, const float deltaTime)
{
	switch (attack_method)
	{
	case DOWN:
		if (player.y + 10.0f < position.y)
			position.y -= move_speed * deltaTime;
		else
			attack_method = TELEPORT;
		break;

	case TELEPORT:
		if (Counter() == 0) {
			position.x = player.x;
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


