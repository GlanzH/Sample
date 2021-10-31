#pragma once
#include "../EnemyBase.h"

using namespace DirectX;

class Enemy : public EnemyBase
{
public:
	Enemy()  {}
	~Enemy() {}

	int  Update(DX9::MODEL& ground, const float deltaTime) override;

private:
	void Move(DX9::MODEL& ground, const float deltaTime);
};