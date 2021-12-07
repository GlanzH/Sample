#pragma once
#include "Base/pch.h"
#include <DirectXTK9.h>
#include <Base/dxtk.h>
#include "cppcoro/generator.h"
#include "Scene.h"

using namespace DirectX;

class SceneManager {
public:
	SceneManager() {};
	~SceneManager() {};


	void Initialize();
	void LoadAsset();
	NextScene Update(const float deltaTime);
	void Render();

private:
	DX9::SPRITE curtain;

	SimpleMath::Vector3 curtain_pos;

	float time_delta;
	bool ending_coro_flag;
	bool scene_change_flag;

	// コルーチンのプロトタイプ宣言
	cppcoro::generator<int> Ending();
	cppcoro::generator<int>	                 co_ending;
	cppcoro::detail::generator_iterator<int> co_ending_it;

};