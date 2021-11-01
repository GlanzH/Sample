#pragma once

using namespace DirectX;

#include "MyClass/EnemyManager/EnemyBase/EnemyBase.h"

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

	DX9::SKINNEDMODEL& GetModel() { return model; }
	BoundingBox  GetBox()		  { return  box; }
	bool GetHitFlag()			  { return hit_flag; }

	static PlayerManager& Instance() {
		static PlayerManager instance;
		return instance;
	}
private:
	//�v���C���[
	DX9::SKINNEDMODEL model;
	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);
	float model_scsle = 0.04f;
	float model_rotetion = -90.0f;

	//�v���C���[�̈ړ�����(��)
	float model_collision_detection_X     = 495.0f;
	float model_collision_detection_Y_MAX = 1000.0f;
	float model_collision_detection_Y_MIN =   -5.0f;
	float model_collision_detection_Z     =  100.0f;


	BoundingBox box;
	D3DMATERIAL9 material;

	int box_size = 2;

	//�v���C���[�̃X�s�[�h
	float player_speed_ = 70.0f;

	DX9::MODEL collision;

	enum
	{
		Wait,
		Koke,
		Jump,
		Push,
		Run,
		Walk,
		MOTION_MAX
	};

	void SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack);




	//�W�����v���Ă邩�̃t���O�B
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//�d�͉����x
	float gravity_ = 100.0f;
	//����
	float V0 = 28.0f;

	bool hit_flag = false;

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

	EnemyBase* enemy;

};
