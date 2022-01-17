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
	int Update(const float deltaTime);
	void Render();

	void OnCollisionEnter(std::string tag);
	void OnWeaponCollisionEnter(std::string tag);
	void OnParryArea();

	bool IsAttack();

	void Debug();
	void OnDeviceLost();

	//�A�j���[�V����
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);


	DX9::SKINNEDMODEL& GetModel() { return model; }

	Collisions GetBox() { return col; }

	//���E�̓����蔻��(�m�b�N�o�b�N�p)
	DX9::MODEL& GetRightModel() { return right_collision; }
	DX9::MODEL& GetLeftModel() { return left_collision; }


	int GetDamage() { return damage; }

	int GetAttackCount() { }

	float GetAppielTime() { return appeil_time; }//�A�s�[�����Ă��鎞��

	bool IsDeathbrow() { return deathbrow_flag; }//�K�E�Z�����t���O

	bool GetAppealCoolFlag() { return appeil_cool_flag; }


	bool IsInvincibleFlag() { return invincible_flag; }//���G�t���O

	bool IsAvoidance() { return avoidance_flag; }//����t���O

	int GetAttackTag() { return attack_type; }//�U���̎��


private:

	//�ړ�
	void Player_move(const float deltaTime);
	//�ړ�����
	void Player_limit();
	//�W�����v
	void Player_jump(const float deltaTime);
	//���G����
	void Invincible(const float deltaTime);
	//�m�b�N�o�b�N
	void Knock_Back();
	//�v���C���[�̍U��(3��ڕύX)
	void Player_Attack_Three(const float deltaTime);
	//�O�A��
	void Burst_Attack(const float deltaTime);
	//���
	void Avoidance(const float deltaTime);


	DX9::SPRITEFONT font;

	D3DMATERIAL9 material;

	//���̓����蔻��{�b�N�X
	BoundingBox sword_box;
	BoundingBox box;


	BoundingBox right_box;
	BoundingBox left_box;

	//�����蔻��p���f��
	DX9::MODEL sword_collision;
	DX9::MODEL collision;
	Collisions col;

	DX9::MODEL right_collision;
	DX9::MODEL left_collision;

	int damage = 0;
	int reduce_num = 0;

	const int body_reduce_num = -20;
	const int weapon_reduce_num = -40;

	const int mb_reduce_num = -30;
	const int mb_weapon_reduce_num = -60;

	//�v���C���[
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scale = 0.25f;
	float model_rotetion = -90.0f;

	//�v���C���[�̈ړ�����(��)
	const float model_collision_detection_X = 67.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN = 0.1f;
	const float model_collision_detection_Z = 100.0f;

	//�����蔻�胂�f���̑傫��
	const int player_box_size_y = 5;
	const int player_box_size_x = 5;
	const int player_box_size_z = 3;

	const int box_size_x = 3;
	const int box_size_y = 2;
	const int box_size_z = 3;

	const int sidebox_size_x = 2;
	const int sidebox_size_y = 9;
	const int sidebox_size_z = 1;


	//�v���C���[�̃X�s�[�h
	const float player_speed_ = 40.0f;

	//�W�����v���Ă邩�̃t���O
	bool jump_flag_;
	float jump_time_;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//�d�͉����x
	const float gravity_ = 120.0f;
	//����
	const float V0 = 50.0f;

	//�W�����v�^�C�~���O
	bool  jump_start_flag;
	float jump_start_time;
	float jump_start_time_max;

	bool jump_end_flag;



	//�U���̎���
	bool  attack_flag;
	float attack_zeit;
	float attack_zeit_max;


	//�U�����@�W�����v�s��
	enum UNDER_ATTACK_STATE
	{
		NOMAL,
		ATTACK
	};

	UNDER_ATTACK_STATE under_attack_state_mode;

	//�U�����@�ړ��s��
	enum CANNOT_MOVE_STATE
	{
		MOVE,
		CANNOT_MOVE
	};

	CANNOT_MOVE_STATE canot_move_state_mode;

	//�U���� ���̍U���s��
	enum CANNOT_OTHER_ATTACK
	{
		NOMAL_STATE,
		ACCUMULATION,
		LIGHT
	};

	CANNOT_OTHER_ATTACK cannot_other;


	//���G����
	bool        invincible_flag;
	float		invincible_time;
	float       invincible_time_max;

	//���[�V�����̖��O
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
		ROLL,
		MOTION_MAX
	};

	//�U���̌���
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//�A�s�[��
	bool appeil_flag;

	float appeil_time;
	float appeil_time_max;

	float appeil_cool_time;
	float appeil_cool_time_max;

	bool appeil_cool_flag;

	//�K�E�Z
	bool deathbrow_flag;//�K�E�Z�����t���O

	bool deathbrow_attack;//�K�E�Z�̓����蔻��

	float specialmove_time;
	float specialmove_time_max;

	//�Ó]
	DX9::SPRITE deathbrow_sprite;
	int Transparency;
	int Blackout;
	int Blackout_max;
	bool Blackout_flag;

	//���]
	bool bright_flag;
	int  Ming_Turn;

	//SE �ϐ�
	//�U��-SE
	XAudio::SOUNDEFFECT  first_attack_se;
	XAudio::SOUNDEFFECT second_attack_se;
	XAudio::SOUNDEFFECT  third_attack_se;
	//�W�����v
	XAudio::SOUNDEFFECT jump_se;
	//���n
	XAudio::SOUNDEFFECT landing_se;

	//�_���[�W
	XAudio::SOUNDEFFECT damege_se;

	//�A�s�[��
	XAudio::SOUNDEFFECT appeal_se;


	//************************************//


	//���
	bool  avoidance_flag;
	float avoidance_start;
	float avoidance_max;


	//�U���̎�� 1:��U���@2:�˂��U��
	int attack_type;

	//�m�b�N�o�b�N
	bool knock_back_flag;
	float knock_back_start;
	float knock_back_end;
	float time_other;

	//�O�A��

	enum  BURST_STATE
	{
		NOT_BURST,
		FIRST,
		SECOND,
		THIRD
	};
	BURST_STATE burst_state_mode;

	void Not_Burst(const float deltaTime);

	//First
	void First_Burst(const float deltaTime);
	bool first_burst_flag;
	float first_burst_start;
	float first_burst_end;

	//Second
	void Second_Burst(const float deltaTime);
	bool second_burst_flag;
	float second_burst_start;
	float second_burst_end;

	//THIRD
	void Third_Burst(const float deltaTime);
	bool third_burst_flag;
	float third_burst_start;
	float third_burst_end;

};