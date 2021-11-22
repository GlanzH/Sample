#include "EnemyFactory.h"
#include "MyClass/EnemyManager/EnemyFactory/EnemyBase/Slime/Slime.h"
#include"EnemyBase/HighSlime/HighSlime.h"
#include"EnemyBase/FakerLamiel/FakerLamiel.h"
#include"EnemyBase/StoneStatue/StoneStatue.h"


EnemyFactory::EnemyFactory()
{
	///@各敵のステータス設定@///
	slime_speed.x = 3.0f;
	FakerLamiel_speed.x = 1.0f;
	slime_hp       = 5;
	highslime_hp   = 7;
	fakerlamiel_hp = 30;
	stonestatue_hp = 60;
	///@敵の種類のタグをプッシュバック@///
	enemy_tag.push_back("slime");
    enemy_tag.push_back("highslime");
    enemy_tag.push_back("fakerlamiel");
    enemy_tag.push_back("stonestatue");
	///@敵のモデル@///
   enemy_model[SLIME]       = L"Model\\Enemy\\slime.X";
   enemy_model[HIGHSLIME]   = L"Model\\Enemy\\slime.X";
   enemy_model[FAKERLAMIEL] = L"Model\\Enemy\\slime.X";
   enemy_model[STONESTATUE] = L"Model\\Enemy\\slime.X";
}

EnemyBase* EnemyFactory::Create(std::string tag, DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* enemy_factory = CreateProduct(tag, position);
	enemy_factory->Initialize(SetSpeed(tag), SetHP(tag));
	enemy_factory->LoadAsset(SetModel(tag), position);
	
	return enemy_factory;
}

EnemyBase* EnemyFactory::CreateProduct(std::string tag, DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* classes[] = { new Slime};


	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { enemy = classes[i]; }
	}

	return enemy;
}

LPCWSTR EnemyFactory::SetModel(std::string tag)
{
	LPCWSTR models[] = { enemy_model[SLIME] };
	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { model_name = models[i]; }
	}
	return model_name;
}

DirectX::SimpleMath::Vector3 EnemyFactory::SetSpeed(std::string tag)
{
	DirectX::SimpleMath::Vector3 speeds[] = { slime_speed };
	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { speed = speeds[i]; }
	}
	return speed;
}

int EnemyFactory::SetHP(std::string tag)
{
	int hps[] = { slime_hp};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { hp = hps[i]; }
	}
	return hp;
}