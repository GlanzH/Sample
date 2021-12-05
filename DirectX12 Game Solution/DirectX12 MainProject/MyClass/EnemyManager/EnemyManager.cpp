#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include<fstream>

EnemyManager::EnemyManager()
{
	//!�Ǎ��O�̓G�̏�����
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
	death_effect_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
	hit_effect_pos   = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);

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
			//�G�����S�����Ƃ��̏���
			dead_enemy_count++;

			auto tag = (*itr)->GetTag();

				if (tag == "S" || tag == "H")
					death_effect_pos = (*itr)->GetAnimModel()->GetPosition();
				else
					death_effect_pos = (*itr)->GetModel()->GetPosition();

				DX12Effect.PlayOneShot("die", death_effect_pos);

				itr = enemy.erase(itr);
		}
	}
}

void EnemyManager::Generator() {
	std::unique_ptr<EnemyFactory> factory = std::make_unique<EnemyFactory>();

	if (!appear_flag[count])
	{
		//!�G�̎�ށE�������W��n���ēG�𐻑�
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

	 if (tag == "S" || tag == "H")
		 hit_effect_pos = base->GetAnimModel()->GetPosition();
	 else
		 hit_effect_pos = base->GetModel()->GetPosition();
	
	 DX12Effect.PlayOneShot("hit_eff",hit_effect_pos);
	
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

	//! 1�`3�s��ǂݔ�΂�
	for (int i = 0; i < DUMMY_LINE; ++i) {
		getline(pos_time_infile, dummy_line);
	}

	//!�f�[�^�ǂݍ���
	for (int i = 0; i < ENEMY_NUM; ++i) {
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> destract_num[i];
	}
}

