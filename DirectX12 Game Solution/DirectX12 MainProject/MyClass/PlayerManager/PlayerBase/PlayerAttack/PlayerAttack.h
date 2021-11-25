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
	//攻撃‐3連撃‐カウント
	int attack_count;

	//攻撃のカウント(秒)
	float attack_count_time;

	//攻撃の時間
	bool  attack_flag = false;
	float attack_zeit = 0.0f;
	float attack_zeit_max = 0.03309f;

	//攻撃のクールタイム
	bool cool_time_flag_zwei = false;
	float cool_time_zwei = 0.0f;
	float cool_time_max_zwei[3]{ 0.2f,0.4f,0.3f };
	int count = 0;

	bool  count_flag = false;
	float count_time = 0.0f;
	float count_time_max = 0.4f;

	int damage = 0;

	//攻撃の向き
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//アピール
	enum Appeal_state
	{
		NORMAL,
		APPEAL,
		FOCUS
	};

	Appeal_state appeal_state_mode;

};