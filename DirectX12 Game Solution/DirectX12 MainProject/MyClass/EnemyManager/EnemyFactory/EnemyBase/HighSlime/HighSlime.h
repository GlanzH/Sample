#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class HighSlime : public EnemyBase
{
public:
	HighSlime();
	~HighSlime() {}
	bool Initialize();
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);

private:
	void Action();
	void EntryExitJump();
	void ExitRotate();
	void Move  ();
	void Rotate();
	void Jump();

	float delta;
	SimpleMath::Vector3 player_pos;

	//ジャンプしてるかのフラグ。
	bool jump_flag = true;
	float jump_time = 0.0f;
	float jump_dist;

	float is_move_frame = 0.0f;
	const float max_is_move = 10.0f;

	float exit_frame = 0.0f;
	const float max_exit = 1.0f;

	const float adjust_y = 45.0f;

	const float move_speed =  5.0f;
	const float jump_power = -0.3f;
	const float jump_speed = 15.0f;
	const float gravity	   = 9.80665f;

	const float exit_jump_power = -0.5f;
	const float exit_jump_speed = 28.0f;

	enum JumpPosition {
		ENTRY_POS = 50,
		EXIT_POS = 15
	};

	enum JumpDistance {
		ENTRY_DIST = 27,
		EXIT_DIST = 30
	};

	enum SlimeAction {
		ENTRY,
		MOVE,
		EXIT
	};

	int action = ENTRY;
};