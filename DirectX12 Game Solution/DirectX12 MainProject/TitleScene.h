//
// TitleScene.h
//

#pragma once
#include "cppcoro/generator.h"

#include "Scene.h"
#include "MyClass/Ground/Ground.h"
#include "MyClass/Camera/C_Camera.h"
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
	void Sound();
private:
    DX12::DESCRIPTORHEAP descriptorHeap;
    DX12::SPRITEBATCH    spriteBatch;
    DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

private:
	DX9::SPRITE title;
	DX9::SPRITE title_logo;
	DX9::SPRITE opening_buzzer;
	SimpleMath::Vector3 title_pos;

	DX9::SPRITE vinette;
	SimpleMath::Vector3 vinette_pos;

	float vinette_alpha;
	float flashing_alpha;
	float ui_alpha;
	float time_delta;
	float time_stop;
    float flashing;

	float buzzer_frame;
	const float buzzer_max = 5.00f;
	float annouce_frame;
	const float annouce_max = 5.00f;

	std::unique_ptr<SoundEffect>buzzer, announce;
	std::unique_ptr<SoundEffectInstance> buzzer_end;
	std::unique_ptr<SoundEffectInstance> announce_end;
	bool flashing_alpha_flag;
	bool announce_flag;
	bool buzzer_flag;
	bool opening_flag;
	bool start_flag;
	bool opencurtain_flag;
	const float ALPHA_SPEED = 200.0f;
	
	const float CURTAIN_UP_SPEED = 130.0f;

	float audience;
	// コルーチンのプロトタイプ宣言
	cppcoro::generator<int> Opening();
	cppcoro::generator<int>                  co_opening;
	cppcoro::detail::generator_iterator<int> co_opening_it;
};