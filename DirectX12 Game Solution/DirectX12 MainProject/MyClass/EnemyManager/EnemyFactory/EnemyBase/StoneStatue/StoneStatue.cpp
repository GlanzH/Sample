#include "Base/pch.h"
#include "Base/dxtk.h"
#include "StoneStatue.h"


bool StoneStatue::Initialize()
{
	DX12Effect.Create(L"Effect//shoot//shoot.efk","shoot");
	DX12Effect.Create(L"Effect//charge//charge.efk","charge");
	DX12Effect.Create(L"Effect//landing//landing.efk","landing");
	wait_count = 0;
	return true;
}

int StoneStatue::Update(PlayerBase* player, const float deltaTime) {
	 player_pos = player->GetModel()->GetPosition();

	//SetAnimesion(model, CHARGE);
	
	/*model->AdvanceTime(deltaTime / 1.0f);*/
	
	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void StoneStatue::Attck(const float deltaTime)
{


	switch (attck_method)
	{
	case stone::CHARGE:

		DX12Effect.SetPosition("charge", position);
		DX12Effect.PlayOneShot("charge");
		//else
		//{
			wait_count +=deltaTime;
		//}
		if (wait_count ==1)
		{
			stone::ATTACK;
		}
		break;
	case stone::ATTACK:

		wait_count = 0;
		wait_count++;

		DX12Effect.SetPosition("shoot", position);
		DX12Effect.PlayOneShot("shoot");
	
		if (wait_count ==150)
		{
			stone::WAIT;
		}
		break;
	case stone::WAIT:
		wait_count = 0;
			DX12Effect.SetPosition("landing", position);
			DX12Effect.PlayOneShot("landing");
			wait_count++;
			if (wait_count == 600)
			{
				stone::INIT;
			}
		break;
	case stone::INIT:
		wait_count = 0;
		stone::CHARGE;
		break;
	default:
		attck_method = stone::CHARGE;
		break;
	}
}

void StoneStatue::Shot()
{
	SimpleMath::Vector3 bullet_pos;
	bullet_pos.x -= 3.0f;
	bullet_pos.y -= 2.0f;
}

