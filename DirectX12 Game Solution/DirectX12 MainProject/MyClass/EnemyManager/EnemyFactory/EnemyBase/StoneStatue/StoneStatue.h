#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class StoneStatue : public EnemyBase
{
public:
	StoneStatue()  {}
	~StoneStatue() {}
	virtual bool Initialize();
	int Update(PlayerBase* player, const float deltaTime) override;
	void Attck(const float deltaTime);
	
	
private:
	void Shot();
	SimpleMath::Vector3 player_pos;

	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	int wait_count;
	enum class stone
	{
		STORAGE,
		CHARGE,
		ATTACK,
		WAIT,
		INIT,
	};
	stone  attck_method;
};