#include "Base/pch.h"
#include "Base/dxtk.h"
#include "StoneStatue.h"
#include"MyClass/ResourceManager/ResourceManager.h"

bool StoneStatue::Initialize()
{
	attck      = ResourceManager::Instance().LoadEffect(L"Effect//shoot//shoot.efk");
	accumulate = ResourceManager::Instance().LoadEffect(L"Effect//charge//charge.efk");;
	landing    = ResourceManager::Instance().LoadEffect(L"Effect//landing//landing.efk");;

	return false;
}

int StoneStatue::Update(PlayerManager* player, const float deltaTime) {
	//SetAnimesion(model, CHARGE);
	
	/*model->AdvanceTime(deltaTime / 1.0f);*/

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void StoneStatue::Attck()
{

}

