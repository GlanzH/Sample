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

	PlayerBase() {};
	~PlayerBase() {};

	bool Initialize();
	void LoadAssets();
	int Update(const float deltaTime);
	void Render();

	DX9::SKINNEDMODEL& GetModel() { return model; }

	Collisions GetBox() { return col; }

	BoundingBox GetParryBox() { return parry_box; }

	void OnCollisionEnter();
	void OnParryArea();

	bool GetParryFlag() { return parry_flag; }
	bool IsAttack();

	int GetDamage() { return damage; }

	int GetAttackCount() { return motion_count; }

	float GetAppielTime() { return appeil_time; }//�A�s�[�����Ă��鎞��

	bool IsDeathbrow() { return deathbrow_flag; }//�K�E�Z�����t���O

	bool GetAppealCoolFlag() { return appeil_cool_flag; }

	bool GetSpecialAttackFlag() { return special_attack_flag; }


	void _2DRender();

	void BrackImage();



private:
	//�A�j���[�V����
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);

	//�ړ�
	void Player_move(const float deltaTime);
	//�ړ�����
	void Player_limit();
	//�W�����v
	void Player_jump(const float deltaTime);
	//�U��
	void Player_attack(const float deltaTime);
	//�p���B
	void Parry(const float deltaTime);
	//���G����
	void Invincible(const float deltaTime);
	//�A�s�[��
	void Appeal(const float deltaTime);
	//�K�E�Z
	void Player_Special_Move(const float deltaTime);

	//�v���C���[�̍U��(�{�^���ύXver)
	void Player_Attack_two(const float deltaTime);

	void Attack(const float deltaTime);

	//�G�t�F�N�g1����
	void Attack_First(const float deltaTime);
	//�G�t�F�N�g2����
	void Attack_Secnod(const float deltaTime);
	//�G�t�F�N�g3����
	void Attack_Third(const float deltaTime);

	DX9::SPRITEFONT font;

	D3DMATERIAL9 material;

	//���̓����蔻��{�b�N�X
	BoundingBox sword_box;
	BoundingBox box;


	//�����蔻��p���f��
	DX9::MODEL sword_collision;
	DX9::MODEL collision;
	Collisions col;

	int damage = 0;

	//�v���C���[
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scale = 0.1f;
	float model_rotetion = -90.0f;

	//�v���C���[�̈ړ�����(��)
	const float model_collision_detection_X = 67.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN = 0.1f;
	const float model_collision_detection_Z = 100.0f;

	//�����蔻�胂�f���̑傫��
	const int player_box_size_y = 7;
	const int player_box_size_x = 5;
	const int player_box_size_z = 3;

	const int box_size_x = 30;
	const int box_size_y = 15;
	const int box_size_z = 3;


	//�v���C���[�̃X�s�[�h
	const float player_speed_ = 25.0f;

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

	//�p���B
	const float  max_parry_count = 0.5f;
	float		 parry_count = 0.0f;
	bool	     parry_flag = false;

	BoundingBox parry_box;
	DX9::MODEL  parry_collision;

	float parry_box_size_x = 3.0f;
	float parry_box_size_y = 10.0f;
	float parry_box_size_z = 2.0f;

	//�K�E�Z
	bool special_attack_flag;

	//�U���]3�A���]�J�E���g
	int attack_count;

	//�U���̃J�E���g(�b)
	float attack_count_time;

	//�U���̎���
	bool  attack_flag;
	float attack_zeit;
	float attack_zeit_max;

	//�U���̃N�[���^�C��
	bool cool_time_flag_zwei;
	float cool_time_zwei;
	float cool_time_max_zwei;
	int count;

	bool  count_flag;
	float count_time;
	float count_time_max;

	//�U��-����
	bool first_attaack_flag;

	//�U��-�J�E���g-�t���O
	//���[�V����
	bool motion_time_start_flag;

	bool motion_attack_flag;

	float motion_time;
	float motion_time_max[3]{ 0.617f,0.517f,0.583f };
	int   motion_count;

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
		FIRST,
		SECOND,
		THIRD
	};

	CANNOT_OTHER_ATTACK cannot_other;

	//�G�t�F�N�g�̔����^�C�~���O��
	bool  effect_generation;
	float effect_generation_time;
	float effect_generation_time_max[3]{ 1.0f,0.033f,0.005f };//�t���[��(19f,2f,11f)

	bool effect_end_flag;


	bool  first_attack_hit;
	float first_attack_time;
	float first_attack_time_max;


	//���G����
	bool        invincible_flag;
	float		invincible_time;
	const float invincible_time_max = 0.2f;

	//�v���C���[���_���[�W����������̕ϐ�


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
		MOTION_MAX
	};

	//�ύX*2
	//���[�V�����n��
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

	//���͎�t���Ԃ܂ł̎��� & �G�t�F�N�g�\���܂ł̎���
	bool  input_wait_flag;
	float input_wait_time;
	float input_wait_time_max[3]{ 0.433f,0.05f,0.2f };//(3��ڂ̓G�t�F�N�g�\���̂�)
	int   input_wait_count;

	//���͎�t����
	bool  input_flag;
	float input_time;
	float input_time_max[2]{ 0.633f, 0.8f };
	int   input_count;

	//�G�t�F�N�g�\��
	bool effect_flag;

	//�A�j���[�V�������o������
	bool  animation_flag;
	float animation_time;
	float animation_time_max[3]{ 0.967f,0.850f,0.583f };
	int   animation_count;

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



	
};