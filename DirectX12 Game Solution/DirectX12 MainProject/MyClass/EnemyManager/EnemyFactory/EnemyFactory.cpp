#include "EnemyFactory.h"
#include "EnemyBase/SwordMan/SwordMan.h"
#include "EnemyBase/Shielder/Shielder.h"
#include "EnemyBase/RandSwordMan/RandSwordMan.h"
#include "EnemyBase/Arrow/Arrow.h"

EnemyFactory::EnemyFactory()
{
	//�G�̃X�e�[�^�X�ݒ�
	enemy_hp = ENEMY_HP;
	rand_hp  = 2;
	arrow_hp = INT_MAX;

	//�G�̎�ނ̃^�O
	//���m(��)
	enemy_tag.push_back("SW");
    //���m(��)
    enemy_tag.push_back("SH");
	//�\�����ς�镺�m(��)
	enemy_tag.push_back("RS");
	//��
	enemy_tag.push_back("AR");

	///@�G�̃��f��@///
     enemy_model[SWORD_MAN]  = L"Model\\Enemy\\SwordMan\\armor_red2_0210.X";
	 enemy_model[SHIELDER]   = L"Model\\Enemy\\Shielder\\armor_blue_0125.X";
	 enemy_model[ARROW]      = L"Model\\Enemy\\Arrow\\arrow_big.X";

}

EnemyBase* EnemyFactory::Create(
	string tag,double init_wait,double stop_pos,
	 SimpleMath::Vector3 position,double speed,string direct,string posture
)
{
	EnemyBase* enemy_factory = CreateProduct(tag,position);
	enemy_factory->Initialize(tag,init_wait,stop_pos,speed,direct, posture, SetHP(tag));

	if(tag != "AR")
		enemy_factory->LoadAsset(SetModel(tag), position);
	else
		enemy_factory->LoadModel(SetModel(tag), position);
	
	return enemy_factory;
}

EnemyBase* EnemyFactory::CreateProduct(string tag, SimpleMath::Vector3 position)
{
	EnemyBase* classes[] = 
	{ 
		new SwordMan,
		new Shielder,
		new RandSwordMan,
		new Arrow
	};


	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { enemy = classes[i]; }
	}

	return enemy;
}

LPCWSTR EnemyFactory::SetModel(string tag)
{
	LPCWSTR models[] = 
	{ 
		enemy_model[SWORD_MAN],
		enemy_model[SHIELDER],
		enemy_model[SWORD_MAN],
		enemy_model[ARROW]
	};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { model_name = models[i]; }
	}
	return model_name;
}

int EnemyFactory::SetHP(string tag)
{
	int hps[] = 
	{ 
		enemy_hp,
		enemy_hp,
		rand_hp,
		arrow_hp
	};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { hp = hps[i]; }
	}
	return hp;
}