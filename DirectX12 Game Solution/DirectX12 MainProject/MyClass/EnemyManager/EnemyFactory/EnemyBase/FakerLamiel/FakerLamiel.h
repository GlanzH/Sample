#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class FakerLamiel : public EnemyBase
{
public:
	FakerLamiel()  {}
	~FakerLamiel() {}
	bool Initialize(SimpleMath::Vector3 speed, int hp);
	int Update(PlayerBase* player, const float deltaTime) override;
private:
	void Move(PlayerBase* player, const float deltaTime);
	void Attack(PlayerBase* player,const float deltaTime);


	SimpleMath::Vector3 init_pos;

	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	
	const float move_speed = 2.5f;

	int Recoil_count = 0;
	 enum Lami
	 {
		 WAIT,
		 ATTACK,
		 SPREAD,
		 TELEPORT
	 };

	 int attack_method = WAIT;
};