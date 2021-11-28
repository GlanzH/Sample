#pragma once
#include "../../EnemyBase.h"

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

	SimpleMath::Vector3 player_pos;
	SimpleMath::Vector3 bull_pos;

	bool shot_flag = false;
	
	float delta;

	float wait_count = 0;
	float stop_count = 0;

	float charge_effect_frame = 0;
	const float max_charge    = 2.6f;

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

	enum EffectFrame {

	};

	int  action = MOVE;
};