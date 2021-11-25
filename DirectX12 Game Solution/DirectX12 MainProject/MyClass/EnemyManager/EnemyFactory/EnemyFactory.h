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
	char hp{};
	char Slime_hp;
	char HighSlime_hp;
	char FakerLamiel_hp;
	char StoneStatue_hp;
	std::vector<std::string> enemy_tag;

	DirectX::SimpleMath::Vector3 Slime_speed;
	DirectX::SimpleMath::Vector3 HighSlime_speed;
	DirectX::SimpleMath::Vector3 FakerLamiel_speed;

	DirectX::SimpleMath::Vector3 speed;

	LPCWSTR enemy_model[3];
	LPCWSTR model_name;
	/**
�@�@* @enum EnemyType
�@�@* �G�̎��
�@�@*/
	enum EnemyType { SLIME, HIGHSLIME, FAKERLAMIEL, STONESTATUE };
};