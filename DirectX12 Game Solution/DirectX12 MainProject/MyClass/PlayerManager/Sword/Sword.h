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

	BoundingBox GetBox() { return box; }
	bool IsAttack();

private:

	DX9::MODEL sword_model_;
	SimpleMath::Vector3 sword_pos;

	BoundingBox box;
	DX9::MODEL collision;

	float rotate = 0.0f;

	bool  sword_flag;
	float sword_attack_time = 0.0f;

	const float fixed_pos = 50.0f;

	//�N�[���^�C��
	bool  cool_time_flag;
	float cool_time      = 0.0f;
	float cool_time_max  = 5.0f;

};