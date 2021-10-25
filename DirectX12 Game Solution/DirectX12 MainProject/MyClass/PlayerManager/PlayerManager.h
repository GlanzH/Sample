#pragma once

#include <Windows.h>
using namespace DirectX;

class PlayerManager
{
public:

	void LoadAssets();
	void Initialize();
	void Update(const float deltaTime);
	void Render();
	//DX9::MODEL GetCollision() { return collision };

private:
	//ÉvÉåÉCÉÑÅ[
	DX9::SKINNEDMODEL model;

	DX9::MODEL collision;
};
