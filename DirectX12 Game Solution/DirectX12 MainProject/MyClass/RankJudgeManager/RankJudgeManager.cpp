#include "MyClass/RankJudgeManager/RankJudgeManager.h"

void RankJudgeManager::Initialize() {
	//ランク
	score = 0;
	now_rank = 0;
	rank_alpha = 225.0f;
	rank_hight = 0;
	rank_width = 0;

	//スコア
	score_width = 0.0f;
	score_alpha = 0.0f;

	//リザルトタイトル
	title_alpha = 0.0f;
	title_anim_frame = 0.0f;
	title_hight = 0.0f;

	//リザルト帯
	shadow_alpha = 0.0f;

	//お金
	money = 0;
	digit_state = ONE_DIGIT;
	one_digit = 0;
	two_digit = 0;
	three_digit = 0;
	four_digit = 0;
	digit_pos = 0;
	yen_icon_alpha = 0.0f;
	money_alpha = 0.0f;
	money_pos = SimpleMath::Vector2(MONEY_START_POS_X, 280.0f);
	yen_icon_pos = SimpleMath::Vector2(YEN_ICON_START_POS_X, 280.0f);
	//リスタート
	restart_hight = -1.0f;

	//時間
	time_delta  = 0.0f;
	stop_time	= 0.0f;

	scene_flag = false;

	co_result = ReleaseRank();        // コルーチンの生成
	co_result_it = co_result.begin(); // コルーチンの実行開始
}

void RankJudgeManager::LoadAseet() {
	rank[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Rank/Rank_E.png");
	rank[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Rank/Rank_D.png");
	rank[2] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Rank/Rank_C.png");
	rank[3] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Rank/Rank_B.png");
	rank[4] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Rank/Rank_A.png");
	rank[5] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Rank/Rank_S.png");

	score_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Score/scoreui_coin_bottom.png");
	score_max = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Score/scoreui_coin_top.png");

	result_title = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Result_Title.png");

	result_shadow = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Result_Shadow.png");

	restart = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Result/Restart_Text.png");

	font = DX9::SpriteFont::CreateFromFontFile(DXTK->Device9, L"Scene/Result/ronde_square/Ronde-B_square.otf", L"ロンド B スクエア", 55);
}

void RankJudgeManager::Update(const float deltaTime) {
	time_delta = deltaTime;

	if (co_result_it != co_result.end()) {
		co_result_it++;
	}

	if (co_result_it != co_result.end()) {
		co_result.begin();
	}
}

void RankJudgeManager::Render() {
	//リザルトタイトル
	DX9::SpriteBatch->DrawSimple(
		result_title.Get(),
		SimpleMath::Vector3(359.0f, 121.0f, -1.0f),
		RectWH(0, TITLE_MIN_HIGHT * (int)title_anim_frame, TITLE_WIDTH, TITLE_MIN_HIGHT),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, (int)title_alpha)
	);

	//リザルト帯
	DX9::SpriteBatch->DrawSimple(
		result_shadow.Get(),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, (int)shadow_alpha)
	);

	//スコアゲージ
	DX9::SpriteBatch->DrawSimple(
		score_empty.Get(),
		SimpleMath::Vector3(205.0f, 343.0f, SCORE_EMPTY_POS_Z),
		Rect(0, 0, 422, 96),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, (int)score_alpha)
	);

	DX9::SpriteBatch->DrawSimple(
		score_max.Get(),
		SimpleMath::Vector3(205.0f, 343.0f, SCORE_MAX_POS_Z),
		Rect(0, 0, SCORE_MIN_WIDTH + (int)score_width, SCORE_MAX_HIGHT),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, (int)score_alpha)
	);

	//ランク
	DX9::SpriteBatch->DrawSimple(rank[now_rank].Get(),
		SimpleMath::Vector3(637.0f, 253.0f, 0.0f),
		RectWH(300 * rank_width, 250 * (int)rank_hight, 300, 250),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, (int)rank_alpha)
	);

	//リスタート
	DX9::SpriteBatch->DrawSimple(
		restart.Get(),
		SimpleMath::Vector3(455.0f, 590.0f, 0.0f),
		RectWH(0, (int)restart_hight * RESTART_MIN_HIGHT, RESTART_WIDTH, RESTART_MIN_HIGHT)
	);


	//お金アイコン
	DX9::SpriteBatch->DrawString(font.Get(), yen_icon_pos, DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, yen_icon_alpha), L"￥");

	//金額
	DX9::SpriteBatch->DrawString(font.Get(), money_pos, DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, money_alpha), L"%d", money);
}

void RankJudgeManager::JudgeRnak() {
	score = StatusManager::Instance().GetScore();
	//スコアに応じたランク付け
	switch (score / 500)
	{
	case 0:
		//スコア 0～499
		now_rank = E;
		break;

	case 1:
		//500～999
		now_rank = D;
		break;

	case 2:
		//1000～1499
		now_rank = C;
		break;

	case 3:
		//1500～1999
		now_rank = B;
		break;

	case 4:
	case 5:
		//2000～299
		now_rank = A;
		break;

	default:
		//3000以上
		now_rank = S;
		break;
	}
	return;
}

cppcoro::generator<int> RankJudgeManager::ReleaseRank()
{
	co_yield 0;

	while (stop_time < 2.0f) {
		stop_time += time_delta;
		co_yield 1;
	}
	stop_time = 0.0f;

	//帯の表示、タイトルアニメーション
	while (shadow_alpha < 200.0f) {
		shadow_alpha = std::min(shadow_alpha + 330.0f * time_delta, 200.0f);
		//title_anim_frame = std::min(title_anim_frame + 15.0f * time_delta, 16.0f);
		co_yield 1;
	}

	title_alpha = COLOR_MAX;
	while (title_anim_frame < 16.0f) {
		title_anim_frame = std::min(title_anim_frame + 15.0f * time_delta, 16.0f);
		co_yield 1;
	}
	title_anim_frame = 16.0f;

	while (stop_time < 1.0f) {
		stop_time += time_delta;
		co_yield 1;
	}
	stop_time = 0.0f;


	//score_alpha = COLOR_MAX;
	//スコアゲージ表示
	while (score_alpha < COLOR_MAX) {
		score_alpha = std::min(score_alpha + 350.0f * time_delta, COLOR_MAX);
		co_yield 3;
	}

	while (stop_time < 1.0f) {
		stop_time += time_delta;
		co_yield 1;
	}
	stop_time = 0.0f;


	//ゲージ増加
	JudgeRnak();
	while (true) {
		score_width += 70.0f * time_delta;
		if (score_width > score * 0.113f) {
			score_width = score * 0.113f;
			break;
		}
		co_yield 4;
	}

	//お金表示
	yen_icon_alpha = COLOR_MAX;
	money_alpha = COLOR_MAX;
	while (stop_time < 2.0f) {
		stop_time += time_delta;
		co_yield 1;
	}
	stop_time = 0.0f;


	//金額増加
	while (true) {
		money += 700 * time_delta;
		if (money > score) {
			money = score;
			break;
		}

		money_pos.x = MONEY_START_POS_X - (40.0f * digit_pos);
		yen_icon_pos.x = YEN_ICON_START_POS_X - (40.0f * digit_pos);

		//桁数によって座標をずらす
		if (money >= 10 && money < 100) {	//2桁
			digit_pos = 1;
		}

		if (money >= 100 && money < 1000) {	//3桁
			digit_pos = 2;
		}

		if (money >= 1000) {	//4桁
			digit_pos = 3;
		}
		co_yield 5;
	}

	while (stop_time < 1.5f) {
		stop_time += time_delta;
		co_yield 1;
	}
	stop_time = 0.0f;

	//ランクの表示
	while (true) {
		rank_hight += 20.0f * time_delta;
		if (rank_hight >= 13.0f) {
			rank_hight = 0.0f;
			rank_width++;
		}

		if (rank_width >= 2) {
			break;
		}
		co_yield 5;
	}
	rank_hight = 12;
	rank_width = 1;


	scene_flag = true;
	//リスタート
	while (true) {
		restart_hight += 15.0f * time_delta;
		if (restart_hight > 27.0f) {
			restart_hight = 0.0f;
		}
		co_yield 6;
	}

	co_return;
}