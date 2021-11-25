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
	void Attck(const float deltaTime);
	
	
private:
	void Shot();
	  /// ÅEçUåÇ  ÅEó≠Çﬂ    ÅEíÖíe
	EFFECT attack, charge, landing;
	EFFECTHANDLE attack_h;
	EFFECTHANDLE charge_h;
	EFFECTHANDLE landing_h;

	SimpleMath::Vector3 player_pos;

	bool attack_efk_flg;
	bool charge_efk_flg;
	bool landing_efk_flg;
	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	int wait_count;
	enum class stone
	{
		CHARGE,
		ATTACK,
		WAIT,
		INIT,
	};
	stone  attck_method;
};