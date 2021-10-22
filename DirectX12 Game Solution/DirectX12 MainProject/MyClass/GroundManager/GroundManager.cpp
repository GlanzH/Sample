#include "Base/pch.h"
#include "Base/dxtk.h"
#include "GroundManager.h"

bool GroundManager::Initialize() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground\\ground.x");
	model->SetPosition(0,0,0);
	return true;
}

int GroundManager::Update() {
	return 0;
}

void GroundManager::Render() {
	model->Draw();
}
