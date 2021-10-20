//
// MainScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;
using namespace DX9;
using namespace DX12;

class MainScene final : public Scene {
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	MainScene(MainScene&&) = default;
	MainScene& operator= (MainScene&&) = default;

	MainScene(MainScene const&) = delete;
	MainScene& operator= (MainScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:

	DESCRIPTORHEAP descriptorHeap;
	SPRITEBATCH    spriteBatch;
	HGPUDESCRIPTOR dx9GpuDescriptor;

	SKINNEDMODEL mikoto;
	CAMERA       mainCamera;


	//ƒ‰ƒCƒg
	D3DLIGHT9 light{};

	SimpleMath::Vector3 pos;
};