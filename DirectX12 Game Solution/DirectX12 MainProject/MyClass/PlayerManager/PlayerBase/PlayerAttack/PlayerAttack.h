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

	//First
	void First_Burst(const float deltaTime);
	//Second
	void Second_Burst(const float deltaTime);
	//Third
	void Third_Burst(const float deltaTime);


private:

	//First
	bool first_burst_flag;
	float first_burst_start;
	float first_burst_end;

	//Second
	bool second_burst_flag;
	float second_burst_start;
	float second_burst_end;

	//THIRD
	bool third_burst_flag;
	float third_burst_start;
	float third_burst_end;

};