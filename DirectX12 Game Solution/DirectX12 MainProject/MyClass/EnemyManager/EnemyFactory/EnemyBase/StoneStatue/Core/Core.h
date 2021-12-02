#pragma once
#include "../../EnemyBase.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

class Core : public EnemyBase
{
public:
	Core();
	~Core() {}
    bool Initialize(std::string tag,SimpleMath::Vector3 speed, int hp);
	int Update(SimpleMath::Vector3 player, const float deltaTime);
	void Render();

private:
	void Move(SimpleMath::Vector3 player);
	void Shot(SimpleMath::Vector3 init_bull_pos);

	PlayerBase* player;

	SimpleMath::Vector3 player_pos;
	SimpleMath::Vector3 bull_pos;

	bool shot_flag = false;
	
	float delta;

	const float move_core = 2.0f;
	const float collision_scale = 0.5f;

	const float move_bull_x = 8.0f;
	const float move_bull_y = 4.0f;

	const float max_move = 50.0f;
	const float max_back = 60.0f;

	//!ATTACK�ҋ@����
	float wait_shot_frame = 0;
	const float max_wait_shot = 0.5f;

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
	const float max_landing    = 0.8f;

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