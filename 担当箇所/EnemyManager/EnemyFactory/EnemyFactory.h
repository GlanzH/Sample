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

using namespace std;
using namespace DirectX;

class EnemyBase;

class EnemyFactory {
public:
	EnemyFactory();
	~EnemyFactory() {};
	EnemyBase* Create(string tag,double init_wait,double stop_pos,
		              SimpleMath::Vector3 position,double speed,string direct, string posture, int enemy_hp);

	EnemyBase* CreateProduct(string tag,SimpleMath::Vector3 position);
	LPCWSTR SetModel(string tag);


private:
	EnemyBase* enemy;
	/*int hp;
	int enemy_hp;
	int rand_hp;
	int arrow_hp;*/

	std::vector<std::string> enemy_tag;

	/**
�@�@* @enum EnemyType
�@�@* �G�̎��
�@�@*/
	enum EnemyType { 
		SWORD_MAN,
		SWORD_MANEX,
		SHIELDER,
		ARROW,
		MODEL_MAX
	};

	/*enum EnemyHp {
		ENEMY_HP = 1,
		RAND_HP  = 2
	};*/

	LPCWSTR enemy_model[MODEL_MAX];
	LPCWSTR model_name;
};
