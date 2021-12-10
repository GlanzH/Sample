#include "MyClass/GameSceneManager/SceneManager.h"

void SceneManager::Initialize() {
	curtain_pos = SimpleMath::Vector3(0.0f, CURTAIN_START_POS, 0.0f);
	ending_coro_flag  = false;
	scene_change_flag = false;
}

void SceneManager::LoadAsset() {
	curtain = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/curtain_bright.png");
}

void SceneManager::Update(const float deltaTime) {

	time_delta = deltaTime;

	if (ending_coro_flag == false) {
		co_ending = Ending();        // コルーチンの生成
		co_ending_it = co_ending.begin(); // コルーチンの実行開始

		ending_coro_flag = true;
	}

	if (co_ending_it != co_ending.end()) {
		co_ending_it++;
	}

	if (co_ending_it != co_ending.end()) {
		co_ending.begin();
	}

	return;
}

void SceneManager::Render() {
	DX9::SpriteBatch->DrawSimple(curtain.Get(), curtain_pos);
}

cppcoro::generator<int> SceneManager::Ending() {
	co_yield 0;
	while (curtain_pos.y < 0.0f) {
		curtain_pos.y += CURTAIN_DOWN_SPEED * time_delta;
		co_yield 1;
	}
	curtain_pos.y = 0.0f;
	scene_change_flag = true;

	co_return;
}
