#pragma once


#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerManager;

class Sword
{
public:

	Sword() {}
	~Sword() {};

	bool Initialize();
	void LoadAssets();
	int Update(PlayerManager* player, const float deltaTime);
	void Render();

	DX9::MODEL& GetModel() { return sword_model_; }


private:

	DX9::MODEL sword_model_;
	SimpleMath::Vector3 sword_pos;
	bool  sword_flag;
	float sword_attack_time = 0.0f;

	const float fixed_pos = 50.0f;

};