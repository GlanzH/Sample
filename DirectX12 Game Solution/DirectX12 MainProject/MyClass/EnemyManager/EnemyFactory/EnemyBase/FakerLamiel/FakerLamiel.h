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
	int Update(SimpleMath::Vector3 player, const float deltaTime);
	void Render();
private:
	virtual void Attack(SimpleMath::Vector3 player);

	SimpleMath::Vector3 init_pos;

	float teleport_frame    = 0;
	float omen_effect_frame = 0;
	float fire_effect_frame = 0;

	const float move_speed = 5.0f;

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
		 MAX_FIRE_FRAME = 7,
		 MAX_TELEPORT_FRAME = 10
	 };

	 enum TeleportRenge {
		 MIN_RANGE = -30,
		 NAX_RANGE =  40
	 };

	 int action = DOWN;
	 float delta;

	 std::mt19937 random_device;
	 std::uniform_int_distribution<int> distribute;
};