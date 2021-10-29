#include "EnemyFactory.h"
#include "MyClass/EnemyManager/EnemyBase/Enemy/Enemy.h"

EnemyFactory::EnemyFactory()
{
	//!動く敵のステータス設定
	NormalEnemy_speed.x = 0.1f;
	NormalEnemy_hp =1;

	//!敵の種類のタグをプッシュバック
	_enemytag.push_back("normal");
	enemy_model[NORMAL] = L"Mikoto\\mikoto.x";
}

EnemyBase* EnemyFactory::Create(std::string tag, DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* enemy_factory = CreateProduct(tag, position);
	enemy_factory->Initialize(SetSpead(tag), SetHP(tag));
	enemy_factory->LoadAsset(SetModel(tag), position);
	
	return enemy_factory;
}

EnemyBase* EnemyFactory::CreateProduct(std::string tag, DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* classes[] = { new Enemy};

	for (int i = 0; i < _enemytag.size(); ++i)
	{
		if (tag == _enemytag[i]) { enemy = classes[i]; }
	}

	return enemy;
}

LPCWSTR EnemyFactory::SetModel(std::string tag)
{
	LPCWSTR models[] = { enemy_model[NORMAL] };
	for (int i = 0; i < _enemytag.size(); ++i)
	{
		if (tag == _enemytag[i]) { Model_name = models[i]; }
	}
	return Model_name;
}

DirectX::SimpleMath::Vector3 EnemyFactory::SetSpead(std::string tag)
{
	DirectX::SimpleMath::Vector3 speeds[] = { NormalEnemy_speed };
	for (int i = 0; i < _enemytag.size(); ++i)
	{
		if (tag == _enemytag[i]) { Speed = speeds[i]; }
	}
	return Speed;
}

int EnemyFactory::SetHP(std::string tag)
{
	int hps[] = { NormalEnemy_hp};

	for (int i = 0; i < _enemytag.size(); ++i)
	{
		if (tag == _enemytag[i]) { HP = hps[i]; }
	}
	return HP;
}
