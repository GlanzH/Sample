#pragma once

#include "MyClass/GroundManager/GroundManager.h"
#include"MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase() {};

	virtual bool Initialize(std::string tag,SimpleMath::Vector3 speed,int hp);
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	virtual int Update(SimpleMath::Vector3 player, const float deltaTime);
	void Render();

	void Retreat();
	virtual void Damage(const float deltaTime,int damage);

	DX9::SKINNEDMODEL& GetAnimModel() { return anim_model; }
	DX9::MODEL& GetModel()			  { return model; }
	BoundingBox GetAnimBox()		  { return anim_box; }
	BoundingBox GetBox()			  { return box; }

	std::string GetTag() { return enemy_tag; }

private:
	D3DMATERIAL9  material;
	GroundManager ground;
	
protected:
	DX9::SKINNEDMODEL anim_model;
	DX9::MODEL model;
	BoundingBox  anim_box;
	BoundingBox  box;
	DX9::MODEL	 anim_collision;
	DX9::MODEL	 collision;
	SimpleMath::Vector3  position;
	SimpleMath::Vector3  enemy_speed;

	std::string enemy_tag;
	int count = 0;
	int enemy_hp;
	bool retreat_flg;

	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack);
	enum ENEMYMOSION
	{
		WAIT,
		DAMAGE,
		MAX_MOTION
	};
};