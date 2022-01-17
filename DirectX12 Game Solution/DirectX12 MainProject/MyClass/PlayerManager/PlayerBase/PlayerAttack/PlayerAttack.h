#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

class PlayerAttack
{
public:
	 PlayerAttack();
	 virtual ~PlayerAttack() = 0;
	
	 void Initialize();
	 void LoadAssets();


	void Player_Attack(const float deltaTime);

private:
	//ŽO˜AŒ‚
	enum  BURST_STATE
	{
		FIRST,
		SECOND,
		THIRD
	};
	BURST_STATE burst_state_mode;

};