#pragma once

/**
 * @file   EnemyFactory.h
 * @brief  �G�̐������s���Ă���N���X
 * @author HASHIMOTO HIKARU
 * @date �@2021/10/31
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
	int enemy_hp;
	int mid_boss_hp;
	int arrow_hp;

	std::vector<std::string> enemy_tag;

	/**
�@�@* @enum EnemyType
�@�@* �G�̎��
�@�@*/
	enum EnemyType { 
		SWORD_MAN,
		SHIELDER,
		MID_BOSS,
		ARROW,
		MODEL_MAX
	};

	enum EnemyHp {
		ENEMY_HP    = 2,
		MID_BOSS_HP = 4
	};

	LPCWSTR enemy_model[MODEL_MAX];
	LPCWSTR model_name;
};
