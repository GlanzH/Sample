#include "EnemyFactory.h"
#include "MyClass/EnemyManager/EnemyFactory/EnemyBase/Slime/Slime.h"
#include"EnemyBase/HighSlime/HighSlime.h"
#include"EnemyBase/FakerLamiel/FakerLamiel.h"
#include"EnemyBase/StoneStatue/StoneStatue.h"


EnemyFactory::EnemyFactory()
{
	///@各敵のステータス設定@///
	Slime_speed.x = 3.0f;
	HighSlime_speed.x = 7.0f;
	FakerLamiel_speed.x = 1.0f;
	Slime_hp       = 5;
	HighSlime_hp   = 7;
	FakerLamiel_hp = 30;
	StoneStatue_hp = 60;
	///@敵の種類のタグをプッシュバック@///
	///　　スライム         ///
	enemy_tag.push_back("S");
    /// 　ハイスライム     ///
    enemy_tag.push_back("H");
	///　フェイクラミエル  ///
    enemy_tag.push_back("L");
	/// 　巨大な古代兵器   ///
    enemy_tag.push_back("B");
	///@敵のモデル@///
     enemy_model[SLIME]       = L"Model\\Enemy\\Slime\\slime_blue.X";
	 enemy_model[HIGHSLIME]   = L"Model\\Enemy\\HighSlime\\slime_animatinonv02.X";
     enemy_model[FAKERLAMIEL] = L"Model\\Enemy\\Lamiel\\ramieru.X";
     enemy_model[STONESTATUE] = L"Model\\Enemy\\Stone\\koteihoudai.X";
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
	EnemyBase* classes[] = { new Slime, new HighSlime, new FakerLamiel,new StoneStatue};


	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { enemy = classes[i]; }
	}

	return enemy;
}

LPCWSTR EnemyFactory::SetModel(std::string tag)
{
	LPCWSTR models[] = { enemy_model[SLIME] , enemy_model[HIGHSLIME],enemy_model[FAKERLAMIEL],enemy_model[STONESTATUE]};
	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { model_name = models[i]; }
	}
	return model_name;
}

DirectX::SimpleMath::Vector3 EnemyFactory::SetSpeed(std::string tag)
{
	DirectX::SimpleMath::Vector3 speeds[] = { Slime_speed,HighSlime_speed,FakerLamiel_speed };
	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { speed = speeds[i]; }
	}
	return speed;
}

int EnemyFactory::SetHP(std::string tag)
{
	int hps[] = { Slime_hp,HighSlime_hp,FakerLamiel_hp,StoneStatue_hp};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { hp = hps[i]; }
	}
	return hp;
}