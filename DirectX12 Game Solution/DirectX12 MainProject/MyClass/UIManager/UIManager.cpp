#include "MyClass/UIManager/UIManager.h"

void UIManager::LoadAsset() {
	volt_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/ui_empty.png");
	volt_max   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/ui_max.png"  );
}

void UIManager::Render(float voltage) {
	DX9::SpriteBatch->DrawSimple(volt_empty.Get(), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	DX9::SpriteBatch->DrawSimple(volt_max.Get(), SimpleMath::Vector3(0.0f, 0.0f, 0.0f), RectWH(0, 0, (int)voltage, 86));
}