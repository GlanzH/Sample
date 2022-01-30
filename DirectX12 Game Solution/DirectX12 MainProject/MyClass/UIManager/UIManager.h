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

	void ResetAnimeFrame();	//アニメーション再生をリセット
	void SetAddScore(int add_size);
	void PlayUIEffect();
	void PlayCracker();
	void SetUICamera(DX9::CAMERA* camera) { ui_camaera = camera; }
	void SetAudienceState(int state);
private:
	void Animation(const float deltaTime);


	//スコア
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


	//撃破コンボ
	DX9::SPRITE combo_base;	//吹き出しの部分
	DX9::SPRITE combo_gauge;	//コンボのゲージ
	DX9::SPRITE combo;	//コンボ文字
	DX9::SPRITE combo_number;	//コンボ数
	EFFECT cracker_effect;	//クラッカー

	int combo_anime;
	int combo_gauge_width;
	int combo_one_digit;
	int combo_two_digit;
	int combo_num;
	float combo_anime_frame;	//アニメーション使用変数

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
	const float COMBO_GAUGE_DIVIDE = 24.4f;	//コンボゲージ7分の1の数(描画時使用)

	//コンボ(文字)
	const float COMBO_POS_X = COMBO_BASE_POS_X + 140.0f;
	const float COMBO_POS_Y = COMBO_BASE_POS_Y + 100.0f;

	const float COMBO_ONE_DIGIT_X = COMBO_POS_X - 50.0f;
	const float COMBO_ONE_DIGIT_Y = COMBO_POS_Y - 30.0f;

	const float COMBO_TWO_DIGIT_X = COMBO_POS_X - 90.0f;
	const float COMBO_TWO_DIGIT_Y = COMBO_POS_Y - 30.0f;


	//敵残り数
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

	//観客
	DX9::SPRITE audience_normal;
	DX9::SPRITE audience_hard;
	DX9::SPRITE audience_very_hard;
	DX9::SPRITE rev_audience_normal;
	DX9::SPRITE rev_audience_hard;
	DX9::SPRITE rev_audience_very_hard;

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


	//2Dカメラ
	DX12::CAMERA camera;
	DX9::CAMERA* ui_camaera;
};