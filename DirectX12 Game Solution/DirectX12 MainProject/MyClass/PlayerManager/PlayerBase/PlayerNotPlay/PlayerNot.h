#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerNot
{
public:
	PlayerNot();
	~PlayerNot();

	void Initialize();

	//�U��
	void Player_attack(const float deltaTime);

	//�v���C���[�̍U��(�{�^���ύXver)
	void Player_Attack_two(const float deltaTime);

	void Attack(const float deltaTime);

	//�G�t�F�N�g1����
	void Attack_First(const float deltaTime);
	//�G�t�F�N�g2����
	void Attack_Secnod(const float deltaTime);
	//�G�t�F�N�g3����
	void Attack_Third(const float deltaTime);



private:
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

	//�G�t�F�N�g�̔����^�C�~���O��
	bool  effect_generation;
	float effect_generation_time;
	float effect_generation_time_max[3]{ 1.0f,0.033f,0.005f };//�t���[��(19f,2f,11f)

	bool effect_end_flag;


	bool  first_attack_hit;
	float first_attack_time;
	float first_attack_time_max;

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

};