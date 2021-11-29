#include "GroundManager.h"

void GroundManager::LoadAsset() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model//Theatre\\background.x");	
	model->SetPosition(0, pos_y, pos_z);
}

void GroundManager::Render() {
	model->Draw();}
