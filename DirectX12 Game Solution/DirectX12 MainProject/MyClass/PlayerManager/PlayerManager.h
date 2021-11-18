#pragma once

using namespace DirectX;

#include "Base/DX12Effekseer.h"

#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/PlayerManager/Sword/Sword.h"


class PlayerManager
{
public:

	PlayerManager() {};
	~PlayerManager() {};

	bool Initialize();
	void LoadAssets();
	int Update(DX9::MODEL& ground, const float deltaTime);
	void Render();
	void _2DRender();

	void OnCollisionEnter();
	void OnParryArea();

	bool GetParryFlag() { return parry_flag; }

	bool IsAttack();


	DX9::SKINNEDMODEL& GetModel() { return model; }
	BoundingBox  GetBox()  { return  box; }

	BoundingBox GetSwordBox() { return sword_box; }

	int GetDamage() { return damage; }


private:
	//プレイヤー
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scsle = 500.0f;
	float model_rotetion = -90.0f;

	//プレイヤーの移動制限(幅)
	const float model_collision_detection_X     = 495.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN =   -5.0f;
	const float model_collision_detection_Z     =  100.0f;


	BoundingBox box;
	D3DMATERIAL9 material;

	const int box_size = 4;
	

	//プレイヤーのスピード
	const float player_speed_ = 40.0f;

	DX9::MODEL collision;

	//アニメーション
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);



	enum
	{
		Wait,
		Run,
		Jump,
		Damage,
		Attack_S,
		Attack_L,
		Parry_,
		Appeil,
		MOTION_MAX
	};



	//ジャンプしてるかのフラグ。
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//重力加速度
	const float gravity_ = 120.0f;
	//初速
	const float V0 = 50.0f;

	//パリィ
	const int max_parry_count = 40;
	int		  parry_count = 0;
	bool	  parry_flag = false;


	//プレイヤーの攻撃範囲
	BoundingBox sword_box;
	DX9::MODEL  sword_collision;

	//攻撃の向き
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//攻撃‐3連撃‐カウント
	int attack_count;

	//攻撃のカウント(秒)
	float attack_count_time;

	//攻撃の時間
	bool  attack_flag = false;

	float attack_zeit = 0.0f;
	float attack_zeit_max = 0.03309f;


	//攻撃のクールタイム
	//bool cool_time_flag   = false;
	//float cool_time       = 0.0f;
	//float cool_time_max = 0.2f;

	bool cool_time_flag_zwei = false;
	float cool_time_zwei = 0.0f;
	float cool_time_max_zwei[3]{ 0.1f,0.4f,0.6f };
	int count = 0;

	bool  count_flag = false;
	float count_time = 0.0f;
	float count_time_max = 0.4f;

	
	int damage = 0;

	//攻撃エフェクト
	//1
	EFFECT Sword_Effect_1;
	EFFECTHANDLE handle_1;

	//2
	EFFECT Sword_Effect_2;
	EFFECTHANDLE handle_2;

	//3
	EFFECT Sword_Effect_3;
	EFFECTHANDLE handle_3;


	//無敵時間
	bool  invincible_flag = false;
	float invincible_time      = 0.0f;
	float invincible_time_max = 100.0f;//1.5f;

	//アピール
	enum Appeal_state
	{
		NORMAL,
		APPEAL
	};

	Appeal_state appeal_state_mode;

	float appeal_time     = 0.0f;
	float appeal_time_max = 5.0f;
	


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
	void Player_attack(const float deltaTime);
	//攻撃エフェクト関係
	void Player_Attack_Effect(const float deltaTime);
	//パリィ
	void Parry();
	//無敵時間
	void Invincible(const float deltaTime);
	//アピール
	void Appeal(const float deltaTime);


};