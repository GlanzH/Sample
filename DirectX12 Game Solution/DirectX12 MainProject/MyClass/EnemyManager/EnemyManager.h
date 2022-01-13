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
	int  Update(SimpleMath::Vector3 player,int attack_tag, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	void OnDeviceLost();
	void Render();

	std::vector<EnemyBase*> GetEnemy() { return enemy; }
	int  GetDeathEnemyCount()		   { return dead_enemy_count; }
	int  GetTimeStopCount()			   { return time_stop_count; }


	int  GetEnemyNum() { return enemy_num; }
	void StartTimeStop();
	void EndTimeStop();
	bool IsTimeStop() { return enemy_stop_flag; }

	void OnCollisionEnter(EnemyBase* base);
	void OnThrustCollisionEnter(EnemyBase* base);
	void OnCollisionAudience(EnemyBase* base);
	void OnCollisionSpecialMove(EnemyBase* base);
private:
	void LoadEnemyArrangement();
	void NowDestEnemyCount();
	void EndEnemy();
	void CalcScore();
	void Generator();
	void Iterator();

	std::vector<EnemyBase*> enemy;

	PlayerBase* player_data;

	DX9::SKINNEDMODEL model;
	
	std::unique_ptr<SoundEffect> hit,die,kill;
	
	int now_dead_enemy   = 0;
	int dead_enemy_count = 0;
	int time_stop_count  = 0;

	float delta;

	float count_frame = 0.0f;
	const float max_count = 0.1f;

	const float max_frame = 60.0f;
	const float fix_pos   = 10.0f;

	int add_score = 0;
	int attack_num = 0;
	int enemy_num = 0;
	int push_count = 0;

	bool enemy_stop_flag   = false;
	bool special_move_flag = false;
	bool count_dest_flag   = false;
	bool sound_hit_flag    = false;

	const int max_combo = 3;

	enum KillNum {
		ONE   = 1,
		TWO   = 2,
		THREE = 3,
		FOUR  = 4
	};

	enum AddScore {
		ONE_SCORE       = 20,
		TWO_SCORE       = 40,
		THREE_SCORE     = 80,
		FOUR_SCORE      = 160,
		OVER_FIVE_SCORE = 320
	};

	enum LoadFile {
		DUMMY_LINE = 7,
		ENEMY_NUM = 250 
	};


	enum TimeStop {
		MOVE,
		TIME_STOP
	};

	int count = 0;                          //!敵の累計出現数カウント 
	std::string  tag[ENEMY_NUM];            //!敵の種類         
	Vector3		 appear_pos[ENEMY_NUM];     //!敵の出現座標
	double		 destract_num[ENEMY_NUM];   //!敵の出現時間
	bool		 appear_flag[ENEMY_NUM];    //!敵の出現フラグ
	bool         time_stop_flag[ENEMY_NUM]; //!敵の演出フラグ
};
