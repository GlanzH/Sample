#pragma once

using namespace DirectX;

#include "Base/DX12Effekseer.h"

#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/PlayerManager/Sword/Sword.h"


class PlayerManager
{
public:

	PlayerManager() {};
	~PlayerManager() {};

	bool Initialize();
	void LoadAssets();
	int Update(DX9::MODEL& ground, const float deltaTime);
	void Render();
	void _2DRender();

	void OnCollisionEnter();
	void OnParryArea();

	bool GetParryFlag() { return parry_flag; }

	bool IsAttack();


	DX9::SKINNEDMODEL& GetModel() { return model; }
	BoundingBox  GetBox()  { return  box; }

	BoundingBox GetSwordBox() { return sword_box; }

private:
	//�v���C���[
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scsle = 500.0f;
	float model_rotetion = -90.0f;

	//�v���C���[�̈ړ�����(��)
	const float model_collision_detection_X     = 495.0f;
	const float model_collision_detection_Y_MAX = 1000.0f;
	const float model_collision_detection_Y_MIN =   -5.0f;
	const float model_collision_detection_Z     =  100.0f;


	BoundingBox box;
	D3DMATERIAL9 material;

	const int box_size = 4;
	

	//�v���C���[�̃X�s�[�h
	const float player_speed_ = 40.0f;

	DX9::MODEL collision;

	//�A�j���[�V����
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);

	enum
	{
		Wait,
		Run,
		Jump,
		Damage,
		Attack_S,
		Attack_L,
		Parry_,
		Appeil,
		MOTION_MAX
	};



	//�W�����v���Ă邩�̃t���O�B
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//�d�͉����x
	const float gravity_ = 110.0f;
	//����
	const float V0 = 50.0f;

	//�p���B
	const int max_parry_count = 40;
	int		  parry_count = 0;
	bool	  parry_flag = false;


	//�v���C���[�̍U���͈�
	BoundingBox sword_box;
	DX9::MODEL  sword_collision;

	//�U���̌���
	enum Direction_State
	{
		LEFT,
		RIGHT
	};

	Direction_State direction_state_mode;

	//�U���]3�A���]�J�E���g
	int attack_count;

	//�U���̃J�E���g(�b)
	float attack_count_time;

	//�U���̃N�[���^�C��
	bool cool_time_flag   = false;
	float cool_time       = 0.0f;
	float cool_time_max = 0.4f;

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


	//���G����
	bool  invincible_flag = false;
	float invincible_time      = 0.0f;
	float invincible_time_max  = 100.0f;

	//�A�s�[��
	enum Appeal_state
	{
		NORMAL,
		APPEAL
	};

	Appeal_state appeal_state_mode;

	float appeal_time     = 0.0f;
	float appeal_time_max = 5.0f;
	
	

	DX9::SPRITEFONT font;

	//�n�ʂƂ̓����蔻��
	void Player_collision_detection(DX9::MODEL& ground);
	float collision_detection = 100.0f;
	//�ړ�
	void Player_move(const float deltaTime);
	//�ړ�����
	void Player_limit();
	//�W�����v
	void Player_jump(DX9::MODEL& ground, const float deltaTime);
	//�U��
	void Player_attack(const float deltaTime);
	//�U���G�t�F�N�g�֌W
	void Player_Attack_Effect();
	//�p���B
	void Parry();
	//���G����
	void Invincible(const float deltaTime);
	//�A�s�[��
	void Appeal(const float deltaTime);


};