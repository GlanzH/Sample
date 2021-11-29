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

	float max_move;
	float max_back;
	//!ATTACK待機時間
	float wait_shot_frame = 0;
	const float max_wait_shot = 0.5f;

	//!WAITの待機時間
	float wait_frame = 0;
	const float max_wait = 5.0f;

	//!最終移動(STOP)待機時間
	float stop_frame = 0;
	const float max_stop = 10.0f;

	//!チャージエフェクト待機時間
	float wait_charge_frame = 0;
	const float max_wait_charge = 1.0f;

	//!チャージエフェクト描画時間
	float charge_effect_frame = 0;
	const float max_charge    = 6.7f;

	//!着弾時エフェクト描画時間
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