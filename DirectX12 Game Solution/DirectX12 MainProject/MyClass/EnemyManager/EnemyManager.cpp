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
	DX12Effect.Create(L"Effect/test/test.efk","hit_eff");

	player_data = player_base;

	LoadEnemyArrangement();
	return true;
}

int EnemyManager::Update(SimpleMath::Vector3 player, const float deltaTime)
{
	for (auto& enemies : enemy) {
		enemies->Update(player,deltaTime);
	}

	delta		= deltaTime;

	Iterator(player,delta);

	if (frame < MAX_FRAME)
		++frame;
	else {
		frame = 0;
		++timer;
	}

	if (count < ENEMY_NUM) {
		if (timer > appear_time[count] || dead_enemy_count >= destract_num[count]) {
			Generator();
			count++;
		}
	}

	return 0;
}

void EnemyManager::Iterator(SimpleMath::Vector3 player, const float deltaTime) {
	auto itr = enemy.begin();

	while (itr != enemy.end())
	{
		if ((*itr)->Update(player,deltaTime) == LIVE)
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
     base->Damage(delta,player_data->GetDamage());

	 std::string tag = base->GetTag();

	 if (tag != "C") {
		 if (StatusManager::Instance().GetCombo() == 3)
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

void EnemyManager::OnParryArea(EnemyBase* base) {
	if (base->GetTag() != "C")
		base->Retreat();
	else
		base->BulletParry();
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

	//! 1�`3�s��ǂݔ�΂�
	for (int i = 0; i < DUMMY_LINE; ++i) {
		getline(pos_time_infile, dummy_line);
	}

	//!�f�[�^�ǂݍ���
	for (int i = 0; i < ENEMY_NUM; ++i) {
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> destract_num[i];
	}
}

