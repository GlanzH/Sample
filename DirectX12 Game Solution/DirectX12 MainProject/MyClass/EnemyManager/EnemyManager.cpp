#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include<fstream>

EnemyManager::EnemyManager()
{
	//!読込前の敵の初期化
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

	player_data = player_base;
	enemy_base.EffectInit();

	LoadEnemyArrangement();
	return true;
}

int EnemyManager::Update(SimpleMath::Vector3 player,bool special_attack_flag, bool thorow_things_flag, const float deltaTime)
{
	for (auto& enemies : enemy) {
		enemies->Update(player, special_attack_flag, thorow_things_flag,deltaTime);
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
		}
		else {
			//敵が死亡したときの処理
			dead_enemy_count++;

			if ((*itr)->LifeDeathDecision() == DEAD) {
				(*itr)->DeathEffect();
				StatusManager::Instance().HeartCount();
			}
			else {
				itr = enemy.erase(itr);
				continue;
			}

			itr = enemy.erase(itr);
		}
	}
}

void EnemyManager::Generator() {
	std::unique_ptr<EnemyFactory> factory = std::make_unique<EnemyFactory>();

	if (!appear_flag[count])
	{
		//!敵の種類・初期座標を渡して敵を製造
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
	 base->HitEffect();

	 std::string tag = base->GetTag();

	 if (tag != "C") {
		 if (StatusManager::Instance().GetCombo() == max_combo)
			 base->Retreat();
	 }	
}

void EnemyManager::OnCollisionSpecialMove(EnemyBase* base) {
	base->Damage(20);
}

void EnemyManager::OnCollisionAudience(EnemyBase* base) {
	base->Damage(20);
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

	//! 1〜3行を読み飛ばし
	for (int i = 0; i < DUMMY_LINE; ++i) {
		getline(pos_time_infile, dummy_line);
	}

	//!データ読み込み
	for (int i = 0; i < ENEMY_NUM; ++i) {
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> destract_num[i];
	}
}

