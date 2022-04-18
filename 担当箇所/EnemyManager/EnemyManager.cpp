#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include<fstream>

EnemyManager::EnemyManager()
{
	//!“Ç‘O‚Ì“G‚Ì‰Šú‰»
	enemy = {};

	for (int i = 0; i < MAX_WAVE; ++i) {
		sum_wave_enemy[i] = 0;
		first_process_flag[i] = false;
	}

	for (int i = 0; i < ENEMY_NUM; ++i) {
		tag[i] = "";
		appear_pos[i] = SimpleMath::Vector3(DBL_MAX, DBL_MAX, DBL_MAX);
		appear_time[i] = DBL_MAX;
		appear_flag[i] = false;
		wave_num[i] = INT_MAX;
		init_wait[i] = DBL_MAX;
		stop_pos[i] = DBL_MAX;
		move_speed[i] = DBL_MAX;
		posture[i] = "";
		move_direct[i] = "";
		enemy_hp[i] = INT_MAX;
	}
}

EnemyManager::~EnemyManager() {
	for (auto& enemies : enemy) {
		delete enemies;
	}
}

bool EnemyManager::Initialize(PlayerBase* player_base)
{
	hit = std::make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/Enemy/hit_se.wav");
	die = std::make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/Enemy/enemy_die_se.wav");
	kill = std::make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/Audience/kill_se.wav");

	player_data = player_base;
	appear_frame = 0.0f;
	attack_num = 0;
	LoadEnemyArrangement();

	count = 0;

	dead_enemy_count = 0;
	remain_enemy_count = 0;
	time_stop_count = 0;

	appear_frame = 0;

	now_time = 0.0f;
	count_frame = 0.0f;

	add_score = 0;
	attack_num = 0;
	enemy_num = 0;
	push_count = 0;

	enemy_stop_flag = false;
	special_move_flag = false;
	count_dest_flag = false;
	sound_hit_flag = false;
	temporary_flag = false;
	enemy_destroy_flag = false;
	death_flag = false;
	return true;
}

int EnemyManager::Update(SimpleMath::Vector3 player, int attack, bool destroy_flag, const float deltaTime)
{
	enemy_destroy_flag = destroy_flag;
	attack_num = attack;
	delta = deltaTime;

	for (auto& enemies : enemy) {
		enemies->Update(player, destroy_flag, delta);
	}

	
	Iterator();
	//AllDeathBonus();

	if (count < ENEMY_NUM) {
		if (AppearTime() >= appear_time[count] && wave_num[count] == StatusManager::Instance().GetWave()) {
			Generator();
			count++;
		}
	}


	return 0;
}

void EnemyManager::Iterator() {
	for (auto itr = enemy.begin(); itr != enemy.end();)
	{
		if (enemy_destroy_flag) {
			(*itr)->DieFlag();
		}

		if ((*itr)->LifeDeathDecision() == LIVE) {
			itr++;
		}
		else {
			if ((*itr)->LifeDeathDecision() != LIVE) {

				if ((*itr)->GetTag() != "AR") {
					if ((*itr)->GetTemporaryDeathFlag()) {
						if (!kill->IsInUse())
							kill->Play();
					}

					death_flag = true;
					dead_enemy_count++;
				}

				if (StatusManager::Instance().GetTime() == 0.0f) {
					(*itr)->AutoDestoryEffect();
					remain_enemy_count++;
				}
				else {
					remain_enemy_count = 0;
				}

				itr = enemy.erase(itr);
			}
		}
	}
}

void EnemyManager::Render()
{
	for (auto& enemies : enemy) {
		enemies->Render();
	}
}

bool EnemyManager::GetTemporaryDeath() {
	for (auto& enemies : enemy) {
		if (enemies->GetTemporaryDeathFlag())
			return true;
	}

	return false;
}

void EnemyManager::Generator() {
	std::unique_ptr<EnemyFactory> factory = std::make_unique<EnemyFactory>();

	if (!appear_flag[count])
	{
		//!“G‚Ìí—ŞE‰ŠúÀ•W‚ğ“n‚µ‚Ä“G‚ğ»‘¢
		enemy.push_back
		(
			factory->Create(
				tag[count],
				init_wait[count],
				stop_pos[count],
				appear_pos[count],
				move_speed[count],
				move_direct[count],
				posture[count],
				enemy_hp[count]
			)
		);
		appear_flag[count] = true;
	}

}
//
//void EnemyManager::AllDeathBonus() {
//	if (GetWaveEnemy() - dead_enemy_count == 0 && GetWaveEnemy() != 0) {
//		int time = (int)StatusManager::Instance().GetTime();
//
//		StatusManager::Instance().SetAddScore(time);
//		StatusManager::Instance().ResetWaveTime();
//	}
//}

float EnemyManager::AppearTime() {
	if (StatusManager::Instance().GetTime() == 0.0f) {
		now_time = 0.0f;
		appear_frame = 0.0f;
	}
	else {
		if (appear_frame < max_appear_frame) {
			appear_frame++;
		}
		else {
			appear_frame = 0;
			now_time++;
		}
	}

	return now_time;
}

void EnemyManager::StartTimeStop() {
	if (!enemy_stop_flag) {
		time_stop_count++;
		enemy_stop_flag = true;
	}
}

void EnemyManager::EndTimeStop() {
	if (DXTK->KeyEvent->pressed.B || DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED)
		push_count++;

	if (push_count >= 2 && enemy_stop_flag) {
		enemy_stop_flag = false;
	}
	if (!enemy_stop_flag) {
		push_count = 0;
	}
}

void EnemyManager::OnCollisionEnter(EnemyBase* base) {
	bool front = base->FrontFlag();

	if (!hit->IsInUse())
		hit->Play();

	//ã’iUŒ‚
	if (front && base->GetTag() != "SH") {
		if (base->GetPostune() == "U") {
			if (attack_num == LOWER) {
				base->IsCollision();
				base->HitEffect();
			}

			if (attack_num == UPPER) {
				base->Retreat();
			}
		}
		if (base->GetPostune() == "D") {
			if (attack_num == LOWER) {
				base->Retreat();
			}

			if (attack_num == UPPER) {
				base->IsCollision();
				base->HitEffect();
			}
		}
	}
	else {
		if (!front) {
			base->IsCollision();
			base->HitEffect();
		}
		else
		{
			base->OffCollision();
		}
	}
}

void EnemyManager::LoadEnemyArrangement() {
	std::ifstream pos_time_infile("EnemyArrangement/EnemyArrangement.txt");

	std::string dummy_line;

	//!“Ç‚İ”ò‚Î‚µ
	for (int i = 0; i < DUMMY_LINE; ++i) {
		getline(pos_time_infile, dummy_line);
	}

	//!ƒf[ƒ^“Ç‚İ‚İ
	for (int i = 0; i < ENEMY_NUM; ++i) {
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> wave_num[i]
			>> init_wait[i] >> stop_pos[i] >> move_speed[i] >> move_direct[i] >> posture[i] >> enemy_hp[i];
	}

	SumWaveEnemy();
}

void EnemyManager::SumWaveEnemy() {
	for (int i = 0; i < ENEMY_NUM; ++i) {
		for (int j = 1; j < MAX_WAVE; ++j) {
			if (wave_num[i] == j)
				sum_wave_enemy[j]++;
		}
	}
}

int EnemyManager::GetWaveEnemy() {
	return sum_wave_enemy[StatusManager::Instance().GetWave()];
}