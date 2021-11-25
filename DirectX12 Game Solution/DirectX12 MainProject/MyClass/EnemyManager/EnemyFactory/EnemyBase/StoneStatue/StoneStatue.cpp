#include "Base/pch.h"
#include "Base/dxtk.h"
#include "StoneStatue.h"
#include"MyClass/ResourceManager/ResourceManager.h"

bool StoneStatue::Initialize()
{
	attack      = ResourceManager::Instance().LoadEffect(L"Effect//shoot//shoot.efk");
	charge      = ResourceManager::Instance().LoadEffect(L"Effect//charge//charge.efk");;
	landing     = ResourceManager::Instance().LoadEffect(L"Effect//landing//landing.efk");;

	return false;
}

int StoneStatue::Update(PlayerManager* player, const float deltaTime) {
	//SetAnimesion(model, CHARGE);
	
	/*model->AdvanceTime(deltaTime / 1.0f);*/

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void StoneStatue::Attck(EnemyBase* base)
{
	switch (attck_method)
	{
	case stone::CHARGE:

		wait_count = 0;
		DX12Effect.SetPosition(charge_h, base->GetModel()->GetPosition());
		charge_h = DX12Effect.Play(charge);

		if (wait_count ==1)
		{
			stone::ATTACK;
		}
	case stone::ATTACK:

		wait_count = 0;
		DX12Effect.SetPosition(attack_h, base->GetModel()->GetPosition());
		attack_h = DX12Effect.Play(attack);
		if (true)
		{
			stone::WAIT;
		}

	case stone::WAIT:

		DX12Effect.SetPosition(landing_h, base->GetModel()->GetPosition());
		landing_h = DX12Effect.Play(landing);
		wait_count++;
		if (wait_count ==10)
		{
			stone::CHARGE;
		}
	default:
		attck_method = stone::CHARGE;
		break;
	}
}

