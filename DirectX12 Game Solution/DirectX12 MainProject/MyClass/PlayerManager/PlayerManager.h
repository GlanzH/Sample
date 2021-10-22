#pragma once

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	bool Initialize();
	int  Update();
	void Render();
	DX9::MODEL GetCollision() { return collision };

private:
	DX9::MODEL model;
	DX9::MODEL collision;
};
