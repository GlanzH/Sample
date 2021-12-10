#include "GroundManager.h"

void GroundManager::LoadAsset() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\background.X");	
	model->SetPosition(0.0f, pos_y, 20.0f);
}

void GroundManager::Render() {
	model->Draw();
}
