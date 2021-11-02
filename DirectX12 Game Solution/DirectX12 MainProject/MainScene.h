//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "MyClass/GroundManager/GroundManager.h"
#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/TextManager/TextManager.h"
#include "MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/EnemyManager/EnemyManager.h"
#include "MyClass/Observer/Observer.h"
#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/SwordManager/SwordManager.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;
using namespace DX9;
class MainScene final : public Scene {
public:
	MainScene();
	virtual ~MainScene();

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
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	D3DLIGHT9 light{};

	GroundManager  ground;
	CameraManager  camera;
	TextManager	   text;
	PlayerManager* player;
	EnemyManager*  enemy;
	Observer*      observer;
	SwordManager   sword;
};