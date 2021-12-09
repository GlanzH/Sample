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
	DX9::SPRITE rank_s;
	DX9::SPRITE rank_a;
	DX9::SPRITE rank_b;
	DX9::SPRITE rank_c;
	DX9::SPRITE rank_d;
	DX9::SPRITE rank_e;
	SimpleMath::Vector3 rank_pos;

	float rank_alpha;
	int now_rank;
	float now_score;	//ランク付けに使用

	enum RANK {
		E, D, C, B, A, S
	};

	//フォント
	DX9::SPRITEFONT font;
	SimpleMath::Vector2 font_pos;
	const int font_size = 100;

	//人数
	DX9::SPRITE	people_ui;
	SimpleMath::Vector3 people_pos;
	int people;

	//監督
	DX9::SPRITE director;
	SimpleMath::Vector3 director_pos;

	//吹き出し
	DX9::SPRITE text_box;
	SimpleMath::Vector3 text_box_pos;
	float text_box_alpha;

	//コメント
	DX9::SPRITE text;
	SimpleMath::Vector3 text_pos;
	float text_alpha;

	const int SPRITE_HIGHT = 720;	//画像の最大表示高さ
	const int SPRITE_WIDTH = 1280;	//画像の最大表示幅

	const float COLOR_MAX = 255.0f;	//RGBA最大値
	bool scene_flag;

	//時間
	float time_delta;
	float stop_time;

	// コルーチンのプロトタイプ宣言
	cppcoro::generator<int> ReleaseRank();
	cppcoro::generator<int>                  co_result;
	cppcoro::detail::generator_iterator<int> co_result_it;
};