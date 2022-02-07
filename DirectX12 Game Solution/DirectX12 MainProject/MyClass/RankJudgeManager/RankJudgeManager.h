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


	void GetAudience();

	void JudgeRnak();

	bool SceneChange() { return scene_flag; }
	
private:
	//ランク
	DX9::SPRITE rank[6];
	SimpleMath::Vector3 rank_pos;
	const float RANK_START_POS_Y = -40.0f;

	float rank_alpha;
	int now_rank;
	int now_score;	//ランク付けに使用

	enum RANK {
		E, D, C, B, A, S
	};


	//フォント
	DX9::SPRITEFONT font;
	SimpleMath::Vector2 font_pos;
	const int font_size = 100;//フォントサイズ
	const float FONT_STSRT_POS_X = 680.0f;
	const float FONT_STSRT_POS_Y = 130.0f;
	const float TWO_DIGIT_POS	= 590.0f;//観客人数2桁の座標
	const float THREE_DIGIT_POS = 500.0f;//観客人数3桁の座標


	//人数
	DX9::SPRITE	people_ui;
	SimpleMath::Vector3 people_pos;
	int people;
	const int multiple = 3;//観客人数の倍数

	//監督
	DX9::SPRITE director;
	SimpleMath::Vector3 director_pos;

	//吹き出し
	DX9::SPRITE text_box;
	SimpleMath::Vector3 text_box_pos;
	float text_box_alpha;
	const float TEXTBOX_START_POS_X = -50.0f;

	//テキスト
	DX9::SPRITE text;
	SimpleMath::Vector3 text_pos;
	float text_alpha;

	const float TEXT_START_POS_Y = 40.0f;

	//EXIT
	DX9::SPRITE exit;
	SimpleMath::Vector3 exit_pos;
	int exit_flash;
	const int FLASH_MAX = 100;
	const int FLASH_SPEED = 100;

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
	cppcoro::generator<int> ReleaseRank();
	cppcoro::generator<int>                  co_result;
	cppcoro::detail::generator_iterator<int> co_result_it;
};