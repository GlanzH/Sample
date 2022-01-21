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


	//変数
	//スコア(観客)
	DX9::SPRITE score_good_empty;
	DX9::SPRITE score_good_max;
	DX9::SPRITE score_bad_empty;
	DX9::SPRITE score_bad_max;
	int score_width;

	//撃破コンボ
	DX9::SPRITE combo_base; //吹き出しの部分
	DX9::SPRITE combo_gauge;
	int combo_anime;
	int combo_gauge_width;
	float combo_frame;	//アニメーション使用変数


	//定数
	//スコア(観客)
	const int SCORE_MAX_HIGHT = 119;
	const int SCORE_MIN_WIDTH = 101;
	const float SCORE_POS_X = 79.0f;
	const float SCORE_POS_Y = 58.0f;
	const float SCORE_EMPTY_POS_Z = -99.0f;
	const float SCORE_MAX_POS_Z = -100.0f;

	//撃破コンボ
	const int COMBO_WIDTH = 290;
	const int COMBO_HIGHT = 183;
	const int COMBO_GAUGE_HIGHT = 5;

	const float COMBO_BASE_POS_X = 1000.0f;
	const float COMBO_BASE_POS_Y = 500.0f;

	const float COMBO_GAUGE_POS_X = COMBO_BASE_POS_X + 60.0f;
	const float COMBO_GAUGE_POS_Y = COMBO_BASE_POS_Y + 120.0f;
	const float COMBO_GAUGE_DIVIDE = 34.2f;	//コンボゲージ5分の1の数(描画時使用)

};