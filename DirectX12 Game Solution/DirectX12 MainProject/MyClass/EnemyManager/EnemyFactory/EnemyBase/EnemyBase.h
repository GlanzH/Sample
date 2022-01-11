#pragma once

#include"MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/AudianceManager/ExplodeMan/ExplodeMan.h"
#include "Base/DX12Effekseer.h"

using namespace DirectX;

typedef struct Collision {
	//�G���f���̓����蔻��
	BoundingBox  box;

	BoundingBox weapon;
};

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase() {};

	virtual bool Initialize(std::string tag, bool time_stop_flag, int hp);
	virtual void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	void LoadModel(LPCWSTR model_name, SimpleMath::Vector3 initial_position);

	virtual int  Update(SimpleMath::Vector3 player,bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	virtual void Render() {};
	void OnDeviceLost();
	void Retreat();

	bool GetTimeStopFlag() { return do_time_stop_flag; }

	void HitEffect();
	void NormalDeathEffect();
	void SpecialDeathEffect();

	virtual void Damage();
	virtual bool LifeDeathDecision() { return LIVE; }

	DX9::SKINNEDMODEL& GetAnimModel() { return anim_model; }
	DX9::MODEL& GetModel()			  { return model; }
	Collision GetBox()				  { return col; }

	std::string GetTag() { return enemy_tag; }

private:
	void TimeStopDecision();
	void IsRetreat();
	
	EFFECTHANDLE hit_handle,star_handle,normal_die_handle,special_die_handle,love_handle;
	EFFECT hit, star, normal_die,special_die, love;

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

	//!���o������G���̃t���O
	bool enemy_stop_flag = false;

	//!�������~�߂�t���O
	bool do_time_stop_flag = false;

	//!�_���[�W���[�V�����Đ��p�ϐ�
	int is_damage = 0;
	const int max_is_damage = 5;

	//!�X�^���p
	float stun_frame = 0.0f;
	const float max_stun = 10.0f;

	const float box_size = 2.0f;
	
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

	const float anim_adjust_extents_col = 0.3f;
	const float fit_collision_y = 3.0f;

	const float rotate = 45.0f;

	int enemy_hp;
	float delta;

	bool retreat_flag;

	Collision col;
};