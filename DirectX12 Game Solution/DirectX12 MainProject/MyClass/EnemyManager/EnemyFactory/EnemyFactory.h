#pragma once

/**
 * @file   EnemyFactory.h
 * @brief  敵の製造を行っているクラス
 * @author HASHIMOTO HIKARU
 * @date 　2021/10/31
 */

#include "MyClass/EnemyManager/EnemyFactory/EnemyBase/Enemy/Enemy.h"
#include "Base/pch.h"
#include<string>
#include<vector>

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
	char hp;
	char normal_enemy_hp;

	std::vector<std::string> enemy_tag;

	DirectX::SimpleMath::Vector3 normal_enemy_speed;
	DirectX::SimpleMath::Vector3 speed;

	LPCWSTR enemy_model[1];
	LPCWSTR model_name;
	/**
　　* @enum EnemyType
　　* 敵の種類
　　*/
	enum EnemyType {NORMAL};
};