#include "SwordManager.h"

void SwordManager::LoadAssets()
{
	sword_model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"negi\\negi.X");
	sword_model_->SetTexture(L"negi\\negiii.png");
	sword_model_->SetPosition(sword_pos);
	sword_model_->SetScale(3.0f);
	sword_model_->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);
}

int SwordManager::Update(const float deltaTime)
{
	return 0;
}

void SwordManager::Render()
{
	sword_model_->Draw();
}