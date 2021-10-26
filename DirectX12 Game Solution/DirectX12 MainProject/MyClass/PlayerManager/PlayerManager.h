#pragma once

using namespace DirectX;

class PlayerManager
{
public:

	PlayerManager() {};
	~PlayerManager() {};

	bool Initialize();
	void LoadAssets();
	int Update(DX9::MODEL& ground, const float deltaTime);
	void Render();

	DX9::SKINNEDMODEL& GetModel() { return model; }
	DX9::MODEL& GetCollision()	  { return collision; };

private:
	//�v���C���[
	DX9::SKINNEDMODEL model;

	SimpleMath::Vector3 player_pos = SimpleMath::Vector3(0.0f, 0.0f, 50.0f);

	//�v���C���[�̃X�s�[�h
	float player_speed_ = 30.0f;

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

	BoundingBox model_attack_;



	//�W�����v���Ă邩�̃t���O�B
	bool jump_flag_ = false;
	float jump_time_ = 0.0f;
	float jump_start_v_;

	//�d�͉����x
	float gravity_ = 9.81f;
	//����
	float V0 = 10.0f;


};
