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

	bool Initialize(SimpleMath::Vector3 speed,int hp);
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	virtual int Update(PlayerBase* player, const float deltaTime);
	void Render();

	void Retreat();
	virtual void Damage(const float deltaTime,int damage);

	DX9::SKINNEDMODEL& GetModel() { return model; }
	//DX9::MODEL& GetModel() { return model; }
	BoundingBox GetBox()		  { return box; }

private:
	D3DMATERIAL9  material;
	GroundManager ground;
	
protected:
	DX9::SKINNEDMODEL model;
	DX9::MODEL model;
	BoundingBox  box;
	DX9::MODEL	 collision;
	SimpleMath::Vector3  position;
	SimpleMath::Vector3  enemy_speed;
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