#include "EnemyFactory.h"
#include "MyClass/EnemyManager/EnemyFactory/EnemyBase/Slime/Slime.h"
#include"EnemyBase/HighSlime/HighSlime.h"
#include"EnemyBase/FakerLamiel/FakerLamiel.h"
#include"EnemyBase/StoneStatue/StoneStatue.h"


EnemyFactory::EnemyFactory()
{
	///@�e�G�̃X�e�[�^�X�ݒ�@///
	Slime_speed.x = 3.0f;
	HighSlime_speed.x = 7.0f;
	FakerLamiel_speed.x = 1.0f;
	Slime_hp       = 5;
	HighSlime_hp   = 7;
	FakerLamiel_hp = 30;
	StoneStatue_hp = 60;
	///@�G�̎�ނ̃^�O���v�b�V���o�b�N@///
	///�@�@�X���C��         ///
	enemy_tag.push_back("S");
    /// �@�n�C�X���C��     ///
    enemy_tag.push_back("H");
	///�@�t�F�C�N���~�G��  ///
    enemy_tag.push_back("L");
	/// �@����ȌÑ㕺��   ///
    enemy_tag.push_back("B");
	///@�G�̃��f��@///
  // enemy_model[SLIME]       = L"Model\\Enemy\\Slime\\slime.X";
   enemy_model[HIGHSLIME]   = L"Model\\Enemy\\HighSlime\\haisuraimu.X";
  // enemy_model[FAKERLAMIEL] = L"Model\\Enemy\\slime.X";
  // enemy_model[STONESTATUE] = L"Model\\Enemy\\slime.X";
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
	EnemyBase* classes[] = { new Slime, new HighSlime};


	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { enemy = classes[i]; }
	}

	return enemy;
}

LPCWSTR EnemyFactory::SetModel(std::string tag)
{
	LPCWSTR models[] = { enemy_model[SLIME] ,{ enemy_model[HIGHSLIME]}};
	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { model_name = models[i]; }
	}
	return model_name;
}

DirectX::SimpleMath::Vector3 EnemyFactory::SetSpeed(std::string tag)
{
	DirectX::SimpleMath::Vector3 speeds[] = { Slime_speed,HighSlime_speed };
	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { speed = speeds[i]; }
	}
	return speed;
}

int EnemyFactory::SetHP(std::string tag)
{
	int hps[] = { Slime_hp,HighSlime_hp};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { hp = hps[i]; }
	}
	return hp;
}