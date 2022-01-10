#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerAttack/PlayerAttack.h"

using namespace DirectX;

typedef struct Collisions {
	BoundingBox  sword_box;
	BoundingBox  box;
};

class PlayerBase
{
public:

	PlayerBase();
	~PlayerBase() {};

	bool Initialize();
	void LoadAssets();
	int Update(const float deltaTime);
	void Render();

	void OnCollisionEnter();
	void OnParryArea();

	bool IsAttack();

	void Debug();
	void BrackImage();
	void OnDeviceLost();



	DX9::SKINNEDMODEL& GetModel() { return model; }

	Collisions GetBox() { return col; }

	bool GetParryFlag() { return parry_flag; }

	int GetDamage() { return damage; }

	int GetAttackCount() { }

	float GetAppielTime() { return appeil_time; }//アピールしている時間

	bool IsDeathbrow() { return deathbrow_flag; }//必殺技発動フラグ

	bool GetAppealCoolFlag() { return appeil_cool_flag; }

	bool GetSpecialAttackFlag() { return special_attack_flag; }

	bool IsInvincibleFlag() { return invincible_flag; }//無敵フラグ

	bool IsAvoidance() { return avoidance_flag; }//回避フラグ

	int GetAttackTag() { return attack_type; }//攻撃の種類



private:
	//アニメーション
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);

	//移動
	void Player_move(const float deltaTime);
	//移動制限
	void Player_limit();
	//ジャンプ
	void Player_jump(const float deltaTime);
	//パリィ
	void Parry(const float deltaTime);
	//無敵時間
	void Invincible(const float deltaTime);
	//アピール
	void Appeal(const float deltaTime);
	//必殺技
	void Player_Special_Move(const float deltaTime);
	//プレイヤーの攻撃(3回目変更)
	void Player_Attack_Three(const float deltaTime);
	//回避
	void Avoidance(const float deltaTime);


	DX9::SPRITEFONT font;

	D3DMATERIAL9 material;

	//剣の当たり判定ボックス
	BoundingBox sword_box;
	BoundingBox box;


	//当たり判定用モデル
	DX9::MODEL sword_collision;
	DX9::MODEL collision;
	Collisions col;

	int damage = 0;

	//プレイヤー
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scale = 0.1f;
	float model_rotetion = -90.0f;

	//プレイヤーの移動制限(幅)
	const float model_collision_detection_X = 67.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN = 0.1f;
	const float model_collision_detection_Z = 100.0f;

	//当たり判定モデルの大きさ
	const int player_box_size_y = 7;
	const int player_box_size_x = 5;
	const int player_box_size_z = 3;

	const int box_size_x = 30;
	const int box_size_y = 15;
	const int box_size_z = 3;


	//プレイヤーのスピード
	const float player_speed_ = 25.0f;

	//ジャンプしてるかのフラグ
	bool jump_flag_;
	float jump_time_;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//重力加速度
	const float gravity_ = 120.0f;
	//初速
	const float V0 = 50.0f;

	//ジャンプタイミング
	bool  jump_start_flag;
	float jump_start_time;
	float jump_start_time_max;

	bool jump_end_flag;

	//パリィ
	const float  max_parry_count = 0.5f;
	float		 parry_count;
	bool	     parry_flag;

	//必殺技
	bool special_attack_flag;


	//攻撃の時間
	bool  attack_flag;
	float attack_zeit;
	float attack_zeit_max;


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


	//無敵時間
	bool        invincible_flag;
	float		invincible_time;
	float       invincible_time_max;

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

	//攻撃の向き
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

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

	//暗転
	DX9::SPRITE deathbrow_sprite;
	int Transparency;
	int Blackout;
	int Blackout_max;
	bool Blackout_flag;

	//明転
	bool bright_flag;
	int  Ming_Turn;

	//SE 変数
	//攻撃-SE
	XAudio::SOUNDEFFECT  first_attack_se;
	XAudio::SOUNDEFFECT second_attack_se;
	XAudio::SOUNDEFFECT  third_attack_se;
	//ジャンプ
	XAudio::SOUNDEFFECT jump_se;
	//着地
	XAudio::SOUNDEFFECT landing_se;

	//ダメージ
	XAudio::SOUNDEFFECT damege_se;

	//アピール
	XAudio::SOUNDEFFECT appeal_se;


	//************************************//

	//プレイヤーの攻撃_　Three
	//ダッシュ攻撃
	bool  assault_attack_flag;
	float assault_attack_time;
	float assault_attack_time_max;
	//攻撃中チャージ不可
	bool not_chage;

	bool assault_flag;

	//回避
	bool  avoidance_flag;
	float avoidance_start;
	float avoidance_max;

	//弱攻撃
	bool n_attack_flag_ = false;
	float n_attack_start = 0.0f;
	float n_attack_end_ = 0.617f;

	//攻撃の種類 1:弱攻撃　2:突き攻撃
	int attack_type;


};