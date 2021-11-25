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

	bool Initialize();
	int  Update(PlayerBase* player, const float deltaTime);
	void Render();

	std::list<EnemyBase*> GetEnemy() { return enemy; }
	int  GetDeathEnemyCount()		 { return dead_enemy_count; }

	void OnCollisionEnter(EnemyBase* base);
	void OnParryArea(EnemyBase* base);
	
private:
	void LoadEnemyArrangement();
	void Generator();
	void Iterator(PlayerBase* player, const float deltaTime);
	
	int AppearTimer();

	std::list<EnemyBase*> enemy;

	PlayerBase* player_data;

	EFFECTHANDLE handle;
	EFFECT       effect;
	DX9::SPRITEFONT font;
	DX9::SKINNEDMODEL model;
	
	int dead_enemy_count = 0;
	float delta;

	int frame = 0;
	int timer = 0;

	enum {MAX_FRAME = 60};

	enum LoadFile { DUMMY_LINE = 4, ENEMY_NUM = 250 };

	int count = 0;                   //!敵の累計出現数カウント 
	std::string  tag[ENEMY_NUM];          //!敵の種類         
	Vector3		 appear_pos[ENEMY_NUM];   //!敵の出現座標  
	double		 appear_time[ENEMY_NUM];  //!敵の出現時間
	double		 destract_num[ENEMY_NUM];//!敵の出現時間
	bool		 appear_flag[ENEMY_NUM];  //!敵の出現フラグ 
};
