#pragma once

using namespace DirectX;
#include "Base/DX12Effekseer.h"
#include "../EnemyManager/EnemyFactory/EnemyFactory.h"
#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerManager.h"
#include "Base/DX12Effekseer.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	bool Initialize();
	int  Update(DX9::MODEL& ground, PlayerManager* player, const float deltaTime);
	void Render();

	std::list<EnemyBase*> GetEnemy() { return enemy; }
	int  GetDeathEnemyCount()		 { return dead_enemy_count; }

	void OnCollisionEnter(EnemyBase* base);

private:
	
	void Generator();
	void Iterator(DX9::MODEL& ground, PlayerManager* player, const float deltaTime);

	std::list<EnemyBase*> enemy;
	int dead_enemy_count = 0;

	EFFECTHANDLE handle;
	EFFECT       effect;
};
