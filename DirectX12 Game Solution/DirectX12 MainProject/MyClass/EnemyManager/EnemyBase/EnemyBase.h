#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/GroundManager/GroundManager.h"

using namespace DirectX;


class EnemyBase
{
public:
	EnemyBase() {};
	~EnemyBase() {};

	bool Initialize(SimpleMath::Vector3 speed,int hp);
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	virtual int Update(DX9::MODEL& ground, const float deltaTime);
	void Render();

	void Damage();

	BoundingBox GetBox() { return box; }

	static EnemyBase& Instance() {
		static EnemyBase instance;
		return instance;
	}

private:
	D3DMATERIAL9      material;

	GroundManager ground;
protected:
	DX9::SKINNEDMODEL model;
	BoundingBox  box;
	DX9::MODEL	 collision;
	SimpleMath::Vector3  position;
	SimpleMath::Vector3  enemy_speed;
	
	int enemy_hp;
};