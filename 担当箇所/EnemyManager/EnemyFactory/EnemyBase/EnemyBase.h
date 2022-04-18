#pragma once

#include"MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "Base/DX12Effekseer.h"

using namespace DirectX;

typedef struct Collision {
	//“Gƒ‚ƒfƒ‹‚Ì“–‚½‚è”»’è
	BoundingBox  box;

	BoundingBox weapon;
};

class EnemyBase
{
public:
	EnemyBase() {};
	~EnemyBase() {};

	virtual bool Initialize(std::string tag, double init_wait, double stop_pos,
		double speed, std::string direct, std::string posture, int hp);

	virtual void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	void LoadModel(LPCWSTR model_name, SimpleMath::Vector3 initial_position);

	virtual int  Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime);
	virtual void Render() {};
	void Retreat();
	void DieFlag();

	void TemporaryDeath();
	bool GetTemporaryDeathFlag() { return temporary_death_flag; }
	bool GetAttackFlag() { return attack_flag; }

	std::string GetPostune() { return enemy_posture; }

	virtual void HitEffect();
	void AutoDestoryEffect();

	virtual bool FrontFlag();

	virtual void Damage();
	virtual bool LifeDeathDecision() { return LIVE; }

	void IsCollision();
	void OffCollision();
	bool hit_test();
	bool Offhit_test();
	bool GetDieFlag() { return die_flag; }
	DX9::SKINNEDMODEL& GetAnimModel() { return anim_model; }
	DX9::MODEL& GetModel() { return model; }
	Collision GetBox() { return col; }

	std::string GetTag() { return enemy_tag; }

private:
	EFFECTHANDLE hit_handle, star_handle, confetti_handle, die_handle, del_handle;
	EFFECT hit, star, confetti, normal_die, del;

	SimpleMath::Vector3 death_effect_pos;
	SimpleMath::Vector3 hit_effect_pos;

	std::string enemy_tag;

	int   retreat_count;
	const int max_retreat = 10;

	float auto_destroy_frame;
	const float max_auto_destroy = 1.5f;

	float damage_frame;
	const float max_damage = .8f;

	const float retreat_dist = 10.0f;

	bool dest_flag;

	const float box_size = 2.0f;

protected:
	virtual void Action() {}
	virtual void Move() {}
	//virtual void IsDeath();
	virtual void IsRetreat();
	virtual void IsDamage();

	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack, int max_motion);
	void NormalDeathEffect(float max_death, bool confetti_effect, bool death_effect, int effect_count);
	void AdjustAnimCollision();

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

	float init_wait_frame;
	float death_frame;
	float max_init_wait;

	float dead_frame;
	const float max_dead = 2.f;

	std::string enemy_direct;
	std::string enemy_posture;

	int    enemy_hp;
	int    init_hp;
	double move_speed;
	double enemy_stop;
	float  delta;

	bool damage_flag;
	bool retreat_flag;
	bool die_flag;
	bool attack_flag;
	bool temporary_death_flag;

	bool confetti_effect_flag;
	bool death_effect_flag;
	int effect_count;

	float is_freeze;
	float is_damage;

	Collision col;

	int direct;

	enum {
		CONFINETTI = 1,
		DEATH = 2
	};
};