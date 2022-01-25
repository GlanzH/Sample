#pragma once
#include "../EnemyBase.h"

class Shielder : public EnemyBase {
public:
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	int  Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime);

private:
	bool LifeDeathDecision() override;
	void Render() override;
	void Move()   override;
	void Action() override;
	void HitEffect();
	void Damage();
	void Attack();
	void InitDirect();
	void IsDeath();
	void Freeze();
	void Rotate();

	DX9::MODEL sword_col;
	SimpleMath::Vector3 sword_pos;

	const float limit_x = 65.0f;

	float move_frame     = 0.0f;
	const float max_move = 1.0f;

	float wait_frame = 0.0f;
	const float max_wait = 10.0f;

	const float max_death = 2.0f;

	const float max_range = 100.0f;

	float is_damage = 0.0f;

	enum class Motion {
		RUN,
		DAMAGE,
		DEATH,
		MAX_MOTION
	};

	enum class ActionNum {
		FIRST_WAIT,
		RUN,
		WAIT,
		INIT
	};

	enum Direction {
		RIGHT,
		LEFT
	};

	int action = (int)ActionNum::FIRST_WAIT;
	int direct;
};