#pragma once
#include "../EnemyBase.h"
#include <random>

using namespace DirectX;

class FakerLamiel : public EnemyBase
{
public:
	FakerLamiel()  {}
	~FakerLamiel() {}

	int Update(SimpleMath::Vector3 player, const float deltaTime) override;
private:
	void Attack(SimpleMath::Vector3 player);

	SimpleMath::Vector3 init_pos;

	float teleport_frame = 0;
	float omen_effect_frame = 0;
	float fire_effect_frame = 0;

	const float fit_collision_y    = 4.0f;
	const float stop_enemy_pos     = 20.0f;
	const float ground_collision_y = 100.0f;
	
	const float move_speed = 5.0f;

	 enum LamielAction
	 {
		 DOWN,
		 ATTACK_SIGH,
		 ATTACK,
		 TELEPORT,
		 INIT_DATA
	 };

	 int action = DOWN;
	 float delta;

	 bool omen_load_flag = false;
	 bool fire_load_flag = false;

	 std::mt19937 random_device;
	 std::uniform_int_distribution<int> distribute;
};