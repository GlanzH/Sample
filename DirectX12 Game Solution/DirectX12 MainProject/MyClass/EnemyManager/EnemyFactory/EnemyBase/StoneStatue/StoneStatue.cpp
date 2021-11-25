#include "Base/pch.h"
#include "Base/dxtk.h"
#include "StoneStatue.h"


bool StoneStatue::Initialize()
{
	attack      = DX12Effect.Create(L"Effect//shoot//shoot.efk");
	charge      = DX12Effect.Create(L"Effect//charge//charge.efk");;
	landing     = DX12Effect.Create(L"Effect//landing//landing.efk");;
	wait_count = 0;
	attack_efk_flg  = false;
	charge_efk_flg  = false;
	landing_efk_flg = false;

	return false;
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

		if (!charge_efk_flg)
		{
			DX12Effect.SetPosition(charge_h, position);
			charge_h = DX12Effect.Play(charge);
			charge_efk_flg = true;
		}
		else
		{
			wait_count +=deltaTime;
		}
		if (wait_count ==1)
		{
			stone::ATTACK;
		}
		break;
	case stone::ATTACK:

		wait_count = 0;
		wait_count++;
		if (!attack_efk_flg)
		{
			DX12Effect.SetPosition(attack_h, position);
			attack_h = DX12Effect.Play(attack);
			attack_efk_flg = true;
		}
		if (wait_count ==150)
		{
			stone::WAIT;
		}
		break;
	case stone::WAIT:
		wait_count = 0;
		if (!landing_efk_flg)
		{
			DX12Effect.SetPosition(landing_h, position);
			landing_h = DX12Effect.Play(landing);
			landing_efk_flg = true;
			wait_count++;
			if (wait_count == 600)
			{
				stone::INIT;
			}
		}
		break;
	case stone::INIT:
		wait_count = 0;
		charge_efk_flg  = false;
		attack_efk_flg  = false;
		landing_efk_flg = false;
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

