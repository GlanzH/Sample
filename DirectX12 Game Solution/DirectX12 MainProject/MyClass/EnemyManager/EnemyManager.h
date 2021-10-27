#pragma once

using namespace DirectX;
#include "../PlayerManager/PlayerManager.h"

typedef SimpleMath::Vector3 Vector3;

class EnemyManager
{
public:
	EnemyManager() {};
	~EnemyManager() {};

	bool Initialize();
	void LoadAsset();
	int  Update(DX9::MODEL& ground, const float deltaTime);
	void Render();
	DX9::MODEL& GetCollision() { return collision; }

private:
	void Move(DX9::MODEL& ground, const float deltaTime);

	DX9::SKINNEDMODEL model;
	DX9::MODEL		  collision;
	
	BoundingBox  box;
	D3DMATERIAL9 material;

	PlayerManager player;

	const Vector3 init_pos = Vector3(50.0f, 0.0f, 50.0f);
};
