#pragma once

using namespace DirectX;

class PlayerManager
{
public:

	PlayerManager() {};
	~PlayerManager() {};

	bool Initialize();
	void LoadAssets();
	int Update(DX9::MODEL& ground, BoundingBox& enemy, const float deltaTime);
	void Render();

	DX9::SKINNEDMODEL& GetModel() { return model; }
	BoundingBox  GetBox() { return  box; }
private:
	//プレイヤー
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);

	BoundingBox box;

	D3DMATERIAL9 material;

	//プレイヤーのスピード
	float player_speed_ = 30.0f;

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

	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);




	//ジャンプしてるかのフラグ。
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//重力加速度
	float gravity_ = 9.81f;
	//初速
	float V0 = 10.0f;

public:
	bool GetHitFlag() { return hit_flag; }
private:
	bool hit_flag = false;



};
