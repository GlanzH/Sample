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
			//敵が死亡したときの処理
			dead_enemy_count++;
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

void EnemyManager::OnCollisionEnter(EnemyBase* base) {;
     base->Damage(delta,player_data->GetDamage());

	if(StatusManager::Instance().GetCombo() == 3)
	base->Retreat();

	SimpleMath::Vector3 pos;

	if(base->GetTag() == "S" || base->GetTag() == "H")
	   pos = base->GetAnimModel()->GetPosition();
	else
		pos = base->Get

	DX12Effect.SetPosition("hit_eff", SimpleMath::Vector3(pos.x - fix_pos,pos.y - fix_pos,-fix_pos));
	DX12Effect.Play("hit_eff");

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

	//! 1〜3行を読み飛ばし
	for (int i = 0; i < DUMMY_LINE; ++i) {
		getline(pos_time_infile, dummy_line);
	}

	//!データ読み込み
	for (int i = 0; i < ENEMY_NUM; ++i) {
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> destract_num[i];
	}
}

