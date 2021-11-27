#pragma once
#include "../../EnemyBase.h"

using namespace DirectX;

class Core : public EnemyBase
{
public:
	Core();
	~Core() {}
    bool Initialize(std::string tag, SimpleMath::Vector3 speed, int hp);
	int Update(SimpleMath::Vector3 player, const float deltaTime) override;
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