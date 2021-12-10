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
	void Attack(SimpleMath::Vector3 player);
	PlayerBase* player;

	SimpleMath::Vector3 player_pos;
	SimpleMath::Vector3 bull_pos;
	SimpleMath::Vector3 laser_coordinate;

	const float move_core       = 2.0f;
	const float collision_scale = 0.5f;
	const float max_move        = 50.0f;
	const float max_back        = 60.0f;

	float delta;
	float SHOT_SPEED;

	bool shot_flag;
	bool throw_flag;
	bool special_flag;
	bool landing_flag;

	
   
	int landing_count;
	
	char launch_count_count;
	
	//!WAIT�̑ҋ@����
	float wait_frame = 0;
	const float max_wait = 5.0f;
	//!�`���[�W�G�t�F�N�g�ҋ@����
	float wait_charge_frame = 0;
	const float max_wait_charge = 1.0f;
	//!�`���[�W�G�t�F�N�g�`�掞��
	float charge_effect_frame = 0;
	const float max_charge    = 6.7f;
	//!ATTACK�ҋ@����
	float wait_shot_frame = 0;
    float max_wait_shot = 1.00f;
	//!���e���G�t�F�N�g�`�掞��
	float landing_effect_frame = 0;
	const float max_landing    = 0.6f;
	//!�ŏI�ړ�(STOP)�ҋ@����
	float stop_frame = 0;
	const float max_stop = 10.0f;
	
	int  action = MOVE;
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
	
};