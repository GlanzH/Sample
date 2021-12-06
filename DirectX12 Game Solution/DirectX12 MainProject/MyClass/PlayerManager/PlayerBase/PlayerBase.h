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
	BoundingBox GetParryBox() { return parry_box; }

	void OnCollisionEnter();
	void OnParryArea();

	bool GetParryFlag() { return parry_flag; }
	bool IsAttack();

	int GetDamage() { return damage; }

	int GetAttackCount() { return motion_count; }

	float GetAppielTime() { return appeil_time; }//アピールしている時間

	bool IsDeathbrow() { return deathbrow_flag; }//必殺技発動フラグ



	void _2DRender();

	

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
	//必殺技
	void Player_Special_Move(const float deltaTime);

	//プレイヤーの攻撃(ボタン変更ver)
	void Player_Attack_two(const float deltaTime);

	void Attack(const float deltaTime);

	//エフェクト1撃目
	void Attack_First(const float deltaTime);
	//エフェクト2撃目
	void Attack_Secnod(const float deltaTime);
	//エフェクト3撃目
	void Attack_Third(const float deltaTime);

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
	const float model_collision_detection_X = 67.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN = -5.0f;
	const float model_collision_detection_Z = 100.0f;

	//当たり判定モデルの大きさ
	const int player_box_size_y = 7;
	const int player_box_size_x = 5;
	const int player_box_size_z = 3;

	const int box_size_x = 30;
	const int box_size_y = 15;
	const int box_size_z = 3;


	//プレイヤーのスピード
	const float player_speed_ = 30.0f;

	//ジャンプしてるかのフラグ
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//重力加速度
	const float gravity_ = 120.0f;
	//初速
	const float V0 = 50.0f;

	//ジャンプタイミング
	bool  jump_start_flag     = false;
	float jump_start_time     = 0.0f;
	float jump_start_time_max = 0.133f;
	
	bool jump_end_flag = false;

	//パリィ
	const float  max_parry_count = 0.5f;
	float		 parry_count = 0.0f;
	bool	     parry_flag = false;

	BoundingBox parry_box;
	DX9::MODEL  parry_collision;

	float parry_box_size_x = 3.0f;
	float parry_box_size_y = 10.0f;
	float parry_box_size_z = 2.0f;


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
	float cool_time_max_zwei = 1.0f;
	int count = 0;

	bool  count_flag = false;
	float count_time = 0.0f;
	float count_time_max = 0.4f;

	//攻撃-初回
	bool first_attaack_flag = false;

	//攻撃-カウント-フラグ
	//モーション
	bool motion_time_start_flag = false;

	bool motion_attack_flag = false;

	float motion_time = 0.0f;
	float motion_time_max[3]{ 0.617f,0.517f,0.583f };
	int   motion_count = 0;

	//攻撃中　ジャンプ不可
	enum UNDER_ATTACK_STATE
	{
		NOMAL,
		ATTACK
	};

	UNDER_ATTACK_STATE under_attack_state_mode;

	//攻撃中　移動不可
	enum CANNOT_MOVE_STATE
	{
		MOVE,
		CANNOT_MOVE
	};

	CANNOT_MOVE_STATE canot_move_state_mode;

	//エフェクトの発生タイミング等
	bool  effect_generation = false;
	float effect_generation_time = 0.1f;
	float effect_generation_time_max[3]{ 1.0f,0.033f,0.005f };//フレーム(19f,2f,11f)

	bool effect_end_flag = false;


	bool  effect_first_flag = false;
	float effect_first_time = 0.4f;
	float effect_first_max_time = 0.4f;



	//無敵時間
	bool        invincible_flag     = false;
	float		invincible_time     = 0.0f;
	const float invincible_time_max = 1.5f;


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

	//変更*2

	int  motion_flag = 0;

	bool motion_flag_1 = false;
	bool motion_flag_2 = false;
	bool motion_flag_3 = false;

	bool motion_start_time_1 = false;
	bool motion_start_time_2 = false;
	bool motion_start_time_3 = false;


	float motion_time_1 = 0.0f;
	float motion_time_2 = 0.0f;
	float motion_time_3 = 0.0f;

	float motion_time_max_1 = 0.6f;
	float motion_time_max_2 = 0.26f;
	float motion_time_max_3 = 0.583f;

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
	bool appeil_flag = false;

	float appeil_time = 0.0f;
	float appeil_time_max = 5.0f;

	float appeil_cool_time = 0.0f;
	float appeil_cool_time_max = 1.0f;

	bool appeil_cool_flag = false;

	//必殺技
	bool deathbrow_flag = false;//必殺技発動フラグ

	bool deathbrow_attack = false;//必殺技の当たり判定

	float specialmove_time = 0.0f;
	float specialmove_time_max = 4.0f;


	//暗転
	DX9::SPRITE deathbrow_sprite;
	int Transparency = 0;
	int Blackout = 15;
	int Blackout_max = 255;
	bool Blackout_flag = false;

	//明転
	bool bright_flag   = false;
	int  Ming_Turn = 55;

	int Deathblow_count = 20;

};