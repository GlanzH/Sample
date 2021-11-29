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
	char StoneStatueCore_hp;
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
　　* @enum EnemyType
　　* 敵の種類
　　*/
	enum EnemyType { SLIME, HIGH_SLIME, FAKER_LAMIEL, STONE_STATUE,STONE_CORE };
};
