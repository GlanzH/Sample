#pragma once
#include "Base/pch.h"
#include <DirectXTK9.h>
#include <Base/dxtk.h>
#include "cppcoro/generator.h"
#include "Scene.h"

using namespace DirectX;

class SceneManager {
public:
	SceneManager() {};
	~SceneManager() {};


	void Initialize();
	void LoadAsset();
	void Update(const float deltaTime);
	void Render();

	bool ReturnSceneFlag() { return scene_change_flag; }//�V�[���؂�ւ�

	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	}

private:
	//�J�[�e��
	DX9::SPRITE curtain;
	SimpleMath::Vector3 curtain_pos;
	const float CURTAIN_START_POS = -720.0f;

	//����
	float time_delta;
	const float CURTAIN_DOWN_SPEED = 150.0f;

	//�t���O
	bool ending_coro_flag;	//�R���[�`���N��
	bool scene_change_flag;	//�V�[���؂�ւ�

	// �R���[�`���̃v���g�^�C�v�錾
	cppcoro::generator<int> Ending();
	cppcoro::generator<int>	                 co_ending;
	cppcoro::detail::generator_iterator<int> co_ending_it;

};