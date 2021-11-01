#include "Base/pch.h"
#include "Base/dxtk.h"
#include"MyClass/EnumManager/EnumManager.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	enemy = {};
	Generator();
}

EnemyManager::~EnemyManager() {
	for (auto& enemies : enemy) {
		delete enemies;
	}
}

bool EnemyManager::Initialize()
{
	
	return true;
}

void EnemyManager::LoadAsset()
{
	DX12Effect.Initialize();
}

int EnemyManager::Update(DX9::MODEL& ground, const float deltaTime) 
{
	
	for (auto& enemies : enemy) {
		enemies->Update(ground,deltaTime);
	}

	DX12Effect.Update();
	Iterator(ground,deltaTime);

	return 0;
}

void EnemyManager::Iterator(DX9::MODEL& ground, const float deltaTime) {
	auto itr = enemy.begin();

	while (itr != enemy.end())
	{
		if ((*itr)->Update(ground,deltaTime) == LIVE)
			itr++;
		else {
			//“G‚ª€–S‚µ‚½‚Æ‚«‚Ìˆ—
			dead_enemy_count++;
			itr = enemy.erase(itr);
		}
	}
}

void EnemyManager::Generator() {
	std::unique_ptr<EnemyFactory> factory = std::make_unique<EnemyFactory>();
	
		
			enemy.push_back(factory->Create("normal", SimpleMath::Vector3(30, 0, 50)));
			enemy.push_back(factory->Create("normal", SimpleMath::Vector3(100, 0, 50)));
			enemy.push_back(factory->Create("normal", SimpleMath::Vector3(170, 0, 50)));
}

void EnemyManager::OnDeviceLost() {
	DX12Effect.Reset();
}

void EnemyManager::Render()
{
	for (auto& enemies : enemy) {
		enemies->Render();
	}

	DX12Effect.Renderer();
}

void EnemyManager::OnCollisionEnter(EnemyBase* base) {
	base->Damage();
}