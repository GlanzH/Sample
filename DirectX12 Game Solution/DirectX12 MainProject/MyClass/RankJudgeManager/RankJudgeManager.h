#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "cppcoro/generator.h"
#include "MyClass/StatusManager/StatusManager.h"

using namespace DirectX;

class RankJudgeManager {
public:
	RankJudgeManager() {};
	~RankJudgeManager() {};

	void Initialize();
	void LoadAseet();
	void Update(const float deltaTime);
	void Render();



	void JudgeRnak();

	bool SceneChange() { return scene_flag; }
	
private:

	DX9::SPRITEFONT font;
	//ランク
	DX9::SPRITE rank[6];
	SimpleMath::Vector3 rank_pos;
	float rank_hight;
	int rank_width;
	float rank_alpha;
	int now_rank;
	int score;	//ランク付けに使用

	enum RANK {
		E, D, C, B, A, S
	};

	//スコア
	DX9::SPRITE score_empty;
	DX9::SPRITE score_max;
	float score_width;
	float score_alpha;

	const int SCORE_MAX_HIGHT = 96;
	const int SCORE_MIN_WIDTH = 81;
	const float SCORE_EMPTY_POS_Z = 0.0f;
	const float SCORE_MAX_POS_Z = -1.0f;

	//リザルトタイトル
	DX9::SPRITE result_title;
	float title_alpha;
	float title_anim_frame;
	float title_hight;

	const int TITLE_WIDTH = 550;
	const int TITLE_MIN_HIGHT = 100;

	//リザルト帯
	DX9::SPRITE result_shadow;
	float shadow_alpha;

	//お金
	DX9::SPRITE yen_icon;
	DX9::SPRITE yen_number;

	int money;
	int digit_state;
	int one_digit;
	int two_digit;
	int three_digit;
	int four_digit;

	float yen_alpha;

	SimpleMath::Vector2 money_pos;

	enum DIGIT_STATE
	{
		ONE_DIGIT,
		TWO_DIGIT,
		THREE_DIGIT,
		FOUR_DIGIT
	};

	const int YEN_ICON_WIDTH = 30;
	const int YEN_ICON_HIGHT = 51;
	const int YEN_NUM_WIDTH = 40;
	const int YEN_NUM_HIGHT = 70;
	const float ONE_DIGIT_POS_X	  = 0.0f;
	const float TWO_DIGIT_POS_X	  = ONE_DIGIT_POS_X - 40.0f;
	const float THREE_DIGIT_POS_X = ONE_DIGIT_POS_X - 80.0f;
	const float FOUR_DIGIT_POS_X  = ONE_DIGIT_POS_X - 120.0f;
	const float YEN_NUM_POS_Y = 0.0f;

	//リスタート
	DX9::SPRITE restart;
	float restart_hight;

	const int RESTART_WIDTH = 400;
	const int RESTART_MIN_HIGHT = 40;

	const int SPRITE_HIGHT = 720;	//画像の最大表示高さ
	const int SPRITE_WIDTH = 1280;	//画像の最大表示幅

	const float COLOR_MAX = 255.0f;	//RGBA最大値
	bool scene_flag;	//シーン切り替え可能フラグ

	//時間
	float time_delta;
	float stop_time;
	const float ALPHA_SPEED		  = 700.0f;//アルファ値増加スピード
	const float SPRITE_MOVE_SPEED = 100.0f;//画像の移動スピード

	// コルーチンのプロトタイプ宣言
	//リザルト演出
	cppcoro::generator<int> ReleaseRank();
	cppcoro::generator<int>                  co_result;
	cppcoro::detail::generator_iterator<int> co_result_it;
};