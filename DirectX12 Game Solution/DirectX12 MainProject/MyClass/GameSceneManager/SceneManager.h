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
	void Update(const float deltaTime, bool clear_flag);
	void Render();

	bool ReturnSceneFlag() { return scene_change_flag; }	//�V�[���؂�ւ�

	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	}

private:
	//�J�[�e��
	DX9::SPRITE curtain;
	SimpleMath::Vector3 curtain_pos;
	bool curtain_move_flag;
	const float CURTAIN_START_POS = -900.0f;

	//�u���b�N
	DX9::SPRITE black;
	int black_alpha;

	//����
	const float CURTAIN_DOWN_SPEED = 400.0f;

	bool scene_change_flag;	//�V�[���؂�ւ��\�t���O
};