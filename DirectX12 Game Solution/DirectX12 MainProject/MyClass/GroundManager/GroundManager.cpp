#include "GroundManager.h"

void GroundManager::LoadAsset() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"bg_forest\\bg_forest.X");	
	model->SetPosition(0.0f, pos_y, 10.0f);
}

void GroundManager::Render() {
	model->Draw();
}
