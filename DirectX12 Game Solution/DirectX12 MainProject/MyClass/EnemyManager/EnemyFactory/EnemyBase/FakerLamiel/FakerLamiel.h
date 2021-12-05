#pragma once
#include "../EnemyBase.h"
#include <random>

using namespace DirectX;

class FakerLamiel : public EnemyBase
{
public:
	FakerLamiel()  {}
	~FakerLamiel() {}

	bool Initialize(std::string tag, SimpleMath::Vector3 speed, int hp);
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	void Render();
private:
	void Move(SimpleMath::Vector3 player);
	void MoveFireCollision();

	SimpleMath::Vector3 fire_pos;
	const SimpleMath::Vector3 collision_scale = SimpleMath::Vector3(25, 14, 10);

	float teleport_frame    = 0;
	float omen_effect_frame = 0;
	float fire_effect_frame = 0;

	const float min_down_pos = 15.0f;

	const float max_omen_frame = 3.5f;

	const float adjust_sigh_y = 6.0f;
	const float fire_effect_y = 15.0f;
	const float fire_effect_z = 150.0f;

	const float adjust_fire_x = 60.0f;
	const float adjust_fire_y = 15.0f;

	const float move_fire  = 53.95f;
	const float move_speed = 10.0f;

	 bool appear_collision_flag = false;

	 float delta;

	 bool draw_flag = false;

	 std::mt19937 random_device;
	 std::uniform_int_distribution<int> distribute;

	 enum LamielAction
	 {
		 DOWN,
		 ATTACK_SIGH,
		 ATTACK,
		 TELEPORT,
		 INIT_DATA
	 };

	 enum MaxFrame {
		 MAX_OMEN_FRAME = 3,
		 MAX_FIRE_FRAME = 2,
		 MAX_TELEPORT_FRAME = 10
	 };

	 enum TeleportRenge {
		 MIN_RANGE = -30,
		 NAX_RANGE = 40
	 };

	 int action = DOWN;
};