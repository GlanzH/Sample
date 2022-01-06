#include "EnemyFactory.h"
#include "EnemyBase/SwordMan/SwordMan.h"
#include "EnemyBase/Shielder/Shielder.h"
#include "EnemyBase/MidBoss/MidBoss.h"
#include "EnemyBase/Arrow/Arrow.h"


EnemyFactory::EnemyFactory()
{
	//“G‚ÌƒXƒe[ƒ^ƒXÝ’è
	enemy_hp    = ENEMY_HP;
	mid_boss_hp = MID_BOSS_HP;
	arrow_hp    = INT_MAX;

	//“G‚ÌŽí—Þ‚Ìƒ^ƒO
	//•ºŽm(Œ•)
	enemy_tag.push_back("SW");
    //•ºŽm(‚)
    enemy_tag.push_back("SH");
	//’†ƒ{ƒX
    enemy_tag.push_back("MB");
	//–î
	enemy_tag.push_back("AR");

	///@“G‚Ìƒ‚ƒfƒ‹@///
     enemy_model[SWORD_MAN] = L"Model\\Enemy\\SwordMan\\models_sord.X";
	 enemy_model[SHIELDER]  = L"Model\\Enemy\\Shielder\\goblin_shield.X";
	 enemy_model[MID_BOSS]  = L"Model\\Enemy\\MidBoss\\midolboss_goblin.X";
	 enemy_model[ARROW]     = L"Model\\Enemy\\Arrow\\arrow_big.X";

}

EnemyBase* EnemyFactory::Create(std::string tag, bool time_stop_flag,DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* enemy_factory = CreateProduct(tag,time_stop_flag,position);
	enemy_factory->Initialize(tag,time_stop_flag, SetHP(tag));

	if(tag != "AR")
		enemy_factory->LoadAsset(SetModel(tag), position);
	else
		enemy_factory->LoadModel(SetModel(tag), position);
	
	return enemy_factory;
}

EnemyBase* EnemyFactory::CreateProduct(std::string tag, bool time_stop_flag, DirectX::SimpleMath::Vector3 position)
{
	EnemyBase* classes[] = 
	{ 
		new SwordMan,
		new Shielder,
		new MidBoss,
		new Arrow
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
		enemy_model[SWORD_MAN],
		enemy_model[SHIELDER],
		enemy_model[MID_BOSS],
		enemy_model[ARROW]
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
		enemy_hp,
		enemy_hp,
		mid_boss_hp,
		arrow_hp
	};

	for (int i = 0; i < enemy_tag.size(); ++i)
	{
		if (tag == enemy_tag[i]) { hp = hps[i]; }
	}
	return hp;
}