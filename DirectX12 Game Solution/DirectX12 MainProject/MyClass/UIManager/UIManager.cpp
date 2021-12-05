#include "MyClass/UIManager/UIManager.h"

void UIManager::LoadAsset() {
	audience_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/audience_ui_empty.png");
	audience_max   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/audience_ui_max.png"  );
	heart_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/heart_empty.png");
	heart_max	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/heart_max.png"  );

	rank_s = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/rank_s.png");
	rank_a = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/rank_a.png");
	rank_b = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/rank_b.png");
	rank_c = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/rank_c.png");
	rank_d = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/rank_d.png");
	rank_e = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/rank_e.png");

}

int UIManager::Update(const float deltaTime){

	return 0;
}

void UIManager::Render(float audience, float parry) {
	DX9::SpriteBatch->DrawSimple(
		audience_empty.Get(),
		SimpleMath::Vector3(AUDIENCE_UI_POS_X, AUDIENCE_UI_POS_y, 1.0f)
	);
	DX9::SpriteBatch->DrawSimple(
		audience_max.Get(),
		SimpleMath::Vector3(AUDIENCE_UI_POS_X + 44.0f, AUDIENCE_UI_POS_y, 0.0f),
		RectWH(0, 0, (int)audience, AUDIENCE_MAX_HIGH)
	);

	DX9::SpriteBatch->DrawSimple(
		heart_empty.Get(),
		SimpleMath::Vector3(HEART_UI_POS_X, HEART_UI_POS_Y, 0.0f),
		RectWH(0, 0, HEART_MAX_WIDTH, 91 + (int)-4.55 * parry)
	);
	DX9::SpriteBatch->DrawSimple(
		heart_max.Get(),
		SimpleMath::Vector3(HEART_UI_POS_X, HEART_UI_POS_Y , 1.0f)
	);
}

void UIManager::RankRnder(int rank) {
	switch (rank)
	{
	case 0:
		DX9::SpriteBatch->DrawSimple(rank_e.Get(),SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		break;

	case 1:
		DX9::SpriteBatch->DrawSimple(rank_d.Get(),SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		break;

	case 2:
		DX9::SpriteBatch->DrawSimple(rank_c.Get(),SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		break;

	case 3:
		DX9::SpriteBatch->DrawSimple(rank_b.Get(),SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		break;

	case 4:
		DX9::SpriteBatch->DrawSimple(rank_a.Get(),SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		break;

	case 5:
		DX9::SpriteBatch->DrawSimple(rank_s.Get(),SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
		break;

	default:
		break;
	}
}