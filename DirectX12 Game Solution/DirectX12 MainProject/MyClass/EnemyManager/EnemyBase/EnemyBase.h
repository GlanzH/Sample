#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"


#include "MyClass/GroundManager/GroundManager.h"

using namespace DirectX;


class EnemyBase
{
public:
	EnemyBase() {};
	~EnemyBase() {};

	bool Initialize(SimpleMath::Vector3 Speed,int hp);
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	virtual int Update(const float deltaTime);
	void Render();

	void Damage();

	BoundingBox GetBox() { return box; }

private:
	DX9::SKINNEDMODEL model;
	D3DMATERIAL9      material;

	GroundManager ground;
protected:
	BoundingBox  box;
	DX9::MODEL	 collision;
	SimpleMath::Vector3  position;
	
	int hp = 1;
};