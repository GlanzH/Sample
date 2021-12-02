#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include<fstream>

EnemyManager::EnemyManager()
{
	//!“Ç‘O‚Ì“G‚Ì‰Šú‰»
	enemy = {};


	for (int i = 0; i < ENEMY_NUM; ++i) {
		tag[i]          = INT_MAX;
		appear_pos[i]   = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
		appear_time[i]  = INT_MAX;
		destract_num[i] = INT_MAX;
		appear_flag[i]  = false;
	}
}

EnemyManager::~EnemyManager() {
	for (auto& enemies : enemy) {
		delete enemies;
	}
}

bool EnemyManager::Initialize(PlayerBase* player_base)
{
	DX12Effect.Initialize();
	DX12Effect.Create(L"Effect/EnemyEffect/hit/hit.efk","hit_eff");
	DX12Effect.Create(L"Effect/EnemyEffect/die/die.efk","die");
	player_data = player_base;
	effect_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);

	LoadEnemyArrangement();
	return true;
}

int EnemyManager::Update(SimpleMath::Vector3 player, const float deltaTime)
{
	for (auto& enemies : enemy) {
		enemies->Update(player,deltaTime);
	}

	Iterator();
	delta = deltaTime;

	if (count < ENEMY_NUM) {
		if (AppearTimer() > appear_time[count] || dead_enemy_count >= destract_num[count]) {
			Generator();
			count++;
		}
	}

	return 0;
}

void EnemyManager::Iterator() {
	auto itr = enemy.begin();

	while (itr != enemy.end())
	{
		if ((*itr)->LifeDeathDecision() == LIVE) {
			itr++;
			effect_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
		}
		else {
			//“G‚ª€–S‚µ‚½‚Æ‚«‚Ìˆ—
			dead_enemy_count++;

			auto tag = (*itr)->GetTag();

			if (death_frame < max_death_frame) {
				if (tag == "S" || tag == "H") {
					effect_pos = (*itr)->GetAnimModel()->GetPosition();
				}
				else {
					effect_pos = (*itr)->GetModel()->GetPosition();
				}

				DX12Effect.SetPosition("die", effect_pos);
				DX12Effect.Play("die");
				death_frame += delta;
			}
			else {
				death_frame = 0;
				itr = enemy.erase(itr);
			}
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
     base->Damage(player_data->GetDamage());

	 std::string tag = base->GetTag();

	 if (tag != "C") {
		 if (StatusManager::Instance().GetCombo() == max_combo)
			 base->Retreat();
	 }

	SimpleMath::Vector3 pos;
	if (tag == "S" || tag == "H") 
		pos = base->GetAnimModel()->GetPosition();
	else 
		pos = base->GetModel()->GetPosition();

	DX12Effect.SetPosition("hit_eff", pos);
	DX12Effect.Play("hit_eff");
}

int EnemyManager::AppearTimer() {
	if (frame < max_frame) 
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
	for (int i = 0; i < DUMMY_LINE; ++i) {
		getline(pos_time_infile, dummy_line);
	}

	//!ƒf[ƒ^“Ç‚İ‚İ
	for (int i = 0; i < ENEMY_NUM; ++i) {
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> destract_num[i];
	}
}

