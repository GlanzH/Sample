#pragma once

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
};
