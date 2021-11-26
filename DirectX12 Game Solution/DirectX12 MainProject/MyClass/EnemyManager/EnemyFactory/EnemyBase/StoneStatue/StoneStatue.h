#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class StoneStatue : public EnemyBase
{
public:
	StoneStatue();
	~StoneStatue();
	void Initialize(SimpleMath::Vector3 speed, int h);
	int Update(PlayerBase* player, const float deltaTime) override;
	void Attack(const float deltaTime);
	
private:
	const float fit_collision_y = 4.0f;
	const float stop_enemy_pos = 20.0f;
	const float ground_collision_y = 100.0f;
};