#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class Slime : public EnemyBase
{
public:
	Slime()  {}
	~Slime() {}

	bool Initialize();
	int Update(PlayerBase* player, const float deltaTime) override;

private:
	void Move(PlayerBase* player, const float deltaTime);

	bool rush_flag = false;
	char  count = 0;

	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	
	const int stop_count = 120;
	const int accel_num  = 5;

	enum ENEMYMOSION
	{
		DAMAGE,
		WAIT,
		MAX_MOSION
	};
protected:

};