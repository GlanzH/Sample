#include "MyClass/GameSceneManager/SceneManager.h"
#include "MyClass/StatusManager/StatusManager.h"

void SceneManager::Initialize() {
	curtain_pos = SimpleMath::Vector3(0.0f, CURTAIN_START_POS, 0.0f);
	scene_change_flag = false;
	curtain_move_flag = false;
}

void SceneManager::LoadAsset() {
	curtain = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/curtain_bright.png");
}

void SceneManager::Update(const float deltaTime) {

	if (StatusManager::Instance().GetScoreGauge() <= 0.0f) {
		curtain_move_flag = true;
	}

	if (curtain_move_flag) {
		curtain_pos.y = std::min(curtain_pos.y + CURTAIN_DOWN_SPEED * deltaTime, 0.0f);
	}

	if (curtain_pos.y >= 0.0f) {
		scene_change_flag = true;
	}

	return;
}

void SceneManager::Render() {
	DX9::SpriteBatch->DrawSimple(curtain.Get(), curtain_pos);
}