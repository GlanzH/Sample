#pragma once
#include "../../EnemyBase.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

class Core : public EnemyBase
{
public:
	Core();
	~Core() {}
    bool Initialize(std::string tag, bool time_stop_flag,int hp);
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	void Render();

private:
	void Move(SimpleMath::Vector3 player);
	void Shot(SimpleMath::Vector3 init_bull_pos);
	void StopEffect();

	PlayerBase* player;

	SimpleMath::Vector3 player_pos;
	SimpleMath::Vector3 bull_pos;
	
	bool shot_flag = false;
	
	float delta;
	
	SimpleMath::Vector3 shot_pos;

	float oblique_shooting;
	float spead;
	const float move_core = 2.0f;
	const float collision_scale = 0.5f;
	const float max_move = 50.0f;
	const float max_back = 60.0f;
	int attack_count =0;
	const int MAX_COUNT=3;
	int landing_count;

	//!ATTACK�ҋ@����
	float wait_shot_frame = 0;
	const float max_wait_shot = 0.75f;

	//!WAIT�̑ҋ@����
	float wait_frame = 0;
	const float max_wait = 5.0f;

	//!�ŏI�ړ�(STOP)�ҋ@����
	float stop_frame = 0;
	const float max_stop = 10.0f;

	//!�`���[�W�G�t�F�N�g�ҋ@����
	float wait_charge_frame = 0;
	const float max_wait_charge = 1.0f;

	//!�`���[�W�G�t�F�N�g�`�掞��
	float charge_effect_frame = 0;
	const float max_charge    = 6.7f;

	//!���e���G�t�F�N�g�`�掞��
	float landing_effect_frame = 0;
	const float max_landing    = 0.2f;

	bool throw_flag;
	bool special_flag;

	bool launch_permit;
	char launch_count_count;
	enum StatueAction
	{
		MOVE,
		CHARGE,
		ATTACK,
		WAIT,
		BACK,
		STOP,
		INIT,
	};

	int  action = MOVE;
};