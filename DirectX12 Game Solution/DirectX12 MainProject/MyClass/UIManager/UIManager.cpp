#include "MyClass/UIManager/UIManager.h"
#include "MyClass/StatusManager/StatusManager.h"

void UIManager::Initialize() {
	score_width = 0.0;
	combo_anime = 0.0f;
	combo_gauge_width = 0.0f;
}

void UIManager::LoadAsset() {
	score_good_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/scoreui_nice_bottom.png");
	score_good_max   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/scoreui_nice_top.png"   );
	score_bad_empty	 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/scoreui_bad_bottom.png");
	score_bad_max	 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/scoreui_bad_top.png"	  );

	combo_base = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Combo_Anim.png");
	combo_gauge = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/combo_gauge.png");

	time = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/TIME.png");
}

void UIManager::Update(const float deltaTime) {
	Animation(deltaTime);
	score_width = SCORE_MIN_WIDTH + (int)StatusManager::Instance().GetScoreGauge();
	combo_anime = COMBO_BASE_HIGHT * (int)combo_anime_frame;
	combo_gauge_width = COMBO_GAUGE_DIVIDE * StatusManager::Instance().GetKillComboTime();
}

void UIManager::Render() {
	//�X�R�A�Q�[�W
	if (StatusManager::Instance().GetGoodFlag()) {
		DX9::SpriteBatch->DrawSimple(
			score_good_empty.Get(),
			SimpleMath::Vector3(SCORE_POS_X, SCORE_POS_Y, SCORE_EMPTY_POS_Z)
		);
		DX9::SpriteBatch->DrawSimple(
			score_good_max.Get(),
			SimpleMath::Vector3(SCORE_POS_X, SCORE_POS_Y, SCORE_MAX_POS_Z),
			RectWH(0, 0, score_width, SCORE_MAX_HIGHT)
		);
	}
	else {
		DX9::SpriteBatch->DrawSimple(
			score_bad_empty.Get(),
			SimpleMath::Vector3(SCORE_POS_X, SCORE_POS_Y, SCORE_EMPTY_POS_Z)
		);
		DX9::SpriteBatch->DrawSimple(
			score_bad_max.Get(),
			SimpleMath::Vector3(SCORE_POS_X, SCORE_POS_Y, SCORE_MAX_POS_Z),
			RectWH(0, 0, score_width, SCORE_MAX_HIGHT)
		);
	}

	if (StatusManager::Instance().GetKillFlag()) {
		//�R���{�����o��
		DX9::SpriteBatch->DrawSimple(
			combo_base.Get(),
			SimpleMath::Vector3(COMBO_BASE_POS_X, COMBO_BASE_POS_Y, 0.0f),
			RectWH(0, combo_anime, COMBO_BASE_WIDTH, COMBO_BASE_HIGHT)
		);

		//�R���{�Q�[�W
		DX9::SpriteBatch->DrawSimple(
			combo_gauge.Get(),
			SimpleMath::Vector3(COMBO_GAUGE_POS_X, COMBO_GAUGE_POS_Y, 0.0f),
			RectWH(0, 0, combo_gauge_width, COMBO_GAUGE_HIGHT)
		);
	}

	//����
	DX9::SpriteBatch->DrawSimple(
		time.Get(),
		SimpleMath::Vector3(TIME_POS_X, TIME_POS_Y, 0.0f)
	);
}

void UIManager::Animation(const float deltaTime) {
	if (StatusManager::Instance().GetAnimeFlag()) {
		combo_anime_frame += 10.0f * deltaTime;
	}
	else {
		ResetAnimeFrame();
	}

	if (combo_anime_frame > 9.0f) {
		StatusManager::Instance().ResetaAnimeFlag();
		ResetAnimeFrame();
	}

	return;
}

void UIManager::ResetAnimeFrame() {
	combo_anime_frame = 0.0f;
	return;
}