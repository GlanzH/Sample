#pragma once
#include "Base/pch.h"
#include <DirectXTK9.h>
#include <Base/dxtk.h>

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

	void ResetAnimeFrame();

private:
	void Animation(const float deltaTime);


	//スコア(観客)
	DX9::SPRITE score_good_empty;
	DX9::SPRITE score_good_max;
	DX9::SPRITE score_bad_empty;
	DX9::SPRITE score_bad_max;
	int score_width;

	const int SCORE_MAX_HIGHT = 119;
	const int SCORE_MIN_WIDTH = 101;
	const float SCORE_POS_X = 79.0f;
	const float SCORE_POS_Y = 58.0f;
	const float SCORE_EMPTY_POS_Z = -99.0f;
	const float SCORE_MAX_POS_Z = -100.0f;


	//撃破コンボ
	DX9::SPRITE combo_base;	//吹き出しの部分
	DX9::SPRITE combo_gauge;	//コンボのゲージ

	int combo_anime;
	int combo_gauge_width;
	float combo_anime_frame;	//アニメーション使用変数

	const int COMBO_BASE_WIDTH = 331;
	const int COMBO_BASE_HIGHT = 232;
	const int COMBO_GAUGE_HIGHT = 5;

	const float COMBO_BASE_POS_X = 950.0f;
	const float COMBO_BASE_POS_Y = 500.0f;

	const float COMBO_GAUGE_POS_X = COMBO_BASE_POS_X + 80.0f;
	const float COMBO_GAUGE_POS_Y = COMBO_BASE_POS_Y + 130.0f;
	const float COMBO_GAUGE_DIVIDE = 34.2f;	//コンボゲージ5分の1の数(描画時使用)

	//時間
	DX9::SPRITE time;
	const float TIME_POS_X = 1160.0f;
	const float TIME_POS_Y = 20.0f;
};