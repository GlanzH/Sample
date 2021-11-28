#pragma once

#include"MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

typedef struct Collision {
	//“Gƒ‚ƒfƒ‹‚Ì“–‚½‚è”»’è
	BoundingBox  box;
	//‰Š‚Ì“–‚½‚è”»’è
	BoundingBox  fire;
	//’e‚Ì“–‚½‚è”»’è
	BoundingBox  bullet;
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

	void Retreat();
	virtual void Damage(const float deltaTime,int damage);

	DX9::SKINNEDMODEL& GetAnimModel() { return anim_model; }
	DX9::MODEL& GetModel()			  { return model; }
	BoundingBox GetAnimBox()		  { return anim_box; }
	Collision GetBox()			  { return col; }

	std::string GetTag() { return enemy_tag; }

private:
	float box_size;
	float parry_count = 0;
	int   damage_count = 0;
	
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
	int count = 0;
	int enemy_hp;
	bool retreat_flg;

	Collision col;

	enum ENEMYMOSION
	{
		WAIT,
		DAMAGE,
		MAX_MOTION
	};
};