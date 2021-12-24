#include "EnemyFactory.h"
#include "MyClass/EnemyManager/EnemyFactory/EnemyBase/Slime/Slime.h"
#include "EnemyBase/HighSlime/HighSlime.h"
#include "EnemyBase/FakerLamiel/FakerLamiel.h"
#include "EnemyBase/StoneStatue/StoneStatue.h"
#include "EnemyBase/StoneStatue/Core/Core.h"
#include "EnemyBase/FootHold/FootHoldBase/FootHoldBase.h"



EnemyFactory::EnemyFactory()
{
	//�G�̃X�e�[�^�X�ݒ�
	slime_hp			 = SLIME_HP;
	high_slime_hp		 = HIGH_SLIME_HP;
	faker_lamiel_hp		 = LAMIEL_HP;
	stone_statue_hp		 = INT_MAX;
	stone_statue_core_hp = STONE_CORE_HP;
	foot_hold_hp         = INT_MAX;

	//�G�̎�ނ̃^�O
	//�X���C��
	enemy_tag.push_back("S");
    //�n�C�X���C��
    enemy_tag.push_back("H");
	//�t�F�C�N���~�G��
    enemy_tag.push_back("L");
	//����ȌÑ㕺��
    enemy_tag.push_back("B");
	//�Ñ㕺��̃R�A
	enemy_tag.push_back("C");
	//����
	enemy_tag.push_back("F");

	///@�G�̃��f��@///
     enemy_model[SLIME]        = L"Model\\Enemy\\Slime\\slime_blue_motion.X";
	 enemy_model[HIGH_SLIME]   = L"Model\\Enemy\\HighSlime\\slime_orange_animation.X";
     enemy_model[FAKER_LAMIEL] = L"Model\\Enemy\\Lamiel\\ramieru.X";
     enemy_model[STONE_STATUE] = L"Model\\Enemy\\Stone\\houdai.X";
	 enemy_model[STONE_CORE]   = L"Model\\Enemy\\Stone\\koteihoudai_core.X";
	 enemy_model[FOOT_HOLD]    = L"Model\\asiba.X";

}

EnemyBase* EnemyFactory::Create(std::string tag, bool time_stop_flag,DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* enemy_factory = CreateProduct(tag,time_stop_flag,position);
	enemy_factory->Initialize(tag,time_stop_flag, SetHP(tag));
	enemy_factory->LoadAsset(SetModel(tag), position);
	
	return enemy_factory;
}

EnemyBase* EnemyFactory::CreateProduct(std::string tag, bool time_stop_flag, DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* classes[] = 
	{ 
		new Slime,
		new HighSlime,
		new FakerLamiel,
		new StoneStatue,
		new Core,
		new FootHoldBase
	};


	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { enemy = classes[i]; }
	}

	return enemy;
}

LPCWSTR EnemyFactory::SetModel(std::string tag)
{
	LPCWSTR models[] = 
	{ 
		enemy_model[SLIME] ,
		enemy_model[HIGH_SLIME],
		enemy_model[FAKER_LAMIEL],
		enemy_model[STONE_STATUE],
		enemy_model[STONE_CORE],
		enemy_model[FOOT_HOLD]
	};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { model_name = models[i]; }
	}
	return model_name;
}

int EnemyFactory::SetHP(std::string tag)
{
	int hps[] = 
	{ 
		slime_hp,
		high_slime_hp,
		faker_lamiel_hp,
		stone_statue_hp,
		stone_statue_core_hp,
		foot_hold_hp
	};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { hp = hps[i]; }
	}
	return hp;
}