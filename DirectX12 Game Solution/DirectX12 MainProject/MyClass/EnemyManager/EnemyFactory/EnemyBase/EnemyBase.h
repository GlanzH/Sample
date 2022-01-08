#pragma once

#include"MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/AudianceManager/ExplodeMan/ExplodeMan.h"
#include "Base/DX12Effekseer.h"

using namespace DirectX;

typedef struct Collision {
	//敵モデルの当たり判定
	BoundingBox  box;
};

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase() {};

	virtual bool Initialize(std::string tag, bool time_stop_flag, int hp);
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	void LoadModel(LPCWSTR model_name, SimpleMath::Vector3 initial_position);

	virtual int  Update(SimpleMath::Vector3 player,bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	virtual void AnimModelRender();
	virtual void ModelRender();
	virtual void OnDeviceLost();
	void Retreat();

	bool GetTimeStopFlag() { return do_time_stop_flag; }

	bool EffectInit();
	void HitEffect();
	void DeathEffect();

	virtual void Damage();
	virtual bool LifeDeathDecision() { return LIVE; }

	DX9::SKINNEDMODEL& GetAnimModel() { return anim_model; }
	DX9::MODEL& GetModel()			  { return model; }
	Collision GetBox()				  { return col; }

	std::string GetTag() { return enemy_tag; }

private:
	void TimeStopDecision();
	void EnemyAnimation();
	void IsRetreat();
	
	EFFECTHANDLE hit_handle,star_handle,die_handle,love_handle;
	EFFECT hit, star, die, love;

	ExplodeMan explode;

	SimpleMath::Vector3 death_effect_pos;
	SimpleMath::Vector3 hit_effect_pos;

	int   retreat_count   = 0;
	const int max_retreat = 30;

	float dead_frame = 0.0f;
	const float max_dead = 0.5f;

	float auto_destroy_frame = 0.0f;
	const float max_auto_destroy = 1.5f;

	const float retreat_dist = 15.0f;

	bool reduce_audience_flag = false;

	//!演出をする敵かのフラグ
	bool enemy_stop_flag = false;

	//!動きを止めるフラグ
	bool do_time_stop_flag = false;

	//!ダメージモーション再生用変数
	int is_damage = 0;
	const int max_is_damage = 5;

	//!スタン用
	float stun_frame = 0.0f;
	const float max_stun = 10.0f;

	const float anim_box_size = 2.0f;
	const float box_size      = 2.0f;

	const float anim_adjust_extents_col = 0.02f;
	
protected:
	virtual void Action() {}
	virtual void Move()   {}
	void SetAnimation(DX9::SKINNEDMODEL& model,const int enabletack,int max_motion);
	void AdjustAnimCollision();
	bool Stun();

	D3DMATERIAL9  material;
	DX9::SKINNEDMODEL anim_model;

	DX9::MODEL   model;
	DX9::MODEL	 collision;
	DX9::MODEL	 obstacle_collision;

	SimpleMath::Vector3  init_pos;
	SimpleMath::Vector3  position;
	SimpleMath::Vector3  enemy_speed;
	SimpleMath::Vector3  player_pos;

	std::string enemy_tag;

	const float fit_collision_y = 4.0f;

	const float rotate = 45.0f;

	int enemy_hp;
	float delta;

	bool retreat_flag;

	Collision col;
};