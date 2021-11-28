#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class Slime : public EnemyBase
{
public:
	Slime() {};
	~Slime() {}

	int Update(SimpleMath::Vector3 player, const float deltaTime);

private:
	void Move  (SimpleMath::Vector3 player, const float deltaTime);
	void Rotate(SimpleMath::Vector3 player, const float deltaTime);

	const float move_speed      = 2.5f;
};