#pragma once

#include "Base/DX12Effekseer.h"
#include "../EnemyManager/EnemyFactory/EnemyFactory.h"
#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerManager.h"

using namespace DirectX;

class EnemyManager
{
public:

	EnemyManager();
	~EnemyManager();

	bool Initialize();
	int  Update(PlayerManager* player, const float deltaTime);
	void Render();

	std::list<EnemyBase*> GetEnemy() { return enemy; }
	int  GetDeathEnemyCount()		 { return dead_enemy_count; }

	void OnCollisionEnter(EnemyBase* base);
	void OnParryArea(EnemyBase* base);
	
private:
	void LoadEnemyArrangement();
	void Generator();
	void Iterator(PlayerManager* player, const float deltaTime);
	
	int AppearTimer();

	std::list<EnemyBase*> enemy;

	PlayerManager* player_data;

	EFFECTHANDLE handle;
	EFFECT       effect;
	DX9::SPRITEFONT font;
	DX9::SKINNEDMODEL model;
	
	int dead_enemy_count = 0;
	float delta;
	char MAX_COUNT;

	int frame = 0;
	int timer = 0;

	enum {MAX_FRAME = 60};

	enum LoadFile { DUMMY_LINE = 3, ENEMY_NUM = 250 };

	int count = 0;                   //!�G�̗݌v�o�����J�E���g 
	std::string  tag[ENEMY_NUM];          //!�G�̎��         
	Vector3		 appear_pos[ENEMY_NUM];   //!�G�̏o�����W  
	float		 appear_time[ENEMY_NUM];  //!�G�̏o������
	float		 destract_num[ENEMY_NUM];//!�G�̏o������
	bool		 appear_flag[ENEMY_NUM];  //!�G�̏o���t���O 
};
