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

class EnemyBase;

class EnemyFactory {
public:
	EnemyFactory();
	~EnemyFactory() {};
	EnemyBase* Create(std::string tag, bool time_stop_flag,DirectX::SimpleMath::Vector3 position);
	EnemyBase* CreateProduct(std::string tag, bool time_stop_flag,DirectX::SimpleMath::Vector3 position);
	LPCWSTR SetModel(std::string tag);
	int SetHP(std::string tag);


private:
	EnemyBase* enemy;
	int hp;
	int slime_hp;
	int high_slime_hp;
	int faker_lamiel_hp;
	int stone_statue_hp;
	int stone_statue_core_hp;
	int foot_hold_hp;
	std::vector<std::string> enemy_tag;

	/**
　　* @enum EnemyType
　　* 敵の種類
　　*/
	enum EnemyType { 
		SLIME,
		HIGH_SLIME,
		FAKER_LAMIEL,
		STONE_STATUE,
		STONE_CORE,
		FOOT_HOLD,
		MODEL_MAX
	};

	enum EnemyHp {
		SLIME_HP      =  2,
		HIGH_SLIME_HP =  7,
		LAMIEL_HP     = 30,
		STONE_CORE_HP = 60
	};

	LPCWSTR enemy_model[MODEL_MAX];
	LPCWSTR model_name;
};
