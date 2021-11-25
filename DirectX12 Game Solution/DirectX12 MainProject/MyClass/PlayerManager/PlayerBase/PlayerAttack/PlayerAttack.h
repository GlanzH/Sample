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

	//�U���G�t�F�N�g
    //1�A����
	EFFECT Sword_Effect_1;
	EFFECTHANDLE handle_1;

	//2�A����
	EFFECT Sword_Effect_2;
	EFFECTHANDLE handle_2;

	//3�A����
	EFFECT Sword_Effect_3;
	EFFECTHANDLE handle_3;


	//�U���]3�A���]�J�E���g
	int attack_count;

	//�U���̃J�E���g(�b)
	float attack_count_time;

	//�U���̎���
	bool  attack_flag = false;
	float attack_zeit = 0.0f;
	float attack_zeit_max = 0.03309f;

	//�U���̃N�[���^�C��
	bool cool_time_flag_zwei = false;
	float cool_time_zwei = 0.0f;
	float cool_time_max_zwei[3]{ 0.2f,0.4f,0.3f };
	int count = 0;

	bool  count_flag = false;
	float count_time = 0.0f;
	float count_time_max = 0.4f;

	int damage = 0;

	//�U���̌���
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//�A�s�[��
	enum Appeal_state
	{
		NORMAL,
		APPEAL,
		FOCUS
	};

	Appeal_state appeal_state_mode;

};