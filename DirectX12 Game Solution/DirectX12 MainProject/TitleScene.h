//
// TitleScene.h
//

#pragma once
#include "cppcoro/generator.h"

#include "Scene.h"
#include "MyClass/GroundManager/GroundManager.h"
#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/AudianceManager/AudianceManager.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TitleScene final : public Scene {
public:
	TitleScene();
	virtual ~TitleScene() { Terminate(); }

	TitleScene(TitleScene&&) = default;
	TitleScene& operator= (TitleScene&&) = default;

	TitleScene(TitleScene const&) = delete;
	TitleScene& operator= (TitleScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
    DX12::DESCRIPTORHEAP descriptorHeap;
    DX12::SPRITEBATCH    spriteBatch;
    DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

private:
	GroundManager*   ground;
	CameraManager*   camera;
	PlayerBase*      player;
	AudienceManager* audience_m;

	DX9::SPRITE title;
	DX9::SPRITE title_ui;

	SimpleMath::Vector3 title_pos;

	float ui_alpha;
	float time_delta;
	float time_stop;

	bool opening_flag;
	bool start_flag;

	const float ALPHA_SPEED = 200.0f;
	
	const float CURTAIN_UP_SPEED = 130.0f;

	float audience;
	// コルーチンのプロトタイプ宣言
	cppcoro::generator<int> Opening();
	cppcoro::generator<int>                  co_opening;
	cppcoro::detail::generator_iterator<int> co_opening_it;
};