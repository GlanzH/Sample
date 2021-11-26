#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Care.h"



bool Care::Initialize(SimpleMath::Vector3 speed, int hp)
{
	EnemyBase::Initialize(speed, hp);
	DX12Effect.Create(L"Effect//shoot//shoot.efk", "shoot");
	DX12Effect.Create(L"Effect//charge//charge.efk", "charge");
	DX12Effect.Create(L"Effect//landing//landing.efk", "landing");
	wait_count = 0;
	return true;
}

int Care::Update(PlayerBase* player, const float deltaTime) {
	
	player_pos = player->GetModel()->GetPosition();

	//SetAnimesion(model, CHARGE);
	 Attack(deltaTime);
	/*model->AdvanceTime(deltaTime / 1.0f);*/

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void Care::Attack(const float deltaTime)
{
	switch (attack_method)
	{
	case stone::STORAGE:
		model->Move(0.1, 0, 0);
		if (position.z >= 50);
		{
			position.z = 50;
			wait_count++;
			if(wait_count ==1)
			{
			stone::CHARGE;
			}
		}
		break;
	/*case stone::CHARGE:

		DX12Effect.SetPosition("charge", position);
		DX12Effect.PlayOneShot("charge");
		wait_count += deltaTime;
		if (wait_count == 1/2)
		{
			stone::ATTACK;
		}
		break;
	case stone::ATTACK:

		wait_count = 0;
		wait_count++;

		DX12Effect.SetPosition("shoot", position);
		DX12Effect.PlayOneShot("shoot");

		if (wait_count == 150)
		{
			stone::WAIT;
		}
		break;
	case stone::WAIT:
		wait_count = 0;
		DX12Effect.SetPosition("landing", position);
		DX12Effect.PlayOneShot("landing");
		wait_count++;
		if (wait_count == 5)
		{
			stone::INIT;
		}
		break;
	case stone::BACK:
	 
	 model->Move(-0.1, 0, 0);
	 if(position.z >=55)
	 {
		 position.z = 55;
		 stone::INIT;
		 if(wait_count ==10)
		 {
		 stone::STORAGE;
		 }
	 }
	 break;
	case stone::INIT:
		wait_count = 0;
		position.x = 55;
		stone::STORAGE;
		break;*/
	default:
		attack_method = stone::STORAGE;
		break;
	}
}

void Care::Shot()
{
	SimpleMath::Vector3 bullet_pos;
	bullet_pos.x -= 3.0f;
	bullet_pos.y -= 2.0f;
}

