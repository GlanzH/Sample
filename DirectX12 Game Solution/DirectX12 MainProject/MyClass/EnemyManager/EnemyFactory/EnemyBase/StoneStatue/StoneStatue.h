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
	void Attck(EnemyBase* base);

private:
	  /// ÅEçUåÇ  ÅEó≠Çﬂ    ÅEíÖíe
	EFFECT attack, charge, landing;
	EFFECTHANDLE attack_h;
	EFFECTHANDLE charge_h;
	EFFECTHANDLE landing_h;
	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	int wait_count;
	enum class stone
	{
		CHARGE,
		ATTACK,
		WAIT
	};
	stone  attck_method;
};