#pragma once
#include "../EnemyBase.h"

class Arrow : public EnemyBase{
public:
	int  Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime);

private:
	bool LifeDeathDecision() override;
	void Render() override;
	void Move()   override;
	void Action() override;
	void Rotate();
	float Atan2(float y,float x);

	const float pi = 3.141592654f;
	const float distance_adjust_y     = 0.067f;
	const float speed = 1.f;
	SimpleMath::Vector3 shot_pos;

	float stop_frame = 0.0f;
	const float max_stop = 5.0f;

	enum Action {
		WAIT,
		SHOT,
		STOP
	};

	int action = WAIT;
};