#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyManager.h"
#include "MyClass/ResourceManager/ResourceManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include<fstream>

EnemyManager::EnemyManager()
{
	//!“Ç‘O‚Ì“G‚Ì‰Šú‰»
	for (int i = 0; i < ENEMY_NUM; ++i) {
		tag[i] = "";
		appear_pos[i]   = SimpleMath::Vector3(DBL_MAX,DBL_MAX,DBL_MAX);
		appear_time[i]  = DBL_MAX;
		destract_num[i] = INT_MAX;
		appear_flag[i]  = false;
	}

	LoadEnemyArrangement();
	enemy = {};
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

int EnemyManager::Update(PlayerManager* player, const float deltaTime)
{
	for (auto& enemies : enemy) {
		enemies->Update(player,deltaTime);
	}
	player_data = player;
	delta		= deltaTime;

	Iterator(player_data,delta);

	if (count < ENEMY_NUM) {
		if (AppearTimer() > appear_time[count] || dead_enemy_count >= destract_num[count]) {
			Generator();
			count++;
		}
	}

	return 0;
}

void EnemyManager::Iterator(PlayerManager* player, const float deltaTime) {
	auto itr = enemy.begin();

	while (itr != enemy.end())
	{
		if ((*itr)->Update(player,deltaTime) == LIVE)
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

	if (!appear_flag[count])
	{
		//!“G‚Ìí—ŞE‰ŠúÀ•W‚ğ“n‚µ‚Ä“G‚ğ»‘¢
		enemy.push_back(factory->Create(tag[count], appear_pos[count]));
		appear_flag[count] = true;
	}

}

void EnemyManager::Render()
{
	for (auto& enemies : enemy) {
		enemies->Render();
	}
}

void EnemyManager::OnCollisionEnter(EnemyBase* base) {
     base->Damage(delta,player_data->GetDamage());

	if(StatusManager::Instance().GetCombo() == 3)
	base->Retreat();

	DX12Effect.SetPosition(handle,base->GetModel()->GetPosition());
	handle = DX12Effect.Play(effect);
	DX12Effect.SetPosition(handle, Vector3(6, -7, 0));
}

void EnemyManager::OnParryArea(EnemyBase* base) {
	base->Retreat();
}

int EnemyManager::AppearTimer() {
	if (frame < MAX_FRAME) 
		++frame;
	else {
		frame = 0;
		++timer;
	}

	return timer;
}

void EnemyManager::LoadEnemyArrangement() {
	std::ifstream pos_time_infile("EnemyArrangement/EnemyArrangement.txt");

	std::string dummy_line;

	//! 1`3s‚ğ“Ç‚İ”ò‚Î‚µ
	for (int i = 0; i < DUMMY_LINE; i++) {
		getline(pos_time_infile, dummy_line);
	}

	//!ƒf[ƒ^“Ç‚İ‚İ
	for (int i = 0; i < ENEMY_NUM; ++i) {
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> destract_num[i];
	}
}