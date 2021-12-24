#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerNot
{
public:
	PlayerNot();
	~PlayerNot();

	void Initialize();

	//攻撃
	void Player_attack(const float deltaTime);

	//プレイヤーの攻撃(ボタン変更ver)
	void Player_Attack_two(const float deltaTime);

	void Attack(const float deltaTime);

	//エフェクト1撃目
	void Attack_First(const float deltaTime);
	//エフェクト2撃目
	void Attack_Secnod(const float deltaTime);
	//エフェクト3撃目
	void Attack_Third(const float deltaTime);



private:
	//攻撃‐3連撃‐カウント
	int attack_count;

	//攻撃のカウント(秒)
	float attack_count_time;

	//攻撃の時間
	bool  attack_flag;
	float attack_zeit;
	float attack_zeit_max;

	//攻撃のクールタイム
	bool cool_time_flag_zwei;
	float cool_time_zwei;
	float cool_time_max_zwei;
	int count;

	bool  count_flag;
	float count_time;
	float count_time_max;

	//攻撃-初回
	bool first_attaack_flag;

	//攻撃-カウント-フラグ
	//モーション
	bool motion_time_start_flag;

	bool motion_attack_flag;

	float motion_time;
	float motion_time_max[3]{ 0.617f,0.517f,0.583f };
	int   motion_count;

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

	//攻撃中 他の攻撃不可
	enum CANNOT_OTHER_ATTACK
	{
		NOMAL_STATE,
		FIRST,
		SECOND,
		THIRD
	};

	CANNOT_OTHER_ATTACK cannot_other;

	//エフェクトの発生タイミング等
	bool  effect_generation;
	float effect_generation_time;
	float effect_generation_time_max[3]{ 1.0f,0.033f,0.005f };//フレーム(19f,2f,11f)

	bool effect_end_flag;


	bool  first_attack_hit;
	float first_attack_time;
	float first_attack_time_max;


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
		DAMAGE,
		MOTION_MAX
	};


	//アピール
	bool appeil_flag;

	float appeil_time;
	float appeil_time_max;

	float appeil_cool_time;
	float appeil_cool_time_max;

	bool appeil_cool_flag;

	//必殺技
	bool deathbrow_flag;//必殺技発動フラグ

	bool deathbrow_attack;//必殺技の当たり判定

	float specialmove_time;
	float specialmove_time_max;

	//エフェクトの発生タイミング等
	bool  effect_generation;
	float effect_generation_time;
	float effect_generation_time_max[3]{ 1.0f,0.033f,0.005f };//フレーム(19f,2f,11f)

	bool effect_end_flag;


	bool  first_attack_hit;
	float first_attack_time;
	float first_attack_time_max;

	//変更*2
//モーション系統
	int  motion_flag;

	bool motion_flag_1;
	bool motion_flag_2;
	bool motion_flag_3;

	bool motion_start_time_1;
	bool motion_start_time_2;
	bool motion_start_time_3;


	float motion_time_1;
	float motion_time_2;
	float motion_time_3;

	float motion_time_max_1;
	float motion_time_max_2;
	float motion_time_max_3;

	//入力受付時間までの時間 & エフェクト表示までの時間
	bool  input_wait_flag;
	float input_wait_time;
	float input_wait_time_max[3]{ 0.433f,0.05f,0.2f };//(3回目はエフェクト表示のみ)
	int   input_wait_count;

	//入力受付時間
	bool  input_flag;
	float input_time;
	float input_time_max[2]{ 0.633f, 0.8f };
	int   input_count;

	//エフェクト表示
	bool effect_flag;

	//アニメーションを出す時間
	bool  animation_flag;
	float animation_time;
	float animation_time_max[3]{ 0.967f,0.850f,0.583f };
	int   animation_count;

};