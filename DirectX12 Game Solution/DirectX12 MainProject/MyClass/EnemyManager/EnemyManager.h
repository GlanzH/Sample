#pragma once
using namespace DX9;
using namespace DirectX;

class EnemyManager
{
public:
	EnemyManager() {};
	~EnemyManager() {};

	bool Initialize();
	void LoadAsset();
	int  Update();
	void Render();
	DX9::MODEL& GetCollision() { return collision; }

private:
	DX9::SKINNEDMODEL model;
	DX9::MODEL		  collision;
	SimpleMath::Vector3 enemy_pos = SimpleMath::Vector3(500.0f, 0.0f, 50.0f);
};
