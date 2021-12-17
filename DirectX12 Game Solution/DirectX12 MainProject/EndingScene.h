//
// TemplateScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class EndScene final : public Scene {
public:
	EndScene();
	virtual ~EndScene() { Terminate(); }

	EndScene(EndScene&&) = default;
	EndScene& operator= (EndScene&&) = default;

	EndScene(EndScene const&) = delete;
	EndScene& operator= (EndScene const&) = delete;

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
	unique_ptr<SoundEffect> bgm;
	unique_ptr<SoundEffectInstance> loop;

	DX9::SPRITE end_0, end_1, end_2,end_3,continued, curtain;

	SimpleMath::Vector3 end_0_pos   = SimpleMath::Vector3(0,0,-2);
	SimpleMath::Vector3 curtain_pos = SimpleMath::Vector3(0,-720.0f,0);

	enum DrawSprite {
		END_0,
		END_1,
		END_2,
		END_3
	};

	bool continued_flag = false;

	float draw_frame = 0.0f;
	const float max_draw = 10.0f;

	float scene_frame = 0.0f;
	float close_curtain_flag = false;

	int draw_sprite = END_0;

	float begin_speed = 10;
	float end_speed = 10;
};