#include "GroundManager.h"

void GroundManager::LoadAsset() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground\\ground.x");	
	model->SetPosition(0, 0, pos_z);
	model->SetScale(5,1,5);
}

void GroundManager::Render() {
	model->Draw();
}
