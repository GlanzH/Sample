#pragma once

#include "Base/DX12Effekseer.h"
#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/PlayerManager/Sword/Sword.h"

using namespace DirectX;

class PlayerManager
{
public:

	PlayerManager() {};
	~PlayerManager() {};

	bool Initialize();
	void LoadAssets();
	int Update(DX9::MODEL& ground,  const float deltaTime);
	void Render();
	void _2DRender();

	void OnCollisionEnter();
	void OnParryArea();

	bool GetParryFlag() { return parry_flag; }

	DX9::SKINNEDMODEL& GetModel() { return model; }
	BoundingBox  GetBox()  { return  box; }

private:
	//プレイヤー
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scsle = 0.05f;
	float model_rotetion = -90.0f;

	//プレイヤーの移動制限(幅)
	const float model_collision_detection_X     = 495.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN =   -5.0f;
	const float model_collision_detection_Z     =  100.0f;


	BoundingBox box;
	D3DMATERIAL9 material;

	const int box_size = 2;
	
	const int max_parry_count = 40;
	int		  parry_count = 0;
	bool	  parry_flag = false;

	//プレイヤーのスピード
	const float player_speed_ = 50.0f;

	DX9::MODEL collision;

	//アニメーション
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);

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

	//エフェクト
	EFFECT Sword_Effect_;
	EFFECTHANDLE handle;





	//ジャンプしてるかのフラグ。
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//重力加速度
	const float gravity_ = 100.0f;
	//初速
	const float V0 = 28.0f;


	DX9::SPRITEFONT font;

	//地面との当たり判定
	void Player_collision_detection(DX9::MODEL& ground);
	float collision_detection = 100.0f;
	//移動
	void Player_move(const float deltaTime);
	//移動制限
	void Player_limit();
	//ジャンプ
	void Player_jump(DX9::MODEL& ground, const float deltaTime);
	//攻撃
	void Player_attack();
	//パリィ
	void Parry();
};