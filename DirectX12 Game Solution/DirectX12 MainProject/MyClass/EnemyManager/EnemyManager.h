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
	int  Update(SimpleMath::Vector3 player, const float deltaTime);
	void Render();

	std::list<EnemyBase*> GetEnemy() { return enemy; }
	int  GetDeathEnemyCount()		 { return dead_enemy_count; }

	void OnCollisionEnter(EnemyBase* base);
	void OnParryArea(EnemyBase* base);
	
private:
	void LoadEnemyArrangement();
	void Generator();
	void Iterator(SimpleMath::Vector3 player, const float deltaTime);
	
	int AppearTimer();

	std::list<EnemyBase*> enemy;

	PlayerBase* player_data;

	DX9::SPRITEFONT font;
	DX9::SKINNEDMODEL model;
	
	int dead_enemy_count = 0;
	float delta;

	const float fix_pos = 10.0f;

	int frame = 0;
	int timer = 0;

	enum Frame {MAX_FRAME = 60};

	enum LoadFile  { DUMMY_LINE = 5, ENEMY_NUM = 250 };

	int count = 0;                   //!�G�̗݌v�o�����J�E���g 
	std::string  tag[ENEMY_NUM];          //!�G�̎��         
	Vector3		 appear_pos[ENEMY_NUM];   //!�G�̏o�����W  
	double		 appear_time[ENEMY_NUM];  //!�G�̏o������
	double		 destract_num[ENEMY_NUM];//!�G�̏o������
	bool		 appear_flag[ENEMY_NUM];  //!�G�̏o���t���O 
};
