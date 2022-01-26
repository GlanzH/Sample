#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerAttack/PlayerAttack.h"

using namespace DirectX;

typedef struct Collisions {
	BoundingBox  sword_box;
	BoundingBox  box;

	BoundingBox right_box;
	BoundingBox left_box;

};

class PlayerBase
{
public:

	PlayerBase();
	~PlayerBase() {};

	bool Initialize();
	void LoadAssets();
	int Update(const float deltaTime, bool temp);
	void Render();

	void OnCollisionEnter(std::string tag);
	void OnWeaponCollisionEnter(std::string tag);

	//敵に当たった時の関数
	void OnLeftCollisionEnter(std::string tag); //左
	void OnRightCollisionEnter(std::string tag);//右

	void OnParryArea();

	bool IsAttack();

	void Debug();
	void OnDeviceLost();

	//攻撃 弾かれる
	void Frip();


	//アニメーション
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);


	DX9::SKINNEDMODEL& GetModel() { return model; }



	Collisions GetBox() { return col; }

	//左右の当たり判定(ノックバック用)
	Collisions GetRightBox() { return right_col; }
	Collisions GetLeftBox() { return left_col; }


	int GetDamage() { return damage; }

	int GetAttackCount() { }

	float GetAppielTime() { return appeil_time; }//アピールしている時間

	bool IsDeathbrow() { return deathbrow_flag; }//必殺技発動フラグ

	bool GetAppealCoolFlag() { return appeil_cool_flag; }


	bool IsInvincibleFlag() { return invincible_flag; }//無敵フラグ

	bool IsAvoidance() { return avoidance_flag; }//回避フラグ

	int GetAttackTag() { return attack_type; }//1 = 上段攻撃 - Y, 2 = 下段攻撃 - X

	bool GetEnemyDeathFlag() { return elimination_flag; }//エネミーの消滅

	void GetFripFlag() { frip_flag = true; }


private:

	//移動
	void Player_move(const float deltaTime);
	//移動制限
	void Player_limit();
	//ジャンプ
	void Player_jump(const float deltaTime);
	//無敵時間
	void Invincible(const float deltaTime);
	//ノックバック
	void Knock_Back();

	//攻撃
	void Attack_Relation(const float deltaTime);
	//降り下ろし
	void Swing_Down(const float deltaTime);
	//切り上げ
	void Reverse_Slash(const float deltaTime);


	//回避
	void Avoidance(const float deltaTime);


	DX9::SPRITEFONT font;

	D3DMATERIAL9 material;

	//剣の当たり判定ボックス
	BoundingBox sword_box;
	BoundingBox box;


	BoundingBox right_box;
	BoundingBox left_box;

	//当たり判定用モデル
	DX9::MODEL sword_collision;
	DX9::MODEL collision;
	Collisions col;

	DX9::MODEL right_collision;
	Collisions right_col;
	DX9::MODEL left_collision;
	Collisions left_col;
	

	int damage = 0;
	int reduce_num = 0;

	const int body_reduce_num = -20;
	const int weapon_reduce_num = -40;

	const int mb_reduce_num = -30;
	const int mb_weapon_reduce_num = -60;

	//プレイヤー
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scale = 1.0f;
	float model_rotetion = -90.0f;

	//プレイヤーの移動制限(幅)
	const float model_collision_detection_X = 67.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN = 0.1f;
	const float model_collision_detection_Z = 100.0f;

	//当たり判定モデルの大きさ
	const int player_box_size_y = 5;
	const int player_box_size_x = 5;
	const int player_box_size_z = 3;

	const int box_size_x = 3.5;
	const int box_size_y = 2;
	const int box_size_z = 4;

	const int sidebox_size_x = 2;
	const int sidebox_size_y = 9;
	const int sidebox_size_z = 1;


	//プレイヤーのスピード
	const float player_speed_ = 40.0f;

	//ジャンプしてるかのフラグ
	bool jump_flag_;
	float jump_time_;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//重力加速度
	const float gravity_ = 170.0f;
	//初速
	const float V0 = 70.5f;

	//ジャンプタイミング
	bool  jump_start_flag;
	float jump_start_time;
	float jump_start_time_max;

	bool jump_end_flag;



	//攻撃の時間
	bool  attack_flag;
	float attack_time;
	float attack_zeit_max;


	//攻撃中　ジャンプ不可
	enum UNDER_ATTACK_STATE
	{
		NOMAL,
		ATTACK
	};

	UNDER_ATTACK_STATE under_attack_state_mode;

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
		FINISH,
		REBOUND,
		JUMP,
		ROLL,
		DAMAGE1,
		MOTION_MAX
	};

	//攻撃の向き
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//『使用しない』****************************//
		//アピール
	bool appeil_flag;
	float appeil_time;
	bool appeil_cool_flag;
	//必殺技
	bool deathbrow_flag;//必殺技発動フラグ
//*****************************************//

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


	//回避
	bool  avoidance_flag;
	float avoidance_start;
	float avoidance_max;
	float avoidance_move;


	//攻撃の種類 1:弱攻撃　2:突き攻撃
	int attack_type;

	//ノックバック
	void Knock_back_Move();

	bool knock_back_flag;
	float knock_back_start;
	float knock_back_end;
	float time_other;

	//起き上がる
	void Rize();

	float rize_end;

	enum Damage_Mode
	{
		NOMAL_STATE, //通常状態
		KNOCK_BACK   //ノックバック
	};
	Damage_Mode damage_mode_state;



	//上段(変数宣言)
	enum Upper_State
	{
		NOT_UPPER,
		UPPER_ATTACK
	};
	Upper_State upper_state_mode;
	float upper_start;
	float upper_end;

	//下段(変数宣言)
	enum Lower_State
	{
		NOT_LOWER,
		LOWER_ATTACK
	};
	Lower_State lower_state_mode;
	float lower_start;
	float lower_end;



	//納刀
	void Sword_Delivery(const float deltaTime, bool temp);
	bool  s_del_flag;
	float s_del_start;
	float s_del_end;

	//敵の消滅
	bool elimination_flag;
	float elimination_end;

	//弾く
	enum Frip_State
	{
		NOT_FRIP,
		FRIP
	};

	Frip_State frip_state_mode;

	bool frip_flag;

	void Frip_Knock_Back();
	float frip_start = 0.0f;
	float frip_end = 0.783f;

	int effect_count = 0;
};