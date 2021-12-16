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
	int  Update(SimpleMath::Vector3 player,bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	void OnDeviceLost();
	void Render();

	std::vector<EnemyBase*> GetEnemy() { return enemy; }
	int  GetDeathEnemyCount()		   { return dead_enemy_count; }
	int  GetTimeStopCount()			   { return time_stop_count; }

	int  GetEnemyNum() { return enemy_num; }
	void StartTimeStop();
	void EndTimeStop();
	bool IsTimeStop() { return enemy_stop_flag; }
	bool EndWaitTime();

	void OnCollisionEnter(EnemyBase* base);
	void OnCollisionAudience(EnemyBase* base);
	void OnCollisionSpecialMove(EnemyBase* base);
private:
	void LoadEnemyArrangement();
	void EndEnemy();
	void Generator();
	void Iterator();
	
	int AppearTimer();

	std::vector<EnemyBase*> enemy;
	EnemyBase enemy_base;

	PlayerBase* player_data;

	DX9::SKINNEDMODEL model;
	
	std::unique_ptr<SoundEffect> hit,die,kill;
	
	int dead_enemy_count = 0;
	int time_stop_count  = 0;
	float delta;

	const float max_frame = 60.0f;
	const float fix_pos   = 10.0f;

	int frame = 0;
	int timer = 0;
	int enemy_num = 0;
	int push_count = 0;

	bool enemy_stop_flag   = false;
	bool special_move_flag = false;

	const int max_combo = 3;

	enum LoadFile {
		DUMMY_LINE = 7,
		ENEMY_NUM = 250 
	};


	enum TimeStop {
		MOVE,
		TIME_STOP
	};

	int count = 0;                          //!�G�̗݌v�o�����J�E���g 
	std::string  tag[ENEMY_NUM];            //!�G�̎��         
	Vector3		 appear_pos[ENEMY_NUM];     //!�G�̏o�����W  
	double		 appear_time[ENEMY_NUM];    //!�G�̏o������
	double		 destract_num[ENEMY_NUM];   //!�G�̏o������
	bool		 appear_flag[ENEMY_NUM];    //!�G�̏o���t���O
	bool         time_stop_flag[ENEMY_NUM]; //!�G�̉��o�t���O
};
