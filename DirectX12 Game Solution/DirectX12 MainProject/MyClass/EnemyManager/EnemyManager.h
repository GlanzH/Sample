#pragma once

#include "Base/DX12Effekseer.h"
#include "../EnemyManager/EnemyFactory/EnemyFactory.h"
#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;


class EnemyManager
{
public:

	EnemyManager();
	~EnemyManager();

	bool Initialize(PlayerBase* player_base);
	int  Update(SimpleMath::Vector3 player, int attack, bool destroy_flag, const float deltaTime);
	void OnDeviceLost();
	void Render();

	std::vector<EnemyBase*> GetEnemy() { return enemy; }

	int  GetWaveEnemy();
	int  GetRemainEnemy() { return remain_enemy_count; }
	int  GetDeathEnemyCount() { return dead_enemy_count; }
	int  ResetRemainEnemy() { return remain_enemy_count = 0; }
	int  ResetDeathEnemy() { return dead_enemy_count = 0; }
	int  GetTimeStopCount() { return time_stop_count; }

	void StartTimeStop();
	void EndTimeStop();
	bool IsTimeStop() { return enemy_stop_flag; }
	bool GetTemporaryDeath();

	void OnCollisionEnter(EnemyBase* base);
	void OnThrustCollisionEnter(EnemyBase* base);
	void OnCollisionAudience(EnemyBase* base);
	void OnCollisionSpecialMove(EnemyBase* base);
private:
	void  AllDeathBonus();
	void  SumWaveEnemy();
	float AppearTime();
	void  LoadEnemyArrangement();
	void  Generator();
	void  Iterator();

	std::vector<EnemyBase*> enemy;

	PlayerBase* player_data;

	DX9::SKINNEDMODEL model;

	std::unique_ptr<SoundEffect> hit, die, kill;

	int dead_enemy_count = 0;
	int remain_enemy_count = 0;

	int time_stop_count = 0;

	float delta;

	int appear_frame = 0;
	const int max_appear_frame = 60;

	float now_time = 0.0f;

	float count_frame = 0.0f;
	const float max_count = 0.1f;

	const float max_frame = 60.0f;
	const float fix_pos = 10.0f;

	int add_score = 0;
	int attack_num = 0;
	int enemy_num = 0;
	int push_count = 0;

	bool enemy_stop_flag = false;
	bool special_move_flag = false;
	bool count_dest_flag = false;
	bool sound_hit_flag = false;
	bool temporary_flag = false;
	bool enemy_destroy_flag = false;

	enum LoadFile {
		DUMMY_LINE = 8,
		ENEMY_NUM = 250
	};

	enum TimeStop {
		MOVE,
		TIME_STOP
	};

	enum SumEnemy {
		MAX_WAVE = 10
	};

	int count = 0;                          //!�G�̗݌v�o�����J�E���g 
	std::string tag[ENEMY_NUM];            //!�G�̎��         
	Vector3		appear_pos[ENEMY_NUM];     //!�G�̏o�����W
	double		appear_time[ENEMY_NUM];    //!�G�̏o������
	bool		appear_flag[ENEMY_NUM];    //!�G�̏o���t���O
	int         wave_num[ENEMY_NUM];       //!�E�F�[�u��
	double      init_wait[ENEMY_NUM];      //!�����ҋ@����
	double      stop_pos[ENEMY_NUM];       //!�ꎞ��~X���W
	double      move_speed[ENEMY_NUM];     //!�ړ����x
	std::string posture[ENEMY_NUM];        //!�\��
	std::string move_direct[ENEMY_NUM];    //!�ړ�����

	bool first_process_flag[MAX_WAVE];
	int  sum_wave_enemy[MAX_WAVE];
};
