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
	void Update(const float deltaTime);
	void Render();

	static UIManager& Instance() {
		static UIManager instance;
		return instance;
	}

	void ResetAnimeFrame();	//�A�j���[�V�����Đ������Z�b�g
	void SetAddScore(int add_size);
	void SetWaveTime(float wave_time);
	void PlayUIEffect();

	void EfkRender();
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

	const int SCORE_MAX_HIGHT = 119;
	const int SCORE_MIN_WIDTH = 101;
	const float SCORE_POS_X = 79.0f;
	const float SCORE_POS_Y = 58.0f;
	const float SCORE_EMPTY_POS_Z = -99.0f;
	const float SCORE_MAX_POS_Z = -100.0f;


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
	const float COMBO_GAUGE_DIVIDE = 34.2f;	//�R���{�Q�[�W5����1�̐�(�`�掞�g�p)

	//�R���{(����)
	const float COMBO_POS_X = COMBO_BASE_POS_X + 140.0f;
	const float COMBO_POS_Y = COMBO_BASE_POS_Y + 100.0f;

	const float COMBO_ONE_DIGIT_X = COMBO_POS_X - 50.0f;
	const float COMBO_ONE_DIGIT_Y = COMBO_POS_Y - 30.0f;

	const float COMBO_TWO_DIGIT_X = COMBO_POS_X - 90.0f;
	const float COMBO_TWO_DIGIT_Y = COMBO_POS_Y - 30.0f;

	//����
	DX9::SPRITE time;
	DX9::SPRITE time_number;

	float time_one_digit;
	int time_two_digit;

	const int TIME_NUM_WIDTH = 56;
	const int TIME_NUM_HIGHT = 70;

	const float TIME_POS_X = 1160.0f;
	const float TIME_POS_Y = 20.0f;

	const float ONE_DIGIT_POS_X = TIME_POS_X + 40;
	const float TWO_DIGIT_POS_X = TIME_POS_X - 10;

	const float TIME_NUM_POS_Y = TIME_POS_Y + 40.0f;

	DX12::CAMERA camera;
};