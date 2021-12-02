#pragma once

#include"MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "Base/DX12Effekseer.h"

using namespace DirectX;

typedef struct Collision {
	//敵モデルの当たり判定
	BoundingBox  box;
	//炎の当たり判定
	BoundingBox  fire;
	//弾の当たり判定
	BoundingSphere bullet;
};

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase() {};

	virtual bool Initialize(std::string tag,SimpleMath::Vector3 speed,int hp);
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	virtual int Update(SimpleMath::Vector3 player, const float deltaTime);
	virtual void Render();

	void BulletParry();
	void Retreat();
	
	virtual void Damage(int damage);
	bool LifeDeathDecision();

	DX9::SKINNEDMODEL& GetAnimModel() { return anim_model; }
	DX9::MODEL& GetModel()			  { return model; }
	BoundingBox GetAnimBox()		  { return anim_box; }
	Collision GetBox()				  { return col; }

	std::string GetTag() { return enemy_tag; }

private:
	void EnemyAnimation();
	
	float box_size;
	float parry_count = 0;

	bool damage_flag = false;

	//!ダメージモーション再生用変数
	int is_damage = 0;
	const int max_is_damage = 5;

	//!ダメージ受けたときに止まる用
	float damage_frame = 0.0f;
	const float max_damage_frame = 1.0f;
	
protected:
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack);
	bool IsDamage();
	D3DMATERIAL9  material;
	DX9::SKINNEDMODEL anim_model;
	BoundingBox		  anim_box;
	DX9::MODEL		  anim_collision;

	DX9::MODEL   model;
	DX9::MODEL	 collision;
	DX9::MODEL	 obstacle_collision;

	SimpleMath::Vector3  position;
	SimpleMath::Vector3  enemy_speed;

	std::string enemy_tag;

	const float fit_collision_y = 4.0f;
	int enemy_hp;
	float delta;

	bool retreat_flg;
	bool bullet_parry_flag = false;

	Collision col;

	enum ENEMYMOSION
	{
		WAIT,
		DAMAGE,
		MAX_MOTION
	};
};