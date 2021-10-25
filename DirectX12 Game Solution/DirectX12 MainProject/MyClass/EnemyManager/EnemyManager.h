#pragma once

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	bool Initialize();
	int  Update();
	void Render();
	//DX9::MODEL Getcollision() { return collision; }

private:
	DX9::MODEL model;
	DX9::MODEL collision;
};
