#pragma once

#include "Base/DX12Effekseer.h"
#include "../EnemyManager/EnemyFactory/EnemyFactory.h"
#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerManager.h"

using namespace DirectX;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	bool Initialize();
	int  Update(PlayerManager* player, const float deltaTime);
	void Render();

	std::list<EnemyBase*> GetEnemy() { return enemy; }
	int  GetDeathEnemyCount()		 { return dead_enemy_count; }

	void OnCollisionEnter(EnemyBase* base);
	void OnParryArea(EnemyBase* base);
	
private:
	void Generator();
	void Iterator(PlayerManager* player, const float deltaTime);
	
	std::list<EnemyBase*> enemy;

	PlayerManager* player_data;

	EFFECTHANDLE handle;
	EFFECT       effect;
	DX9::SPRITEFONT font;
	DX9::SKINNEDMODEL model;
	
	int dead_enemy_count = 0;
	float delta;
};
