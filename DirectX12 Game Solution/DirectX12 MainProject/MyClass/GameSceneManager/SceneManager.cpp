#include "MyClass/GameSceneManager/SceneManager.h"
#include "MyClass/StatusManager/StatusManager.h"

void SceneManager::Initialize() {
	curtain_pos = SimpleMath::Vector3(0.0f, CURTAIN_START_POS, 0.0f);
	scene_change_flag = false;
}

void SceneManager::LoadAsset() {
	curtain = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/curtain_bright.png");
}

void SceneManager::Update(const float deltaTime) {

	if (StatusManager::Instance().ReturnAudience() <= 0.0f) {
		curtain_pos.y = std::min(curtain_pos.y + CURTAIN_DOWN_SPEED * deltaTime, 0.0f);
	}
	else {
		curtain_pos.y = std::max(curtain_pos.y - CURTAIN_DOWN_SPEED * deltaTime, CURTAIN_START_POS);
	}


	if (curtain_pos.y >= 0.0f) {
		scene_change_flag = true;
	}

	return;
}

void SceneManager::Render() {
	DX9::SpriteBatch->DrawSimple(curtain.Get(), curtain_pos);
}