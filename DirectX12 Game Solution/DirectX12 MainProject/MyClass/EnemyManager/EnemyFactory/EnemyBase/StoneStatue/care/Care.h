#pragma once
#include "../../EnemyBase.h"

using namespace DirectX;

class Care : public EnemyBase
{
public:
	Care() {}
	~Care() {}
    bool Initialize(SimpleMath::Vector3 speed, int hp);
	int Update(PlayerBase* player, const float deltaTime) override;
	void Attack(const float deltaTime);


private:
	void Shot();
	SimpleMath::Vector3 player_pos;

	const float fit_collision_y = 4.0f;
	const float stop_enemy_pos = 20.0f;
	const float ground_collision_y = 100.0f;
	int wait_count;
	enum class stone
	{
		STORAGE,
		CHARGE,
		ATTACK,
		WAIT,
		BACK,
		INIT,
	};
	stone  attack_method;
};