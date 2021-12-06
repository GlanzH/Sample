#include "MyClass/GameSceneManager/SceneManager.h"

void SceneManager::Initialize() {
	curtain_pos = SimpleMath::Vector3(0.0f, -720.0f, 0.0f);
	ending_coro_flag = false;
	scene_change_flag = false;
}

void SceneManager::LoadAsset() {
	curtain = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/curtain.png");
}

NextScene SceneManager::Update(const float deltaTime) {

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

	if (scene_change_flag == true) {
		return NextScene::ResultScene;
	}
	return NextScene::Continue;
}

void SceneManager::Render() {
	DX9::SpriteBatch->DrawSimple(curtain.Get(), curtain_pos);
}

cppcoro::generator<int> SceneManager::Ending() {
	co_yield 0;
	while (curtain_pos.y < 0.0f) {
		curtain_pos.y += 100.0f * time_delta;
		co_yield 1;
	}
	curtain_pos.y = 0.0f;
	scene_change_flag = true;

	co_return;
}
