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
	char slime_hp;
	char highslime_hp;
	char fakerlamiel_hp;
	char stonestatue_hp;
	std::vector<std::string> enemy_tag;

	DirectX::SimpleMath::Vector3 slime_speed;
	DirectX::SimpleMath::Vector3 FakerLamiel_speed;

	DirectX::SimpleMath::Vector3 speed;

	LPCWSTR enemy_model[1];
	LPCWSTR model_name;
	/**
　　* @enum EnemyType
　　* 敵の種類
　　*/
	enum EnemyType {SLIME,HIGHSLIME,FAKERLAMIEL,STONESTATUE};
};