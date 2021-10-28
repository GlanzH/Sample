#pragma once

using namespace DirectX;
#include "EnemyBase/EnemyBase.h"
#include "../PlayerManager/PlayerManager.h"

typedef SimpleMath::Vector3 Vector3;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager() {};

	bool Initialize();
	void LoadAsset();
	int  Update(DX9::MODEL& ground, const float deltaTime);
	void Render();

	int GetDeathEnemyCount() { return dead_enemy_count; }

private:
	std::list<EnemyBase*> enemy;

	int dead_enemy_count = 0;

	//	void Move(DX9::MODEL& ground, const float deltaTime);
	//const Vector3 init_pos = Vector3(50.0f, 0.0f, 50.0f);
};
