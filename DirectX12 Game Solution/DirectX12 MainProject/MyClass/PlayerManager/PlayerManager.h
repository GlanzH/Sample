#pragma once

using namespace DirectX;

#include "Base/DX12Effekseer.h"
#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/PlayerManager/Sword/Sword.h"
#include "MyClass/EnemyManager/EnemyManager.h"

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

	void OnCollisionEnter(PlayerManager* player);
	void Retreat();


	DX9::MODEL& GetModel() { return model; }
	BoundingBox  GetBox()		  { return  box; }

private:
	//プレイヤー
	DX9::MODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scsle = 12.0f;
	float model_rotetion = -90.0f;

	//プレイヤーの移動制限(幅)
	float model_collision_detection_X     = 495.0f;
	float model_collision_detection_Y_MAX = 1000.0f;
	float model_collision_detection_Y_MIN =   -5.0f;
	float model_collision_detection_Z     =  100.0f;


	BoundingBox box;
	D3DMATERIAL9 material;

	int box_size = 2;

	//プレイヤーのスピード
	float player_speed_ = 50.0f;

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

	//エフェクト
	EFFECT Sword_Effect_;
	EFFECTHANDLE handle;

	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);




	//ジャンプしてるかのフラグ。
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//1/2
	float half = 0.5f;
	//重力加速度
	float gravity_ = 100.0f;
	//初速
	float V0 = 28.0f;


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

};