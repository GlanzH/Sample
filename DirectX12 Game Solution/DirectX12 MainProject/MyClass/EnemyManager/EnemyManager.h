#pragma once

using namespace DirectX;
#include "Base/DX12Effekseer.h"
#include "../EnemyManager/EnemyFactory/EnemyFactory.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	bool Initialize();
	void LoadAsset();
	int  Update(DX9::MODEL& ground, const float deltaTime);
	void OnDeviceLost();
	void Render();

	int GetDeathEnemyCount() { return dead_enemy_count; }

private:
	
	void Generator();
	void Iterator(DX9::MODEL& ground, const float deltaTime);

	std::list<EnemyBase*> enemy;
	int dead_enemy_count = 0;

	EFFECTHANDLE handle;
	EFFECT       effect;
};
