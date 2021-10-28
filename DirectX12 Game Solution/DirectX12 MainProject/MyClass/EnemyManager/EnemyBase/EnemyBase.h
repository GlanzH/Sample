#pragma once
#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/GroundManager/GroundManager.h"

using namespace DirectX;

typedef SimpleMath::Vector3 Vector3;

class EnemyBase
{
public:
	EnemyBase()  {}
	~EnemyBase() {}

	bool Initialize();
	void LoadAsset();
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
	Vector3      position;
	
	int hp = 1;
};