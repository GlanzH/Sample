#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class Enemy : public EnemyBase
{
public:
	Enemy()  {}
	~Enemy() {}

	int  Update(const float deltaTime) override;
	void Move(const float deltaTime);

private:
};