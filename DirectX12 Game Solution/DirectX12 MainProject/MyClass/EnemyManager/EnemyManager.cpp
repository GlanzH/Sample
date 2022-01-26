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
		tag[i]            = "";
		appear_pos[i]     = SimpleMath::Vector3(DBL_MAX, DBL_MAX, DBL_MAX);
		appear_time[i]    = DBL_MAX;
		appear_flag[i]    = false;
		wave_num[i]       = INT_MAX;
		init_wait[i]      = DBL_MAX;
		stop_pos[i]       = DBL_MAX;
		move_speed[i]     = DBL_MAX;
		posture[i]        = "";
		move_direct[i]    = "";
	}
}

EnemyManager::~EnemyManager() {
	for (auto& enemies : enemy) {
		delete enemies;
	}
}

bool EnemyManager::Initialize(PlayerBase* player_base)
{
	//DX12Effect.Create(L"Effect/EnemyEffect/deathblow_hit/deathblow_hit.efk", "special");
	//DX12Effect.Create(L"Effect/EnemyEffect/boss_death/boss_death.efk", "boss");

	hit  = std::make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/Enemy/hit_se.wav");
	die  = std::make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/Enemy/enemy_die_se.wav");
	kill = std::make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/Audience/kill_se.wav");

	player_data = player_base;
	appear_frame = 0.0f;
	LoadEnemyArrangement();
	return true;
}

int EnemyManager::Update(SimpleMath::Vector3 player, int attack, bool destroy_flag, const float deltaTime)
{	
	enemy_destroy_flag = destroy_flag;
	attack_num = attack;
	delta      = deltaTime;
	
	for (auto& enemies : enemy) {
		enemies->Update(player, destroy_flag, delta);
	}

	Iterator();

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

						dead_enemy_count++;
					}
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
		//!�G�̎�ށE�������W��n���ēG�𐻑�
		enemy.push_back
		(
			factory->Create(
				tag[count],
				init_wait[count], 
				stop_pos[count],
				appear_pos[count],
				move_speed[count],
				move_direct[count],
				posture[count]
			)
		);
		appear_flag[count] = true;
	}

}

float EnemyManager::AppearTime() {
	if (appear_frame < max_appear_frame) {
		appear_frame++;
	}
	else {
		appear_frame = 0;
		now_time++;
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

	if (push_count > 2 && enemy_stop_flag) {
		enemy_stop_flag = false;
	}
	if (!enemy_stop_flag) {
		push_count = 0;
	}
	//else if (time_stop_count == 4 && push_count >= 1) {
	//	push_count = 0;
	//	enemy_stop_flag = false;
	//}
}

void EnemyManager::OnCollisionEnter(EnemyBase* base) {
	 std::string tag = base->GetTag();

	 if (!hit->IsInUse())
		 hit->Play();

	 //��i�U��
	 if (base->FrontFlag() && base->GetTag() != "SH") {
		 if (base->GetPostune() == "U") {
			 if (attack_num == LOWER) {
				 base->Damage();
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
				 base->Damage();
				 base->HitEffect();
			 }
		 }
	 }
	 else {
		 base->Damage();
		 base->HitEffect();
	 }
}

void EnemyManager::OnThrustCollisionEnter(EnemyBase* base) {
	hit->Play();

	base->Damage();
}

void EnemyManager::OnCollisionSpecialMove(EnemyBase* base) {
	if (!hit->IsInUse())
		hit->Play();
	//base->Damage(20);
	
	auto pos = player_data->GetModel()->GetPosition();
	DX12Effect.Play("special", SimpleMath::Vector3(pos.x, 0, pos.z));
	
	special_move_flag = true;
}

void EnemyManager::OnCollisionAudience(EnemyBase* base) {
	if (!hit->IsInUse())
		hit->Play();
	//base->Damage(20);

	auto pos = player_data->GetModel()->GetPosition();
	DX12Effect.Play("special", SimpleMath::Vector3(pos.x, 0, pos.z));

	special_move_flag = true;
}

void EnemyManager::LoadEnemyArrangement() {
	std::ifstream pos_time_infile("EnemyArrangement/EnemyArrangement.txt");

	std::string dummy_line;

	//!�ǂݔ�΂�
	for (int i = 0; i < DUMMY_LINE; ++i) {
		getline(pos_time_infile, dummy_line);
	}

	//!�f�[�^�ǂݍ���
	for (int i = 0; i < ENEMY_NUM; ++i) {
		pos_time_infile >> tag[i] >> appear_pos[i].x >> appear_pos[i].y >> appear_pos[i].z >> appear_time[i] >> wave_num[i] 
			            >> init_wait[i] >> stop_pos[i] >> move_speed[i] >> move_direct[i] >> posture[i];
	}
}

int EnemyManager::GetWaveEnemy() {
	for (int i = 0; i < ENEMY_NUM; ++i) {
		if (wave_num[i] == StatusManager::Instance().GetWave())
			enemy_num++;
	}

	return enemy_num;
}