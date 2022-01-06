#pragma once
#include "../EnemyBase.h"

class Arrow : public EnemyBase{
public:
	bool Initialize(std::string tag, bool time_stop_flag, int hp);
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);

private:
	void Move()   override;
	void Action() override;
	void Rotate();
	float Atan2(float y,float x);

	const float pi = 3.141592654f;
	const float distance_adjust_y     = 0.067f;
	//–î‚Ì‘¬“x
	const float distance_adjust_speed = 0.06f;
	SimpleMath::Vector3 shot_pos;

	enum Action {
		WAIT,
		SHOT
	};

	int action = WAIT;
};