#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class Slime : public EnemyBase
{
public:
	Slime() {};
	~Slime() {}
	void OnDeviceLost() {}
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);

private:
	//void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack) override;
	void Action();
	void EntryExitJump();
	void ExitRotate();
	void InitDirection();
	void ChangeDirection();
	void Move  ();
	void Rotate();

	float exit_frame     = 0.0f;
	const float max_exit = 1.0f;

	float is_move_frame     =  0.0f;
	const float max_is_move = 10.0f;

	const float adjust_y   = 90.0f;
	const float move_speed = 2.5f;

	float delta;
	SimpleMath::Vector3 player_pos;

	D3DMATERIAL9 material;

	 bool jump_flag = true;
	float jump_time = 0.0f;
	float jump_dist;

	bool init_direct_flag = false;

	const float jump_power = -0.3f;
	const float jump_speed = 25.0f;
	const float gravity = 9.80665f;

	enum JumpPosition {
		ENTRY_POS =  50,
		EXIT_POS  = 15
	};

	enum JumpDistance {
		ENTRY_DIST = 27,
		EXIT_DIST  = 30
	};

	enum SlimeAction {
		ENTRY,
		MOVE,
		EXIT
	};

	enum SlimeDirection{
		MOVE_LEFT,
		MOVE_RIGHT
	};

	int action = ENTRY;
	int move_direct = MOVE_LEFT;
};