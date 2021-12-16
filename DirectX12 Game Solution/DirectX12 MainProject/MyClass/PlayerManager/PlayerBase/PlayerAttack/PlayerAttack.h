#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

class PlayerAttack
{
public:
	 PlayerAttack(){};
	~PlayerAttack(){};
	
	void LoadAssets();

	void Player_Attack(const float deltaTime);

private:
	enum ATTACK_BURST_STATE
	{
		ONE,
		TWO,
		THREE
	};
	ATTACK_BURST_STATE attack_burst_state;
};