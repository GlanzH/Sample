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

class EnemyBase;

class EnemyFactory {
public:
	EnemyFactory();
	~EnemyFactory() {};
	EnemyBase* Create(std::string tag, DirectX::SimpleMath::Vector3 position);
	EnemyBase* CreateProduct(std::string tag, DirectX::SimpleMath::Vector3 position);
	LPCWSTR SetModel(std::string tag);
	DirectX::SimpleMath::Vector3 SetSpead(std::string tag);
	int SetHP(std::string tag);

private:
	LPCWSTR Model_name;
	DirectX::SimpleMath::Vector3 Speed;
	char HP;
	EnemyBase* enemy;
	//!動く敵キャラのステータス
	DirectX::SimpleMath::Vector3 NormalEnemy_speed;
	int     NormalEnemy_hp;
	std::vector<std::string> _enemytag;
	LPCWSTR enemy_model[1];
	/**
　　* @enum EnemyType
　　* 敵の種類
　　*/
	enum EnemyType {NORMAL};
};