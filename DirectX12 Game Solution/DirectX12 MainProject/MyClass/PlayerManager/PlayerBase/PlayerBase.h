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

	int GetAttackTag() { return attack_type; }//1 = ��i�U�� - Y, 2 = ���i�U�� - X

	bool GetEnemyDeathFlag() { return elimination_flag; }//�G�l�~�[�̏���


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

	//�U��
	void Attack_Relation(const float deltaTime);
	//�~�艺�낵
	void Swing_Down(const float deltaTime);
	//�؂�グ
	void Reverse_Slash(const float deltaTime);


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
	float model_scale = 1.0f;
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

	const int box_size_x = 3.5;
	const int box_size_y = 2;
	const int box_size_z = 4;

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
	const float gravity_ = 170.0f;
	//����
	const float V0 = 70.5f;

	//�W�����v�^�C�~���O
	bool  jump_start_flag;
	float jump_start_time;
	float jump_start_time_max;

	bool jump_end_flag;



	//�U���̎���
	bool  attack_flag;
	float attack_time;
	float attack_zeit_max;


	//�U�����@�W�����v�s��
	enum UNDER_ATTACK_STATE
	{
		NOMAL,
		ATTACK
	};

	UNDER_ATTACK_STATE under_attack_state_mode;

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
		FINISH,
		REBOUND,
		JUMP,
		ROLL,
		DAMAGE1,
		MOTION_MAX
	};

	//�U���̌���
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//�w�g�p���Ȃ��x****************************//
		//�A�s�[��
	bool appeil_flag;
	float appeil_time;
	bool appeil_cool_flag;
	//�K�E�Z
	bool deathbrow_flag;//�K�E�Z�����t���O
//*****************************************//

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
	float avoidance_move;


	//�U���̎�� 1:��U���@2:�˂��U��
	int attack_type;

	//�m�b�N�o�b�N
	void Knock_back_Move();

	bool knock_back_flag;
	float knock_back_start;
	float knock_back_end;
	float time_other;

	//�N���オ��
	void Rize();

	float rize_end;

	enum Damage_Mode
	{
		NOMAL_STATE, //�ʏ���
		KNOCK_BACK   //�m�b�N�o�b�N
	};
	Damage_Mode damage_mode_state;



	//��i(�ϐ��錾)
	enum Upper_State
	{
		NOT_UPPER,
		UPPER_ATTACK
	};
	Upper_State upper_state_mode;
	float upper_start;
	float upper_end;

	//���i(�ϐ��錾)
	enum Lower_State
	{
		NOT_LOWER,
		LOWER_ATTACK
	};
	Lower_State lower_sate_mode;
	float lower_start;
	float lower_end;


	void Upper_Effect();

	//�[��
	void Sword_Delivery(const float deltaTime, bool temp);
	bool  s_del_flag;
	float s_del_start;
	float s_del_end;

	//�G�̏���
	bool elimination_flag;
	float elimination_end;

	//�U�� �e�����
	void Frip(const float deltaTime);

	enum Frip_State
	{
		NOT_FRIP,
		ATTACK_TEST,
		FRIP
	};
	Frip_State frip_state_mode;

	float not_attack_start = 0.0f;
	float not_attack_end = 0.3f;

	float frip_start = 0.0f;
	float frip_end = 0.783f;
};