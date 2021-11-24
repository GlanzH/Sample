#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class HighSlime : public EnemyBase
{
public:
	HighSlime()  {}
	~HighSlime() {}

	int Update(PlayerManager* player, const float deltaTime) override;

private:
	void Move  (PlayerManager* player, const float deltaTime);
	void Rotate(PlayerManager* player, const float deltaTime);
	void Jump(const float deltaTime);

	const float fit_collision_y    =   4.0f;
	const float ground_collision_y = 100.0f;
	
	//ジャンプしてるかのフラグ。
	bool jump_flag = true;
	float jump_time = 0.0f;

	const float jump_power = -0.1f;
	const float jump_speed = 10.0f;
	const float gravity	   = 9.80665f;
};