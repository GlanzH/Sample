#include "MyClass/RankJudgeManager/RankJudgeManager.h"

void RankJudgeManager::Initialize() {
	//ランク
	rank_pos   = SimpleMath::Vector3(0.0f, -40.0f, 0.0f);
	rank_alpha = 0.0f;

	//フォント
	font_pos = SimpleMath::Vector2(/*500.0f*/680.0f, 130.0f);

	//人数
	people_pos = SimpleMath::Vector3(0.0f, 0.0f, -10.0f);
	people	   = 0;

	//吹き出し
	text_box_pos   = SimpleMath::Vector3(-50.0f, 0.0f, 0.0f);
	text_box_alpha = 0.0f;

	//コメント
	text_pos	  = SimpleMath::Vector3(0.0f, 40.0f, 0.0f);
	text_alpha = 0.0f;

	//時間
	time_delta  = 0.0f;
	stop_time	= 0.0f;

	scene_flag = false;

	co_result = ReleaseRank();        // コルーチンの生成
	co_result_it = co_result.begin(); // コルーチンの実行開始
}

void RankJudgeManager::LoadAseet() {
	rank_s = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_s.png");
	rank_a = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_a.png");
	rank_b = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_b.png");
	rank_c = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_c.png");
	rank_d = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_d.png");
	rank_e = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_e.png");

	font = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"ＭＳ ゴシック", font_size);

	people_ui = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/people_ui.png");

	director = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/directed_ui.png");

	text_box = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/speech_bubble_ui.png");

	text = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/letter_ui.png");
}

void RankJudgeManager::Update(const float deltaTime) {
	GetAudience();
	JudgeRnak();
	time_delta = deltaTime;


	if (co_result_it != co_result.end()) {
		co_result_it++;
	}

	if (co_result_it != co_result.end()) {
		co_result.begin();
	}
}

void RankJudgeManager::Render() {
	DX9::SpriteBatch->DrawSimple(people_ui.Get(), people_pos);

	DX9::SpriteBatch->DrawSimple(director.Get(), director_pos);

	DX9::SpriteBatch->DrawSimple(text_box.Get(), text_box_pos,
		Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, text_box_alpha));

	DX9::SpriteBatch->DrawSimple(text.Get(), text_pos,
		Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, text_alpha));


	switch (now_rank)
	{
	case E:
		DX9::SpriteBatch->DrawSimple(rank_e.Get(), rank_pos,
			Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT), DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, rank_alpha));
		break;

	case D:
		DX9::SpriteBatch->DrawSimple(rank_d.Get(), rank_pos,
			Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT), DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, rank_alpha));
		break;

	case C:
		DX9::SpriteBatch->DrawSimple(rank_c.Get(), rank_pos,
			Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT), DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, rank_alpha));
		break;

	case B:
		DX9::SpriteBatch->DrawSimple(rank_b.Get(), rank_pos,
			Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT), DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, rank_alpha));
		break;

	case A:
		DX9::SpriteBatch->DrawSimple(rank_a.Get(), rank_pos,
			Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT), DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, rank_alpha));
		break;

	case S:
		DX9::SpriteBatch->DrawSimple(rank_s.Get(), rank_pos,
			Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT), DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, rank_alpha));
		break;

	default:
		break;
	}

	DX9::SpriteBatch->DrawString(font.Get(), font_pos, DX9::Colors::White, L"%d", people); 
}

void RankJudgeManager::GetAudience() {
	now_score = StatusManager::Instance().ReturnScore();
}

void RankJudgeManager::JudgeRnak() {
	if (now_score <= 0.0f) {
		now_rank = E;
	}
	else if (now_score >= 1.0f	&& now_score <= 29.0f) {
		now_rank = D;
	}
	else if (now_score >= 30.0f && now_score <= 59.0f) {
		now_rank = C;
	}
	else if (now_score >= 60.0f && now_score <= 89.0f) {
		now_rank = B;
	}
	else if (now_score >= 90.0f && now_score <= 99.0f) {
		now_rank = A;
	}
	else if (now_score >= 100.0f) {
		now_rank = S;
	}

	return;
}

cppcoro::generator<int> RankJudgeManager::ReleaseRank()
{
	co_yield 0;

	//観客人数の表示
	while (people < now_score * 3) {
		people += 100 * time_delta;
		if (people >= 10 && people < 100) {//桁が増えると座標移動
			font_pos.x = 590.0f;
		}
		else if (people >= 100) {
			font_pos.x = 500.0f;
		}
		co_yield 1;
	}
	people = now_score * 3;

	//間
	while (stop_time < 1.0f) {
		stop_time += time_delta;
		co_yield 2;
	}
	stop_time = 0.0f;

	//ランク表示
	while (stop_time < 2.0f) {
		rank_alpha = std::min(rank_alpha + 700.0f * time_delta, COLOR_MAX);
		//rank_alpha = 255.0f;
		rank_pos.y += 100.0f * time_delta;
		if (rank_pos.y > 0.0f) {
			rank_pos.y = 0.0f;
		}
		stop_time += time_delta;
		co_yield 3;
	}
	stop_time = 0.0f;

	//監督の吹き出し表示
	while (stop_time < 2.0f) {
		text_box_alpha = std::min(text_box_alpha + 700.0f * time_delta, COLOR_MAX);
		text_box_pos.x += 100.0f * time_delta;
		if (text_box_pos.x > 0.0f) {
			text_box_pos.x = 0.0f;
		}
		stop_time += time_delta;
		co_yield 4;
	}
	stop_time = 0.0f;

	//コメントの表示
	while (stop_time < 2.0f) {
		text_alpha = std::min(text_alpha + 700.0f * time_delta, COLOR_MAX);
		text_pos.y -= 100.0f * time_delta;
		if (text_pos.y < 0.0f) {
			text_pos.y = 0.0f;
		}
		stop_time += time_delta;
		co_yield 5;
	}
	stop_time = 0.0f;
	scene_flag = true;
	co_return;
}