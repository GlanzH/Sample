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
	Vector3 laser_coordinate;
	

	float SHOT_SPEED= 0.57f;
	//!ATTACK待機時間
	float wait_shot_frame = 0;
	const float max_wait_shot = 1.05f;

	//!WAITの待機時間
	float wait_frame = 0;
	const float max_wait = 5.0f;

	//!最終移動(STOP)待機時間
	float stop_frame = 0;
	const float max_stop = 10.0f;

	//!チャージエフェクト待機時間
	float wait_charge_frame = 0;
	const float max_wait_charge = 1.05f;

	//!チャージエフェクト描画時間
	float charge_effect_frame = 0;
	const float max_charge    = 6.7f;

	//!着弾時エフェクト描画時間
	float landing_effect_frame = 0;
	const float max_landing    = 1.61f;

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