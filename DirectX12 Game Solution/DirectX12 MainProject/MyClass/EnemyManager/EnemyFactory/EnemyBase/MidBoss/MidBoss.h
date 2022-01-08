#pragma once
#include "../EnemyBase.h"

class MidBoss : public EnemyBase {
public:
	bool Initialize(std::string tag, bool time_stop_flag, int hp);
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);

private:
	bool LifeDeathDecision() override;
	void Move()   override;
	void Action() override;
	void Damage();
	bool IsDamage();
	void IsDeath();
	void Rotate();

	float damage_flag = false;
	float move_pos_x;

	float damage_frame = 0.0f;
	const float max_damage = 1.0f;

	float wait_frame = 0.0f;
	const float max_wait = 10.0f;

	float attack_frame = 0.0f;
	const float max_attack = 4.0f;

	float death_frame = 0.0f;
	const float max_death = 2.5f;

	int direct;
	bool end_move;

	enum class Motion {
		CONFUSE,
		WALK,
		DEATH,
		DAMAGE,
		ATTACK,
		WAIT,
		MAX_MOTION
	};

	enum class ActionNum {
		MOVE,
		ATTACK,
		WAIT,
		INIT
	};

	enum Direction {
		LIGHT,
		LEFT
	};

	int action = (int)ActionNum::INIT;

};