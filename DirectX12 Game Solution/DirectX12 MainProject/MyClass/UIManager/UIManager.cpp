#include "MyClass/UIManager/UIManager.h"

void UIManager::LoadAsset() {
	audience_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/score_empty.png");
	audience_max   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/score_gauge.png");
	heart_empty	   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/sword3.png"	 );
	heart_max	   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/sword_gauge.png");
}

void UIManager::Render(float audience, float parry) {
	DX9::SpriteBatch->DrawSimple(
		audience_empty.Get(),
		SimpleMath::Vector3(AUDIENCE_UI_POS_X, AUDIENCE_UI_POS_Y, AUDIENCE_EMPTY_UI_POS_Z)
	);
	DX9::SpriteBatch->DrawSimple(
		audience_max.Get(),
		SimpleMath::Vector3(AUDIENCE_UI_POS_X, AUDIENCE_UI_POS_Y, AUDIENCE_MAX_UI_POS_Z),
		RectWH(0, 0, AUDIENCE_MIN_WIDTH + (int)audience, AUDIENCE_MAX_HIGH)
	);

	DX9::SpriteBatch->DrawSimple(
		heart_empty.Get(),
		SimpleMath::Vector3(HEART_UI_POS_X, HEART_UI_POS_Y, 1.0f)
	);
	DX9::SpriteBatch->DrawSimple(
		heart_max.Get(),
		SimpleMath::Vector3(HEART_UI_POS_X, HEART_UI_POS_Y, 0.0f),
		RectWH(0, 0, HEART_MAX_WIDTH, HEART_MAX_HIGH - parry)
	);
}