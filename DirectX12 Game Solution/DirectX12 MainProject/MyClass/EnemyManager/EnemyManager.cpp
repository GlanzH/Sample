#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyManager.h"
#include "MyClass/ResourceManager/ResourceManager.h"

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
	DX12Effect.Initialize();
	effect = ResourceManager::Instance().LoadEffect(L"Effect//EnemySampleEffect//enemy_hit.efk");
	return true;
}

int EnemyManager::Update(DX9::MODEL& ground, PlayerManager* player, const float deltaTime)
{
	for (auto& enemies : enemy) {
		enemies->Update(ground,player,deltaTime);
	}
	delta = deltaTime;
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

void EnemyManager::Render()
{
	for (auto& enemies : enemy) {
		enemies->Render();
	}
}

void EnemyManager::OnCollisionEnter(EnemyBase* base) {
	base->Damage(delta);
	base->Retreat();

	DX12Effect.SetPosition(handle,base->GetModel()->GetPosition());
	handle = DX12Effect.Play(effect);
	DX12Effect.SetPosition(handle, Vector3(6, -7, 0));
}

void EnemyManager::OnParryArea(EnemyBase* base) {
	base->Retreat();
}

