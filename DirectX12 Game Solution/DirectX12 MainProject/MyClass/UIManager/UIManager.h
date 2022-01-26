#pragma once
#include "Base/pch.h"
#include <DirectXTK9.h>
#include <Base/dxtk.h>
#include "Base/DX12Effekseer2D.h"

using namespace DirectX;

class UIManager {
public:
	UIManager() {};
	~UIManager() {};

	void Initialize();
	void LoadAsset();
	void Update(const float deltaTime, int enemy_num, int enemy_dath);
	void Render();
	void EfkRender();

	static UIManager& Instance() {
		static UIManager instance;
		return instance;
	}

	void ResetAnimeFrame();	//�A�j���[�V�����Đ������Z�b�g
	void SetAddScore(int add_size);
	void PlayUIEffect();

private:
	void Animation(const float deltaTime);


	//�X�R�A
	DX9::SPRITE score_good_empty;
	DX9::SPRITE score_good_max;
	DX9::SPRITE score_bad_empty;
	DX9::SPRITE score_bad_max;
	EFFECT good_effect;
	EFFECT bad_effect;
	EFFECTHANDLE effect_handle;

	int score_width;
	bool effect_play_flag;

	const int SCORE_MAX_HIGHT = 96;
	const int SCORE_MIN_WIDTH = 81;
	const float SCORE_POS_X = 30.0f;
	const float SCORE_POS_Y = 20.0f;
	const float SCORE_EMPTY_POS_Z = 0.0f;
	const float SCORE_MAX_POS_Z = -1.0f;


	//���j�R���{
	DX9::SPRITE combo_base;	//�����o���̕���
	DX9::SPRITE combo_gauge;	//�R���{�̃Q�[�W
	DX9::SPRITE combo;	//�R���{����
	DX9::SPRITE combo_number;	//�R���{��

	int combo_anime;
	int combo_gauge_width;
	int combo_one_digit;
	int combo_two_digit;
	int combo_num;
	float combo_anime_frame;	//�A�j���[�V�����g�p�ϐ�

	bool combo_digit_up_flag;

	const int COMBO_BASE_WIDTH = 331;
	const int COMBO_BASE_HIGHT = 232;
	const int COMBO_GAUGE_HIGHT = 5;
	const int COMBO_NUM_HIGHT = 60;
	const int COMBO_NUM_WIDTH = 48;

	const float COMBO_BASE_POS_X = 950.0f;
	const float COMBO_BASE_POS_Y = 500.0f;

	const float COMBO_GAUGE_POS_X = COMBO_BASE_POS_X + 80.0f;
	const float COMBO_GAUGE_POS_Y = COMBO_BASE_POS_Y + 130.0f;
	const float COMBO_GAUGE_DIVIDE = 24.4f;	//�R���{�Q�[�W7����1�̐�(�`�掞�g�p)

	//�R���{(����)
	const float COMBO_POS_X = COMBO_BASE_POS_X + 140.0f;
	const float COMBO_POS_Y = COMBO_BASE_POS_Y + 100.0f;

	const float COMBO_ONE_DIGIT_X = COMBO_POS_X - 50.0f;
	const float COMBO_ONE_DIGIT_Y = COMBO_POS_Y - 30.0f;

	const float COMBO_TWO_DIGIT_X = COMBO_POS_X - 90.0f;
	const float COMBO_TWO_DIGIT_Y = COMBO_POS_Y - 30.0f;


	//�G�c�萔
	DX9::SPRITE enemy;
	DX9::SPRITE enemy_dead;
	int enemy_width;
	int enemy_dead_width;

	const int ENEMY_MIN_WIDTH = 42;
	const int ENEMY_HIGHT = 42;

	//2D�J����
	DX12::CAMERA camera;
};