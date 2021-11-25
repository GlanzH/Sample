#include "Base/pch.h"
#include "Base/dxtk.h"
#include "StoneStatue.h"

bool StoneStatue::Initialize()
{
	DX12Effect.Initialize();

	attck      = DX12Effect.Create(L"Effect//shoot//shoot.efk");
	accumulate = DX12Effect.Create(L"Effect//charge//charge.efk");;
	landing    = DX12Effect.Create(L"Effect//landing//landing.efk");;

	return true;
}

int StoneStatue::Update(PlayerBase* player, const float deltaTime) {
	//SetAnimesion(model, CHARGE);
	
	/*model->AdvanceTime(deltaTime / 1.0f);*/

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void StoneStatue::Attck()
{

}

