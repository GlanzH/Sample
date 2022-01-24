#pragma once

#include"MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/AudianceManager/ExplodeMan/ExplodeMan.h"
#include "Base/DX12Effekseer.h"

using namespace DirectX;

typedef struct Collision {
	//敵モデルの当たり判定
	BoundingBox  box;

	BoundingBox weapon;
};

class EnemyBase
{
public:
	EnemyBase() {};
	~EnemyBase() {};

	virtual bool Initialize(std::string tag, double init_wait, double stop_pos, std::string time_stop_flag,
		double speed, std::string direct, std::string posture, int hp);

	virtual void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	void LoadModel(LPCWSTR model_name, SimpleMath::Vector3 initial_position);

	virtual int  Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	virtual void Render() {};
	void Retreat();
	void DieFlag();

	void TemporaryDeath(float max_death);
	bool GetTimeStopFlag() { return do_time_stop_flag; }
	bool GetTemporaryDeathFlag() { return temporary_death_flag; }
	bool GetAttackFlag() { return attack_flag; }

	std::string GetPostune() { return enemy_posture; }

	void HitEffect();
	void NormalDeathEffect();
	void SpecialDeathEffect();
	void AutoDestoryEffect();

	virtual void Damage();
	virtual bool LifeDeathDecision() { return LIVE; }

	DX9::SKINNEDMODEL& GetAnimModel() { return anim_model; }
	DX9::MODEL& GetModel() { return model; }
	Collision GetBox() { return col; }

	std::string GetTag() { return enemy_tag; }

private:
	void TimeStopDecision();
	void IsDamage();

	EFFECTHANDLE hit_handle, star_handle, confetti_handle, die_handle, special_die_handle, love_handle,del_handle;
	EFFECT hit, star, confetti, normal_die, special_die, love,del;

	ExplodeMan explode;

	SimpleMath::Vector3 death_effect_pos;
	SimpleMath::Vector3 hit_effect_pos;

	std::string enemy_tag;

	int   retreat_count = 0;
	const int max_retreat = 30;

	float auto_destroy_frame = 0.0f;
	const float max_auto_destroy = 1.5f;

	float damage_frame = 0.0f;
	const float max_damage = 2.0f;

	const float retreat_dist = 15.0f;

	bool reduce_audience_flag = false;

	//!演出をする敵かのフラグ
	std::string enemy_stop_flag = "";

	//!動きを止めるフラグ
	bool do_time_stop_flag = false;

	bool damage_flag = false;

	//!スタン用
	float stun_frame = 0.0f;
	const float max_stun = 10.0f;

	const float box_size = 2.0f;

protected:
	virtual void Action() {}
	virtual void Move() {}
	//virtual void IsDeath();
	virtual void IsRetreat();

	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack, int max_motion);
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

	const float anim_adjust_extents_col = 0.3f;
	const float fit_collision_y = 3.0f;

	const float rotate = 45.0f;

	float init_wait_frame = 0.0f;
	float death_frame = 0.0f;
	float max_init_wait;

	float dead_frame = 0.0f;
	const float max_dead = 0.6f;

	std::string enemy_direct;
	std::string enemy_posture;

	int    enemy_hp;
	double move_speed;
	double enemy_stop;
	float delta;

	bool retreat_flag;
	bool die_flag    = false;
	bool attack_flag = false;
	bool temporary_death_flag = false;

	Collision col;
};