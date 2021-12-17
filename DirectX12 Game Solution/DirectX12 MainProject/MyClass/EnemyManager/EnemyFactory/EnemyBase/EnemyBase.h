#pragma once

#include"MyClass/EnumManager/EnumManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/AudianceManager/ExplodeMan/ExplodeMan.h"
#include "Base/DX12Effekseer.h"

using namespace DirectX;

typedef struct Collision {
	//�G���f���̓����蔻��
	BoundingBox  box;
	//���̓����蔻��
	BoundingBox  fire;
	//�e�̓����蔻��
	BoundingSphere bullet;
};

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase() {};

	virtual bool Initialize(std::string tag, bool time_stop_flag, int hp);
	void LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position);
	virtual int Update(SimpleMath::Vector3 player,bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	virtual void Render();
	virtual void OnDeviceLost();
	void Retreat();

	bool GetTimeStopFlag() { return do_time_stop_flag; }

	bool EffectInit();
	void HitEffect();
	void DeathEffect();

	virtual void Damage(int damage);
	bool LifeDeathDecision();

	DX9::SKINNEDMODEL& GetAnimModel() { return anim_model; }
	DX9::MODEL& GetModel()			  { return model; }
	BoundingBox GetAnimBox()		  { return anim_box; }
	Collision GetBox()				  { return col; }

	std::string GetTag() { return enemy_tag; }

private:
	void TimeStopDecision();
	void EnemyAnimation();
	
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

	bool damage_flag = false;
	bool reduce_audience_flag = false;

	//!���o������G���̃t���O
	bool enemy_stop_flag = false;

	//!�������~�߂�t���O
	bool do_time_stop_flag = false;

	//!�_���[�W���[�V�����Đ��p�ϐ�
	int is_damage = 0;
	const int max_is_damage = 5;

	//!�_���[�W�󂯂��Ƃ��Ɏ~�܂�p
	float damage_frame = 0.0f;
	const float max_damage_frame = 1.0f;

	const float anim_box_size = 2.0f;
	const float box_size      = 1.5f;

	const float anim_adjust_extents_col = 0.02f;

	const float anim_init_rotate = 10.0f;
	const float init_rotate      = 90.0f;
	
protected:
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack);
	bool IsDamage();
	D3DMATERIAL9  material;
	DX9::SKINNEDMODEL anim_model;
	BoundingBox		  anim_box;
	DX9::MODEL		  anim_collision;

	DX9::MODEL   model;
	DX9::MODEL	 collision;
	DX9::MODEL	 obstacle_collision;

	SimpleMath::Vector3  position;
	SimpleMath::Vector3  enemy_speed;
	SimpleMath::Vector3  player_pos;

	std::string enemy_tag;

	const float fit_collision_y = 4.0f;
	int enemy_hp;
	float delta;

	bool retreat_flag;

	Collision col;

	enum ENEMYMOSION
	{
		EXIT_JUMP,
		DAMAGE,
		WAIT,
		MAX_MOTION
	};
};