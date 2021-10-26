#pragma once

#include <Windows.h>
using namespace DirectX;

class PlayerManager
{
public:

	PlayerManager() {};
	~PlayerManager() {};

	bool Initialize();
	void LoadAssets();
	int Update(const float deltaTime);
	void Render();

	DX9::SKINNEDMODEL& GetModel() { return model; }
	DX9::MODEL& GetCollision()	  { return collision; };

private:
	//プレイヤー
	DX9::SKINNEDMODEL model;

	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);


	DX9::MODEL collision;

	enum
	{
		Wait,
		Koke,
		Jump,
		Push,
		Run,
		Walk,
		MOTION_MAX
	};


	//ジャンプしてるかのフラグ。
	bool jump_flag = false;
	float time = 1.0f;
	float gravity = 9.81f;



};
