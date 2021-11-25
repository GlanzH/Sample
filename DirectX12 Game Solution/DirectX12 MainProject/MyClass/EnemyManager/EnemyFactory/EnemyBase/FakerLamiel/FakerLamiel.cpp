#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

int FakerLamiel::Update( PlayerManager* player, const float deltaTime) {
	Attck(player,deltaTime);

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void FakerLamiel::Move(PlayerManager* player, const float deltaTime) {
	float player_pos = player->GetModel()->GetPosition().x;

	
	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}

void FakerLamiel::Attck(PlayerManager*player, const float deltaTime)
{
	switch (attck_method)
	{
	///‘Ò‹@ó‘Ô
	case Lami::STAND:
		Move(player, deltaTime);
		if (true)
		{
			Lami::ATTCK;
		}
		break;
	///‰ºUŒ‚
	case Lami::ATTCK:
		if (true)
		{
			Lami::SPREAD;
		}
		break;
	///‰¡UŒ‚
	case Lami::SPREAD:

		Recoil_count++;
		if (Recoil_count == 10)
		{
			Lami::TELEPORT;
		}
	case Lami::TELEPORT:

		Recoil_count = 0;

		SimpleMath::Vector3 player_pos = player->GetModel()->GetPosition();
	

	//	model->SetRotation(0.0f, rotation, 0.0f);
		break;
	default:
		attck_method = Lami::STAND;
		 break;
	}
}


