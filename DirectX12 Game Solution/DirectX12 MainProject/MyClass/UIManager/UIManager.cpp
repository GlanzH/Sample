#include "MyClass/UIManager/UIManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/ResourceManager/ResourceManager.h"

void UIManager::Initialize() {
	score_width = 0.0;
	combo_anime = 0.0f;
	combo_gauge_width = 0.0f;
	combo_num = 0;
	combo_one_digit = 0;
	combo_two_digit = 0;
	combo_digit_up_flag = false;

	effect_play_flag = false;
	effect_handle = 0;

	DX12Effect2D.Initialize();

	camera.SetView(SimpleMath::Vector3(0.0f, 13.0f, -20.0f),SimpleMath::Vector3::Zero);
	camera.SetPerspectiveFieldOfView(XMConvertToRadians(40.0f), 16.0f / 9.0f, 1.0f, 10000.0f);
	

	DX12Effect2D.SetCamera(&camera);

}

void UIManager::LoadAsset() {
	score_good_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/scoreui_nice_bottom.png");
	score_good_max   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/scoreui_nice_top.png"   );
	score_bad_empty	 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/scoreui_bad_bottom.png");
	score_bad_max	 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/scoreui_bad_top.png"	  );

	combo_base = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Combo_Anim.png");
	combo_gauge = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/combo_gauge.png");
	combo = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/COMBO.png");
	combo_number = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/numbers_combo_h.png");

	good_effect = DX12Effect2D.Create(L"Effect\\UIEffect\\nice\\nice.efk", "nice");
	bad_effect  = DX12Effect2D.Create(L"Effect\\UIEffect\\bad\\bad.efk", "bad");
}

void UIManager::Update(const float deltaTime) {
	Animation(deltaTime);
	DX12Effect2D.Update(deltaTime);
	combo_num = StatusManager::Instance().GetCombo();
	score_width = SCORE_MIN_WIDTH + (int)StatusManager::Instance().GetScoreGauge();
	combo_anime = COMBO_BASE_HIGHT * (int)combo_anime_frame;
	combo_gauge_width = COMBO_GAUGE_DIVIDE * StatusManager::Instance().GetKillComboTime();
	if (combo_num <= 9.0f) {
		combo_digit_up_flag = false;
	}
	else {
		combo_digit_up_flag = true;
	}

	if (!combo_digit_up_flag) {
		combo_one_digit = COMBO_NUM_WIDTH * combo_num;
	}
	else {
		combo_one_digit = COMBO_NUM_WIDTH * (combo_num % 10);
		combo_two_digit = COMBO_NUM_WIDTH * (combo_num / 10);
	}

	if (effect_play_flag) {
		if (StatusManager::Instance().GetGoodFlag()) {
			effect_handle = DX12Effect2D.Play(good_effect, Vector3(0.0f, 0.0f, 0.0f));
		}
		else {
			effect_handle = DX12Effect2D.Play(bad_effect, Vector3(0.0f, 0.0f, 0.0f));
		}
		effect_play_flag = false;
	}
	DX12Effect2D.SetPosition(effect_handle, Vector3(-30.0f, 27.0f, 40.0f));

}

void UIManager::Render() {
	//スコアゲージ
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

	if (StatusManager::Instance().GetComboFlag()) {
		//コンボ吹き出し
		DX9::SpriteBatch->DrawSimple(
			combo_base.Get(),
			SimpleMath::Vector3(COMBO_BASE_POS_X, COMBO_BASE_POS_Y, 0.0f),
			RectWH(0, combo_anime, COMBO_BASE_WIDTH, COMBO_BASE_HIGHT)
		);

		//コンボゲージ
		DX9::SpriteBatch->DrawSimple(
			combo_gauge.Get(),
			SimpleMath::Vector3(COMBO_GAUGE_POS_X, COMBO_GAUGE_POS_Y, 0.0f),
			RectWH(0, 0, combo_gauge_width, COMBO_GAUGE_HIGHT)
		);

		//コンボ文字
		DX9::SpriteBatch->DrawSimple(
			combo.Get(),
			SimpleMath::Vector3(COMBO_POS_X, COMBO_POS_Y, 0.0f)
		);


		//コンボ数(1桁)
		DX9::SpriteBatch->DrawSimple(
			combo_number.Get(),
			SimpleMath::Vector3(COMBO_ONE_DIGIT_X, COMBO_ONE_DIGIT_Y, 0.0f),
			RectWH(combo_one_digit, 0, COMBO_NUM_WIDTH, COMBO_NUM_HIGHT)
		);

		if (combo_digit_up_flag) {
			//コンボ数(2桁)
			DX9::SpriteBatch->DrawSimple(
				combo_number.Get(),
				SimpleMath::Vector3(COMBO_TWO_DIGIT_X, COMBO_TWO_DIGIT_Y, 0.0f),
				RectWH(combo_two_digit, 0, COMBO_NUM_WIDTH, COMBO_NUM_HIGHT)
			);
		}
	}


	//時間
	//DX9::SpriteBatch->DrawSimple(
	//	time.Get(),
	//	SimpleMath::Vector3(TIME_POS_X, TIME_POS_Y, 0.0f)
	//);

	//DX9::SpriteBatch->DrawSimple(
	//	time_number.Get(),
	//	SimpleMath::Vector3(ONE_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
	//	RectWH(((int)time_one_digit % 10) * TIME_NUM_WIDTH, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
	//);

	//DX9::SpriteBatch->DrawSimple(
	//	time_number.Get(),
	//	SimpleMath::Vector3(TWO_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
	//	RectWH(((int)time_one_digit / 10) * TIME_NUM_WIDTH, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
	//);

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

void UIManager::PlayUIEffect() {
	effect_play_flag = true;
}

void UIManager::EfkRender()
{
	DX12Effect2D.SetCameraPosition(&camera);
	DX12Effect2D.Renderer();
}

