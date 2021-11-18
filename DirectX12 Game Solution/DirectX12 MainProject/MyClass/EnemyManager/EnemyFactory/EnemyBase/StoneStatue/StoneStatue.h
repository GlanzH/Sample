#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class StoneStatue : public EnemyBase
{
public:
	StoneStatue()  {}
	~StoneStatue() {}

	virtual int Update(DX9::MODEL& ground, PlayerManager* player, const float deltaTime) ;

private:
	void Move(DX9::MODEL& ground, PlayerManager* player, const float deltaTime);

	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
};