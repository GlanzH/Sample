#include "EnemyFactory.h"
#include "MyClass/EnemyManager/EnemyFactory/EnemyBase/Slime/Slime.h"
#include"EnemyBase/HighSlime/HighSlime.h"
#include"EnemyBase/FakerLamiel/FakerLamiel.h"
#include"EnemyBase/StoneStatue/StoneStatue.h"
#include"EnemyBase/StoneStatue/Core/Core.h"


EnemyFactory::EnemyFactory()
{
	//@�e�G�̃X�e�[�^�X�ݒ�@//
	slime_speed.x = 3.0f;
	high_slime_speed.x = 7.0f;
	faker_lamiel_speed.x = 1.0f;
	statue_speed.z =0.0f ;
	stone_core_speed.z = 0.0f;
	slime_hp       = 2;
	high_slime_hp   = 7;
	faker_lamiel_hp = 2;
	stone_statue_hp = 60;
	stone_statue_core_hp = 2;
	//@�G�̎�ނ̃^�O���v�b�V���o�b�N@//
	//@�@�@�X���C��         @//
	enemy_tag.push_back("S");
    //@�@�n�C�X���C��     @//
    enemy_tag.push_back("H");
	//@�@�t�F�C�N���~�G��  @//
    enemy_tag.push_back("L");
	//@�@����ȌÑ㕺��   @//
    enemy_tag.push_back("B");
	//@  ����ȌÑ㕺��̃R�A@//
	enemy_tag.push_back("C");

	///@�G�̃��f��@///
     enemy_model[SLIME]        = L"Model\\Enemy\\Slime\\slime_blue.X";
	 enemy_model[HIGH_SLIME]   = L"Model\\Enemy\\HighSlime\\high_slime.X";
     enemy_model[FAKER_LAMIEL] = L"Model\\Enemy\\Lamiel\\ramieru.X";
     enemy_model[STONE_STATUE] = L"Model\\Enemy\\Stone\\houdai.X";
	 enemy_model[STONE_CORE]   = L"Model\\Enemy\\Stone\\houdai_core.X";
}

EnemyFactory::~EnemyFactory()
{
			delete new Slime;
			delete new HighSlime;
			delete new FakerLamiel;
			delete new StoneStatue;
			delete new Core;
}





EnemyBase* EnemyFactory::Create(std::string tag, DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* enemy_factory = CreateProduct(tag, position);
	enemy_factory->Initialize(tag,SetSpeed(tag), SetHP(tag));
	enemy_factory->LoadAsset(SetModel(tag), position);
	
	return enemy_factory;
}

EnemyBase* EnemyFactory::CreateProduct(std::string tag, DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* classes[] = { new Slime, new HighSlime, new FakerLamiel,new StoneStatue,new Core};


	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { enemy = classes[i]; }
	}
	return enemy;
}

LPCWSTR EnemyFactory::SetModel(std::string tag)
{
	LPCWSTR models[] = { enemy_model[SLIME] , enemy_model[HIGH_SLIME],enemy_model[FAKER_LAMIEL],enemy_model[STONE_STATUE],enemy_model[STONE_CORE]};
	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { model_name = models[i]; }
	}
	return model_name;
}

DirectX::SimpleMath::Vector3 EnemyFactory::SetSpeed(std::string tag)
{
	DirectX::SimpleMath::Vector3 speeds[] = { slime_speed,high_slime_speed,faker_lamiel_speed ,statue_speed,stone_core_speed};
	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { speed = speeds[i]; }
	}
	return speed;
}

int EnemyFactory::SetHP(std::string tag)
{
	int hps[] = { slime_hp,high_slime_hp,faker_lamiel_hp,stone_statue_hp,stone_statue_core_hp};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { hp = hps[i]; }
	}
	return hp;
}