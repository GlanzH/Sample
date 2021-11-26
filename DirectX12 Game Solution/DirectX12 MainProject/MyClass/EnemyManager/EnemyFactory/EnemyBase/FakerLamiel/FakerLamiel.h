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
	int Counter();

	SimpleMath::Vector3 init_pos;

	int count = 0;

	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	
	const float move_speed = 5.0f;

	 enum Lami
	 {
		 DOWN,
		 TELEPORT,
		 ATTACK
	 };

	 int attack_method = DOWN;
};