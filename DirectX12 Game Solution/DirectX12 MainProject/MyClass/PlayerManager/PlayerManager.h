#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerManager
{
public:

	PlayerManager() {};
	~PlayerManager() {};

	bool Initialize();
	void LoadAssets();
	int Update(const float deltaTime);
	void Render();
	void _2DRender();

	DX9::SKINNEDMODEL& GetModel() { return model; }

	BoundingBox GetSwordBox() { return sword_box; }
	BoundingBox GetBox() { return  box; }

	void OnCollisionEnter();
	void OnParryArea();

	bool GetParryFlag() { return parry_flag; }
	bool IsAttack();

	int GetDamage() { return damage; }


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

	//�U���G�t�F�N�g
	//1
	EFFECT Sword_Effect_1;
	EFFECTHANDLE handle_1;

	//2
	EFFECT Sword_Effect_2;
	EFFECTHANDLE handle_2;

	//3
	EFFECT Sword_Effect_3;
	EFFECTHANDLE handle_3;

	DX9::SPRITEFONT font;

	D3DMATERIAL9 material;

	//���̓����蔻��{�b�N�X
	BoundingBox sword_box;
	BoundingBox box;


	//�����蔻��p���f��
	DX9::MODEL sword_collision;
	DX9::MODEL collision;

	int damage = 0;

	//�v���C���[
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scale = 0.1f;
	float model_rotetion = -90.0f;

	//�v���C���[�̈ړ�����(��)
	const float model_collision_detection_X = 80.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN = -5.0f;
	const float model_collision_detection_Z = 100.0f;

	//�����蔻�胂�f���̑傫��
	const int player_box_size = 2;
	const int box_size = 4;

	//�v���C���[�̃X�s�[�h
	const float player_speed_ = 40.0f;

	//�W�����v���Ă邩�̃t���O�B
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//�d�͉����x
	const float gravity_ = 120.0f;
	//����
	const float V0 = 50.0f;

	//�p���B
	const float  max_parry_count = 0.5f;
	float		 parry_count = 0.0f;
	bool	     parry_flag = false;

	//�U���]3�A���]�J�E���g
	int attack_count;

	//�U���̃J�E���g(�b)
	float attack_count_time;

	//�U���̎���
	bool  attack_flag = false;
	float attack_zeit = 0.0f;
	float attack_zeit_max = 0.03309f;

	//�U���̃N�[���^�C��
	bool cool_time_flag_zwei = false;
	float cool_time_zwei = 0.0f;
	float cool_time_max_zwei[3]{ 0.2f,0.4f,0.3f };
	int count = 0;

	bool  count_flag = false;
	float count_time = 0.0f;
	float count_time_max = 0.4f;

	//���G����
	bool  invincible_flag = false;
	float		invincible_time = 0.0f;
	const float invincible_time_max = 100.0f;//1.5f;

	//�A�s�[�����鎞��
	float		appeal_time = 0.0f; //�A�s�[�����鏉���l
	const float appeal_time_max = 2.0f; //�A�s�[�����鎞�Ԃ̍ő�l

	//�X�e�[�^�X�A�b�v�̎���
	float		focus_time = 0.0f;//�X�e�[�^�X�A�b�v�̎���:�����l
	const float focus_time_max = 10.0f;//�X�e�[�^�X�A�b�v�̎���:�ő�l

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
		MOTION_MAX
	};


	//���͎�t���Ԃ܂ł̎��� & �G�t�F�N�g�\���܂ł̎���
	bool  input_wait_flag = false;
	float input_wait_time = 0.0f;
	float input_wait_time_max[3]{ 0.433f,0.05f,0.2f };//(3��ڂ̓G�t�F�N�g�\���̂�)
	int   input_wait_count = 0;

	//���͎�t����
	bool  input_flag = false;
	float input_time = 0.0f;
	float input_time_max[2]{ 0.633f, 0.8f };
	int   input_count = 0;

	//�G�t�F�N�g�\��
	bool effect_flag = false;

	//�A�j���[�V�������o������
	bool  animation_flag = false;
	float animation_time = 0.0f;
	float animation_time_max[3]{ 0.967f,0.850f,0.583f };
	int   animation_count = 0;

	//�ŏ��̍U���̃t���O
	bool first_attack_flag = false;

	//�A���U��
	bool attack_next_flag = false;

	//�U���̌���
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//�A�s�[��
	enum Appeal_state
	{
		NORMAL,
		APPEAL,
		FOCUS
	};

	Appeal_state appeal_state_mode;
};