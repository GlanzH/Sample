#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class Slime : public EnemyBase
{
public:
	Slime();
	~Slime() {}

	bool Initialize();
	int Update(PlayerBase* player, const float deltaTime) override;

private:
	void Move  (PlayerBase* player, const float deltaTime);
	void Rotate(PlayerBase* player, const float deltaTime);

	const float fit_collision_y = 4.0f;
	const float move_speed      = 2.5f;
};