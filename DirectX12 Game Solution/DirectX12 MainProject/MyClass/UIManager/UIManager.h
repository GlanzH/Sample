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
	void PlayCracker();
	void SetUICamera(DX9::CAMERA* camera) { ui_camaera = camera; }
	void SetAudienceState(int state);
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
	bool icon_play_flag;

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
	EFFECT cracker_effect;	//�N���b�J�[�G�t�F�N�g
	XAudio::SOUNDEFFECT cracker_se;	//�N���b�J�[SE

	int combo_anime;
	int combo_gauge_width;
	int combo_one_digit;
	int combo_two_digit;
	int combo_num;
	float combo_anime_frame;	//�A�j���[�V�����g�p�ϐ�

	bool combo_digit_up_flag;
	bool cracker_play_flag;

	const int COMBO_BASE_WIDTH = 331;
	const int COMBO_BASE_HIGHT = 232;
	const int COMBO_GAUGE_HIGHT = 5;
	const int COMBO_NUM_HIGHT = 60;
	const int COMBO_NUM_WIDTH = 48;

	const float COMBO_BASE_POS_X = 950.0f;
	const float COMBO_BASE_POS_Y = 500.0f;

	const float COMBO_GAUGE_POS_X = COMBO_BASE_POS_X + 80.0f;
	const float COMBO_GAUGE_POS_Y = COMBO_BASE_POS_Y + 130.0f;
	const float COMBO_GAUGE_DIVIDE = 28.5f;	//�R���{�Q�[�W6����1�̐�(�`�掞�g�p)

	//�R���{(����)
	const float COMBO_POS_X = COMBO_BASE_POS_X + 140.0f;
	const float COMBO_POS_Y = COMBO_BASE_POS_Y + 100.0f;

	const float COMBO_ONE_DIGIT_X = COMBO_POS_X - 50.0f;
	const float COMBO_ONE_DIGIT_Y = COMBO_POS_Y - 30.0f;

	const float COMBO_TWO_DIGIT_X = COMBO_POS_X - 90.0f;
	const float COMBO_TWO_DIGIT_Y = COMBO_POS_Y - 30.0f;


	//�G�c�萔
	DX9::SPRITE enemy;
	DX9::SPRITE enemy_alive;
	DX9::SPRITE enemy_dead;

	int enemy_max_num;
	int enemy_dead_num;
	int enemy_dead_width;
	float enemy_pos_x;
	float enemy_pos_y;

	const float ENEMY_MIN_POS_X = 830.0f;
	const int ENEMY_HIGHT = 42;

	//�ϋq
	DX9::SPRITE audience_normal;
	DX9::SPRITE audience_hard;
	DX9::SPRITE audience_very_hard;
	DX9::SPRITE rev_audience_normal;
	DX9::SPRITE rev_audience_hard;
	DX9::SPRITE rev_audience_very_hard;
	XAudio::SOUNDEFFECT applause;
	XAudio::SOUNDEFFECT excitement;

	int audience_anim;
	int audience_state;
	float state_reset_time;

	SimpleMath::Vector3 audience_pos;
	SimpleMath::Vector3 rev_audience_pos;

	enum AUDIENCE_STATE {
		NORMAL,
		HARD,
		VERY_HARD
	};


	//2D�J����
	DX12::CAMERA camera;
	DX9::CAMERA* ui_camaera;
};