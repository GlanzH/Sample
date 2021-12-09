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
	DX9::SPRITE curtain;

	SimpleMath::Vector3 curtain_pos;

	float time_delta;
	bool ending_coro_flag;
	bool scene_change_flag;

	// �R���[�`���̃v���g�^�C�v�錾
	cppcoro::generator<int> Ending();
	cppcoro::generator<int>	                 co_ending;
	cppcoro::detail::generator_iterator<int> co_ending_it;

};