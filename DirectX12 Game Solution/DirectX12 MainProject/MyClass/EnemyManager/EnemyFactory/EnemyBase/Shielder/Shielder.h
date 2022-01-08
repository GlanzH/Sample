#pragma once
#include "../EnemyBase.h"

class Shielder : public EnemyBase {
public:
	bool Initialize(std::string tag, bool time_stop_flag, int hp);
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);

private:
	bool LifeDeathDecision() override;
	void Move()   override;
	void Action() override;
	void IsDeath();
	void Rotate();
	void LimitRange();

	int direct;

	const float limit_x = 65.0f;

	float move_frame     = 0.0f;
	const float max_move = 1.0f;

	float wait_frame = 0.0f;
	const float max_wait = 10.0f;

	float death_frame = 0.0f;
	const float max_death = 2.0f;

	enum class Motion {
		CONFUSE,
		DEATH,
		DAMAGE,
		RUN,
		WAIT,
		MAX_MOTION
	};

	enum class ActionNum {
		RUN,
		WAIT,
		INIT
	};

	enum Direction {
		LIGHT,
		LEFT
	};

	int action = (int)ActionNum::INIT;

};