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
	int  Update(SimpleMath::Vector3 player, const float deltaTime);
	void Render();

	std::list<EnemyBase*> GetEnemy() { return enemy; }
	int  GetDeathEnemyCount()		 { return dead_enemy_count; }

	void OnCollisionEnter(EnemyBase* base);
	void OnParryArea(EnemyBase* base);
	
private:
	void LoadEnemyArrangement();
	void Generator();
	void Iterator();
	
	int AppearTimer();

	SimpleMath::Vector3 effect_pos;

	std::list<EnemyBase*> enemy;

	PlayerBase* player_data;

	DX9::SPRITEFONT font;
	DX9::SKINNEDMODEL model;
	
	int dead_enemy_count = 0;
	float delta;

	const float max_frame = 60.0f;
	const float fix_pos   = 10.0f;

	int frame = 0;
	int timer = 0;

	const int max_combo = 3;

	float death_frame = 0.0f;
	const  float max_death_frame = 0.5f;

	enum LoadFile  { DUMMY_LINE = 6, ENEMY_NUM = 250 };

	int count = 0;                        //!敵の累計出現数カウント 
	std::string  tag[ENEMY_NUM];          //!敵の種類         
	Vector3		 appear_pos[ENEMY_NUM];   //!敵の出現座標  
	double		 appear_time[ENEMY_NUM];  //!敵の出現時間
	double		 destract_num[ENEMY_NUM];//!敵の出現時間
	bool		 appear_flag[ENEMY_NUM];  //!敵の出現フラグ 
};
