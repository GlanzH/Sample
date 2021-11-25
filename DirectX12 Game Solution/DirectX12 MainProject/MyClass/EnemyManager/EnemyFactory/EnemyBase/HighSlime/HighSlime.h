#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class HighSlime : public EnemyBase
{
public:
	HighSlime()  {}
	~HighSlime() {}

	int Update(PlayerBase* player, const float deltaTime) override;

private:
	void Jump(PlayerBase* player, const float deltaTime);

	bool rush_flag = false;
	char  count = 0;

	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	
	const int stop_count = 120;
	const int accel_num  = 5;
	//ジャンプしてるかのフラグ。
	bool jump_flag = true;
	float jump_time = 0.0f;
	float jump_start_y ;
	//1/2
	const float half = 0.5f;
	//重力加速度
	const float gravity = 120.0f;
	//初速
	const float fastspeed = 10.0f;
	/*void SetAnimesion(DX9::SKINNEDMODEL& model, const int enabletack);
	enum ENEMYMOSION
	{
		DAMAGE,
		WAIT,
		MAX_MOSION
	};*/
};