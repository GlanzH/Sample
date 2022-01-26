#pragma once

/**
 * @file   EnemyFactory.h
 * @brief  敵の製造を行っているクラス
 * @author HASHIMOTO HIKARU
 * @date 　2021/10/31
 */

#include "Base/pch.h"
#include<string>
#include<vector>

#include "EnemyBase/EnemyBase.h"

using namespace std;
using namespace DirectX;

class EnemyBase;

class EnemyFactory {
public:
	EnemyFactory();
	~EnemyFactory() {};
	EnemyBase* Create(string tag,double init_wait,double stop_pos,
		              SimpleMath::Vector3 position,double speed,string direct, string posture);

	EnemyBase* CreateProduct(string tag,SimpleMath::Vector3 position);
	LPCWSTR SetModel(string tag);
	int SetHP(string tag);


private:
	EnemyBase* enemy;
	int hp;
	int enemy_hp;
	int mid_boss_hp;
	int arrow_hp;

	std::vector<std::string> enemy_tag;

	/**
　　* @enum EnemyType
　　* 敵の種類
　　*/
	enum EnemyType { 
		SWORD_MAN,
		SHIELDER,
		MID_BOSS,
		ARROW,
		MODEL_MAX
	};

	enum EnemyHp {
		ENEMY_HP    = 1,
		MID_BOSS_HP = 4
	};

	LPCWSTR enemy_model[MODEL_MAX];
	LPCWSTR model_name;
};
