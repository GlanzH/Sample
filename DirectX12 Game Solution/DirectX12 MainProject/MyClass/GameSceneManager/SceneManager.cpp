#include "MyClass/GameSceneManager/SceneManager.h"
#include "MyClass/StatusManager/StatusManager.h"

void SceneManager::Initialize() {
	curtain_pos = SimpleMath::Vector3(0.0f, CURTAIN_START_POS, -10.0f);
	scene_change_flag = false;
	curtain_move_flag = false;

	black_alpha = 0;
}

void SceneManager::LoadAsset() {
	curtain = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Curtain.png");
	black = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/kuro.png");
}

void SceneManager::Update(const float deltaTime, bool game_clear) {

	if (StatusManager::Instance().GetScoreGauge() <= 0.0f || game_clear) {
		curtain_move_flag = true;
	}

	if (curtain_move_flag) {
		curtain_pos.y = std::min(curtain_pos.y + CURTAIN_DOWN_SPEED * deltaTime, 0.0f);
		black_alpha += 200 * deltaTime;
	}

	if (black_alpha > 255) {
		black_alpha = 255;
	}


	if (curtain_pos.y >= 0.0f) {
		scene_change_flag = true;
	}

	return;
}

void SceneManager::Render() {
	DX9::SpriteBatch->DrawSimple(
		black.Get(),
		SimpleMath::Vector3::Zero,
		RECT(0, 0, 1280, 720),
		DX9::Colors::RGBA(255, 255, 255, black_alpha)
	);

	DX9::SpriteBatch->DrawSimple(curtain.Get(), curtain_pos);
}