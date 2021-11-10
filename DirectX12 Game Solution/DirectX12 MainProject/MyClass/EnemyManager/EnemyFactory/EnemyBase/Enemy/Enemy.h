#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class Enemy : public EnemyBase
{
public:
	Enemy()  {}
	~Enemy() {}

	int Update(DX9::MODEL& ground, PlayerManager* player, const float deltaTime) override;

private:
	void Move(DX9::MODEL& ground, PlayerManager* player, const float deltaTime);

	bool rush_flag = false;
	int  count = 0;

	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;

	const int stop_count = 120;
	const int accel_num  = 5;
};