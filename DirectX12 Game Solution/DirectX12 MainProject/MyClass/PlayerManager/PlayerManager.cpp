#include "Base/pch.h"
#include "Base/dxtk.h"
#include "PlayerManager.h"

void PlayerManager::Initialize() {



}

void PlayerManager::LoadAssets() 
{

	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Mikoto//mikoto.x");
	model->SetScale(0.005f);
}

void PlayerManager::Update(const float deltaTime) {

	//プレイヤーの移動
	if (DXTK->KeyState->Right) {
		model->Move(10.0f * deltaTime, 0.0f, 0.0f);
	}
	if (DXTK->KeyState->Left) {
		model->Move(-10.0f * deltaTime, 0.0f, 0.0f);
	}
}

void PlayerManager::Render() {
	//プレイヤーの描画
	model->Draw();
}