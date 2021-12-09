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
		tag[i]            = "";
		appear_pos[i]     = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
		appear_time[i]    = INT_MAX;
		destract_num[i]   = INT_MAX;
		appear_flag[i]    = false;
		time_stop_flag[i] = false;
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
	DX12Effect.Create(L"Effect/EnemyEffect/deathblow_hit/deathblow_hit.efk", "special");
	DX12Effect.Create(L"Effect/EnemyEffect/boss_death/boss_death.efk", "boss");
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

	for (auto itr = enemy.begin(); itr != enemy.end();)
	{
		if ((*itr)->LifeDeathDecision() == LIVE) {
			itr++;
		}
		else {
			//“G‚ª€–S‚µ‚½‚Æ‚«‚Ìˆ—
			dead_enemy_count++;

			if ((*itr)->GetTimeStopFlag()) {
				time_stop_count++;
				enemy_stop_flag = true;
			}

			if ((*itr)->LifeDeathDecision() == DEAD) {

				if (!special_move_flag) {
					if ((*itr)->GetTag() != "C")
						(*itr)->DeathEffect();
					else
						DX12Effect.PlayOneShot("boss", (*itr)->GetModel()->GetPosition() + SimpleMath::Vector3(0, 21, 0));
				}

				special_move_flag = false;

				StatusManager::Instance().HeartCount();
				itr = enemy.erase(itr);
			}
			else {
				itr = enemy.erase(itr);
				continue;
			}
		}
	}
}

void EnemyManager::Generator() {
	std::unique_ptr<EnemyFactory> factory = std::make_unique<EnemyFactory>();

	if (!appear_flag[count])
	{
		//!“G‚Ìí—ŞE‰ŠúÀ•W‚ğ“n‚µ‚Ä“G‚ğ»‘¢
		enemy.push_back(factory->Create(tag[count],time_stop_flag[count], appear_pos[count]));
		appear_flag[count] = true;
	}

}

void EnemyManager::Render()
{
	for (auto& enemies : enemy) {
		enemies->Render();
	}
}

void EnemyManager::EndTimeStop() {
	if (DXTK->KeyEvent->pressed.Z)
		enemy_stop_flag = false;
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
	
	auto pos = player_data->GetModel()->GetPosition();
	DX12Effect.Play("special", SimpleMath::Vector3(pos.x, 0, pos.z));
	
	special_move_flag = true;
}

void EnemyManager::OnCollisionAudience(EnemyBase* base) {
	base->Damage(20);

	auto pos = player_data->GetModel()->GetPosition();
	DX12Effect.Play("special", SimpleMath::Vector3(pos.x, 0, pos.z));

	special_move_flag = true;
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
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> destract_num[i] >> time_stop_flag[i];
	}

	EndEnemy();
}

void EnemyManager::EndEnemy() {
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (tag[i] == "") {
			enemy_num = i;
			break;
		}
	}
}

