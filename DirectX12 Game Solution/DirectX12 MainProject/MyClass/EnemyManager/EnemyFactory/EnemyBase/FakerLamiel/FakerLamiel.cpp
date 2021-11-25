#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

int FakerLamiel::Update( PlayerBase* player, const float deltaTime) {
	Attck(player,deltaTime);

	if (enemy_hp < 0)
		return DEAD;
	model->SetScale(1.0);
	model->SetPosition(0 ,13, 50);
	return LIVE;
}

void FakerLamiel::Move(PlayerBase* player, const float deltaTime) {
	float player_pos = player->GetModel()->GetPosition().x;

	
	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}

void FakerLamiel::Attck(PlayerBase*player, const float deltaTime)
{
	switch (attck_method)
	{
	//�ҋ@���
	case Lami::STAND:
		Move(player, deltaTime);
		if (true)
		{
			Lami::ATTCK;
		}
		break;
	//���U��
	case Lami::ATTCK:
		if (true)
		{
			Lami::SPREAD;
		}
		break;
	///���U��
	case Lami::SPREAD:

		Recoil_count++;
		if (Recoil_count == 10)
		{
			Lami::TELEPORT;
		}
	case Lami::TELEPORT:

		Recoil_count = 0;
		break;
	default:
		attck_method = Lami::STAND;
		 break;
	}
}


