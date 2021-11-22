#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class StoneStatue : public EnemyBase
{
public:
	StoneStatue()  {}
	~StoneStatue() {}
	bool Initialize();
	int Update(PlayerManager* player, const float deltaTime) override;
	void Attck();

private:
	  /// �E�U��  �E����    �E���e
	EFFECT attck, accumulate, landing;
	EFFECTHANDLE handle;
	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	enum STONEMOSION
	{
		CHARGE,
		ATTCK,
	};
};