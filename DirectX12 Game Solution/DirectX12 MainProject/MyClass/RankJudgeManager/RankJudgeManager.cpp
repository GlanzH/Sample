#include "MyClass/RankJudgeManager/RankJudgeManager.h"

void RankJudgeManager::Initialize() {
	//ランク
	rank_pos   = SimpleMath::Vector3(0.0f, RANK_START_POS_Y, 0.0f);
	rank_alpha = 0.0f;
	now_score = 0;
	now_rank = 0;

	//フォント
	font_pos = SimpleMath::Vector2(FONT_STSRT_POS_X, FONT_STSRT_POS_Y);

	//人数
	people_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	people	   = 0;

	//吹き出し
	text_box_pos   = SimpleMath::Vector3(TEXTBOX_START_POS_X, 0.0f, 0.0f);
	text_box_alpha = 0.0f;

	//コメント
	text_pos   = SimpleMath::Vector3(0.0f, TEXT_START_POS_Y, 0.0f);
	text_alpha = 0.0f;

	//EXIT
	exit_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	exit_flash = 0;

	//時間
	time_delta  = 0.0f;
	stop_time	= 0.0f;

	scene_flag = false;

	co_result = ReleaseRank();        // コルーチンの生成
	co_result_it = co_result.begin(); // コルーチンの実行開始
}

void RankJudgeManager::LoadAseet() {
	rank[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_e.png");
	rank[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_d.png");
	rank[2] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_c.png");
	rank[3] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_b.png");
	rank[4] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_a.png");
	rank[5] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/rank_s.png");

	font = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"ＭＳ ゴシック", font_size);

	people_ui = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/people_ui.png");

	director = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/directed_ui.png");

	text_box = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/speech_bubble_ui.png");

	text = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/letter_ui.png");

	exit = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/exit.png");
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

	DX9::SpriteBatch->DrawSimple(text_box.Get(),
		text_box_pos,
		Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, text_box_alpha)
	);

	DX9::SpriteBatch->DrawSimple(text.Get(), text_pos,
		Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, text_alpha)
	);

	if (exit_flash % 2 != 0) {
		DX9::SpriteBatch->DrawSimple(exit.Get(), exit_pos);
	}

	DX9::SpriteBatch->DrawSimple(rank[now_rank].Get(),
		rank_pos,
		Rect(0, 0, SPRITE_WIDTH, SPRITE_HIGHT),
		DX9::Colors::RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, rank_alpha)
	);

	DX9::SpriteBatch->DrawString(font.Get(), font_pos, DX9::Colors::White, L"%d", people);
}

void RankJudgeManager::GetAudience() {
	now_score = StatusManager::Instance().GetScore();
}

void RankJudgeManager::JudgeRnak() {
	//スコアに応じたランク付け
	switch (now_score / 500)
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

	//間
	while (stop_time < 1.0f) {
		stop_time += time_delta;
		co_yield 1;
	}
	stop_time = 0.0f;

	//観客人数の表示
	while (people < now_score * multiple) {
		people += 100 * time_delta;
		if (people >= 10 && people < 100) {//桁が増えると座標移動
			font_pos.x = TWO_DIGIT_POS;
		}
		else if (people >= 100) {
			font_pos.x = THREE_DIGIT_POS;
		}
		co_yield 1;
	}
	people = now_score * multiple;

	//間
	while (stop_time < 1.0f) {
		stop_time += time_delta;
		co_yield 2;
	}
	stop_time = 0.0f;

	//ランク表示
	while (stop_time < 2.0f) {
		rank_alpha = std::min(rank_alpha + ALPHA_SPEED * time_delta, COLOR_MAX);
		rank_pos.y += SPRITE_MOVE_SPEED * time_delta;
		if (rank_pos.y > 0.0f) {
			rank_pos.y = 0.0f;
		}
		stop_time += time_delta;
		co_yield 3;
	}
	stop_time = 0.0f;

	//監督の吹き出し表示
	while (stop_time < 2.0f) {
		text_box_alpha = std::min(text_box_alpha + ALPHA_SPEED * time_delta, COLOR_MAX);
		text_box_pos.x += SPRITE_MOVE_SPEED * time_delta;
		if (text_box_pos.x > 0.0f) {
			text_box_pos.x = 0.0f;
		}
		stop_time += time_delta;
		co_yield 4;
	}
	stop_time = 0.0f;

	//コメントの表示
	while (stop_time < 2.0f) {
		text_alpha = std::min(text_alpha + ALPHA_SPEED * time_delta, COLOR_MAX);
		text_pos.y -= SPRITE_MOVE_SPEED * time_delta;
		if (text_pos.y < 0.0f) {
			text_pos.y = 0.0f;
		}
		stop_time += time_delta;
		co_yield 5;
	}
	stop_time = 0.0f;
	scene_flag = true;

	while (true) {
		exit_flash += FLASH_SPEED * time_delta;
		if (exit_flash > FLASH_MAX) {
			exit_flash = 0;
		}
		co_yield 6;
	}

	co_return;
}