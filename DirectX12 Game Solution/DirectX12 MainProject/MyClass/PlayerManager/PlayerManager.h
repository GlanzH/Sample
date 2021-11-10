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
	int Update(DX9::MODEL& ground,  const float deltaTime);
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

	const int box_size = 2;
	

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

	//�G�t�F�N�g
	EFFECT Sword_Effect_;
	EFFECTHANDLE handle;

	//���G����
	bool  invincible_flag      = false;
	float invincible_count     = 0.0f;
	float invincible_count_max = 0.05f;



	//�W�����v���Ă邩�̃t���O�B
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//1/2
	const float half = 0.5f;
	//�d�͉����x
	const float gravity_ = 100.0f;
	//����
	const float V0 = 45.0f;

	//�p���B
	const int max_parry_count = 40;
	int		  parry_count = 0;
	bool	  parry_flag = true;


	//�v���C���[�̍U���͈�
	BoundingBox sword_box;
	DX9::MODEL  sword_collision;

	

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
	void Player_attack();
	//�p���B
	void Parry();

};