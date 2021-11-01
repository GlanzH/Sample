#include "Base/pch.h"
#include "Base/dxtk.h"
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

int EnemyManager::Update(DX9::MODEL& ground, PlayerManager* player, const float deltaTime)
{
	for (auto& enemies : enemy) {
		enemies->Update(ground,player,deltaTime);
	}

	Iterator(ground,player,deltaTime);

	return 0;
}

void EnemyManager::Iterator(DX9::MODEL& ground,PlayerManager* player, const float deltaTime) {
	auto itr = enemy.begin();

	while (itr != enemy.end())
	{
		if ((*itr)->Update(ground,player,deltaTime) == LIVE)
			itr++;
		else {
			//�G�����S�����Ƃ��̏���
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

void EnemyManager::Render()
{
	for (auto& enemies : enemy) {
		enemies->Render();
	}
}

void EnemyManager::OnCollisionEnter(EnemyBase* base) {
	base->Damage();
}