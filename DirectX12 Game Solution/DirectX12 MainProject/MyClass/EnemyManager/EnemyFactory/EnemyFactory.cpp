#include "EnemyFactory.h"
#include "EnemyBase/SwordMan/SwordMan.h"
#include "EnemyBase/Shielder/Shielder.h"
#include "EnemyBase/MidBoss/MidBoss.h"
#include "EnemyBase/Arrow/Arrow.h"
#include "EnemyBase/Slime/Slime.h"

EnemyFactory::EnemyFactory()
{
	//敵のステータス設定
	enemy_hp    = ENEMY_HP;
	mid_boss_hp = MID_BOSS_HP;
	arrow_hp    = INT_MAX;

	//敵の種類のタグ
	//兵士(剣)
	enemy_tag.push_back("SW");
    //兵士(盾)
    enemy_tag.push_back("SH");
	//中ボス
    enemy_tag.push_back("MB");
	//スライム
	enemy_tag.push_back("SL");
	//矢
	enemy_tag.push_back("AR");

	///@敵のモデル@///
     enemy_model[SWORD_MAN] = L"Model\\Enemy\\SwordMan\\armor_red_0124.X";
	 enemy_model[SHIELDER]  = L"Model\\Enemy\\Shielder\\armor_blue_0125.X";
	 enemy_model[MID_BOSS]  = L"Model\\Enemy\\MidBoss\\midolboss_goblin.X";
	 enemy_model[ARROW]     = L"Model\\Enemy\\Arrow\\arrow_big.X";
	 enemy_model[SLIME] = L"Model\\Enemy\\Slime\\slime_blue_motion_.X";

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
		new MidBoss,
		new Arrow,
		new Slime
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
		enemy_model[MID_BOSS],
		enemy_model[ARROW],
		enemy_model[SLIME]
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
		mid_boss_hp,
		arrow_hp,
		enemy_hp
	};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { hp = hps[i]; }
	}
	return hp;
}