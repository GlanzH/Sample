#include "MyClass/UIManager/UIManager.h"

void UIManager::LoadAsset() {
	volt_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/ui_empty.png");
	volt_max   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/ui_max.png"  );
	sword_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/empty_sword.png");
	sword_max	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/sword.png"	  );
}

void UIManager::Render(float voltage) {
	DX9::SpriteBatch->DrawSimple(volt_empty.Get(), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	DX9::SpriteBatch->DrawSimple(volt_max.Get(), SimpleMath::Vector3(0.0f, 0.0f, 0.0f), RectWH(0, 0, (int)voltage, 86));
	DX9::SpriteBatch->DrawSimple(volt_empty.Get(), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	DX9::SpriteBatch->DrawSimple(sword_max.Get(), SimpleMath::Vector3(0.0f, 0.0f, 0.0f), RectWH(95, 0, (int)32.4, 124));
}