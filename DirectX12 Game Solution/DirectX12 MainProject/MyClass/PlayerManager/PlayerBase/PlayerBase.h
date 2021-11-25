#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerAttack/PlayerAttack.h"

using namespace DirectX;

class PlayerBase
{
public:

	PlayerBase() {};
	~PlayerBase() {};

	bool Initialize();
	void LoadAssets();
	int Update(const float deltaTime);
	void Render();

	DX9::SKINNEDMODEL& GetModel() { return model; }

	BoundingBox GetSwordBox() { return sword_box; }
	BoundingBox GetBox() { return  box; }

	void OnCollisionEnter();
	void OnParryArea();

	bool GetParryFlag() { return parry_flag; }
	bool IsAttack();

	int GetDamage() { return damage; }




private:
	//アニメーション
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);

	//移動
	void Player_move(const float deltaTime);
	//移動制限
	void Player_limit();
	//ジャンプ
	void Player_jump(const float deltaTime);
	//攻撃
	void Player_attack(const float deltaTime);
	//パリィ
	void Parry(const float deltaTime);
	//無敵時間
	void Invincible(const float deltaTime);
	//アピール
	void Appeal(const float deltaTime);

	DX9::SPRITEFONT font;

	D3DMATERIAL9 material;

	//剣の当たり判定ボックス
	BoundingBox sword_box;
	BoundingBox box;


	//当たり判定用モデル
	DX9::MODEL sword_collision;
	DX9::MODEL collision;

	int damage = 0;

	//プレイヤー
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scale = 0.1f;
	float model_rotetion = -90.0f;

	//プレイヤーの移動制限(幅)
	const float model_collision_detection_X = 70.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN = -5.0f;
	const float model_collision_detection_Z = 100.0f;

	//当たり判定モデルの大きさ
	const int player_box_size = 2;
	const int box_size = 4;

	//プレイヤーのスピード
	const float player_speed_ = 40.0f;

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
	const float  max_parry_count = 0.5f;
	float		 parry_count = 0.0f;
	bool	     parry_flag = false;

	//攻撃‐3連撃‐カウント
	int attack_count;

	//攻撃のカウント(秒)
	float attack_count_time;

	//攻撃の時間
	bool  attack_flag = false;
	float attack_zeit = 0.0f;
	float attack_zeit_max = 0.03309f;

	//攻撃のクールタイム
	bool cool_time_flag_zwei = false;
	float cool_time_zwei = 0.0f;
	float cool_time_max_zwei[3]{ 0.2f,0.4f,0.3f };
	int count = 0;

	bool  count_flag = false;
	float count_time = 0.0f;
	float count_time_max = 0.4f;

	//攻撃 - 初回
	bool First_attack_flag = false;

	//受付時間
	float Reception_time = 0.0f;



	//無敵時間
	bool  invincible_flag = false;
	float		invincible_time = 0.0f;
	const float invincible_time_max = 100.0f;//1.5f;

	//アピールする時間
	float		appeal_time = 0.0f; //アピールする初期値
	const float appeal_time_max = 2.0f; //アピールする時間の最大値

	//ステータスアップの時間
	float		focus_time = 0.0f;//ステータスアップの時間:初期値
	const float focus_time_max = 10.0f;//ステータスアップの時間:最大値

	//モーションの名前
	enum
	{
		STAND,
		RUN,
		ACT1,
		ACT2,
		ACT3,
		APPEIL,
		JUMP,
		PARRY,
		MOTION_MAX
	};


	//入力受付時間までの時間 & エフェクト表示までの時間
	bool  input_wait_flag = false;
	float input_wait_time = 0.0f;
	float input_wait_time_max[3]{ 0.433f,0.05f,0.2f };//(3回目はエフェクト表示のみ)
	int   input_wait_count = 0;

	//入力受付時間
	bool  input_flag = false;
	float input_time = 0.0f;
	float input_time_max[2]{ 0.633f, 0.8f };
	int   input_count = 0;

	//エフェクト表示
	bool effect_flag = false;

	//アニメーションを出す時間
	bool  animation_flag = false;
	float animation_time = 0.0f;
	float animation_time_max[3]{ 0.967f,0.850f,0.583f };
	int   animation_count = 0;

	//攻撃の向き
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//アピール
	enum Appeal_state
	{
		NORMAL,
		APPEAL,
		FOCUS
	};

	Appeal_state appeal_state_mode;


};