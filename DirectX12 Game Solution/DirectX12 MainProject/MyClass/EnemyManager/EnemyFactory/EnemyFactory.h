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
	EnemyBase* Create(std::string tag, DirectX::SimpleMath::Vector3 position);
	EnemyBase* CreateProduct(std::string tag, DirectX::SimpleMath::Vector3 position);
	LPCWSTR SetModel(std::string tag);
	DirectX::SimpleMath::Vector3 SetSpeed(std::string tag);
	int SetHP(std::string tag);


private:
	EnemyBase* enemy;
	int hp;
	int Slime_hp;
	int HighSlime_hp;
	int FakerLamiel_hp;
	int StoneStatue_hp;
	int StoneStatueCore_hp;
	std::vector<std::string> enemy_tag;

	DirectX::SimpleMath::Vector3 slime_speed;
	DirectX::SimpleMath::Vector3 high_slime_speed;
	DirectX::SimpleMath::Vector3 faker_lamiel_speed;
	DirectX::SimpleMath::Vector3 statue_speed;

	DirectX::SimpleMath::Vector3 stone_core_speed;

	DirectX::SimpleMath::Vector3 speed;

	LPCWSTR enemy_model[5];
	LPCWSTR model_name;
	/**
�@�@* @enum EnemyType
�@�@* �G�̎��
�@�@*/
	enum EnemyType { SLIME, HIGH_SLIME, FAKER_LAMIEL, STONE_STATUE,STONE_CORE };
};
