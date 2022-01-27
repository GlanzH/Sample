#pragma once
#include "../EnemyBase.h"

class RandSwordMan : public EnemyBase {
public:
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	int  Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime);

private:
	bool LifeDeathDecision() override;
	void Render() override;
	void Move()   override;
	void Action() override;
	void IsRetreat();
	void Attack();
	void Freeze();
	void IsDeath();
	void InitDirect();
	void Rotate();
	void Run();

	DX9::MODEL sword_col;
	SimpleMath::Vector3 sword_pos;

	float move_pos_x;

	float attack_frame = 0.0f;
	const float max_attack = 2.5f;

	const float max_death = 2.f;
	const float max_range = 100.0f;

	const float max_is_damage = 0.05f;

	bool end_move;

	enum class Motion {
		RUN_UP,
		ATTACK_UP,
		BOUNCE,
		DAMAGE,
		DEATH,
		RUN_DOWN,
		ATTACK_DOWN,
		FREEZE,
		MAX_MOTION
	};

	enum class ActionNum {
		FIRST_WAIT,
		MOVE,
		ATTACK,
		INIT
	};

	int action = (int)ActionNum::FIRST_WAIT;

};