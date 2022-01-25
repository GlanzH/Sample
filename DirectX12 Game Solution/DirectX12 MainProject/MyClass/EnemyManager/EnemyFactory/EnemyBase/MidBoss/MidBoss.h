#pragma once
#include "../EnemyBase.h"

class MidBoss : public EnemyBase {
public:
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	int  Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime);

private:
	bool LifeDeathDecision() override;
	void Render() override;
	void Move()   override;
	void Action() override;
	void Attack();
	void Damage();
	bool IsDamage();
	void IsRetreat();
	void IsDeath();
	void InitDirect();
	void Rotate();

	DX9::MODEL sword_col;
	SimpleMath::Vector3 sword_pos;

	float damage_flag = false;
	float move_pos_x;

	float damage_frame = 0.0f;
	const float max_damage = 1.0f;

	float wait_frame = 0.0f;
	const float max_wait = 10.0f;

	float attack_frame = 0.0f;
	const float max_attack = 4.0f;

	const float max_death = 2.5f;
	const float max_range = 100.0f;

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
		FIRST_WAIT,
		MOVE,
		ATTACK,
		INIT
	};

	enum Direction {
		RIGHT,
		LEFT
	};

	int action = (int)ActionNum::FIRST_WAIT;
	int direct;
};