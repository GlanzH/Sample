#include "Base/pch.h"
#include "Base/dxtk.h"
#include "PlayerManager.h"

bool PlayerManager::Initialize() 
{
	return true;
}

void PlayerManager::LoadAssets() 
{

	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Mikoto//mikoto.x");
	model->SetScale(0.04f);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, XMConvertToRadians(-90.0f), 0.0f);

}

int PlayerManager::Update(const float deltaTime) 
{
	//プレイヤー:移動
	if (DXTK->KeyState->Right||DXTK->KeyState->D) {
		model->Move(0.0f, 0.0f, -10.0f * deltaTime);
	}
	if (DXTK->KeyState->Left||DXTK->KeyState->A) {
		model->Move(0.0f, 0.0f, 10.0f * deltaTime);
	}

	//プレイヤー:ジャンプ
	if (DXTK->KeyEvent->pressed.Space)
		jump_flag = true;

	if (jump_flag == true)
		player_pos.y = 10000.0f * time - (0.5f * gravity * time * time);

	//プレイヤー:攻撃
	if (DXTK->KeyEvent->pressed.L) {

	}

	//ランバージャック




	return 0;
}

void PlayerManager::Render() 
{
	//プレイヤーの描画
	model->Draw();
}