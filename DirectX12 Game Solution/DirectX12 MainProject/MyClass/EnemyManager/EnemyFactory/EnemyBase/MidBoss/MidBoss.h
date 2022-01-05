#pragma once
#include "../EnemyBase.h"

class MidBoss : public EnemyBase {
public:
	bool Initialize(std::string tag, bool time_stop_flag, int hp);
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);

private:
	void Move()   override;
	void Action() override;
	void Rotate();


	float move_pos_x;

	float wait_frame = 0.0f;
	const float max_wait = 10.0f;

	float attack_frame = 0.0f;
	const float max_attack = 4.0f;

	int direct;
	bool end_move;

	enum class Motion {
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