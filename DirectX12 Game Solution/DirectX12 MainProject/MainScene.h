//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "MyClass/GroundManager/GroundManager.h"
#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/AudianceManager/AudianceManager.h"
#include "MyClass/EnemyManager/EnemyManager.h"
#include "MyClass/Observer/Observer.h"
#include "MyClass/CameraManager/CameraManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/GameSceneManager/SceneManager.h"
#include "MyClass/DialogueManager/DialogueManager.h"
#include "MyClass/UIManager/UIManager.h"
#include "MyClass/Shader//SpotLight.h"

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
	void ChangeBGM(int music_num);
	void ChangeLightRenge(const float deltaTime);

	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	D3DLIGHT9 light{};

	DX9::SHADER shader;

	unique_ptr<SoundEffect> introduct,main,boss;
	unique_ptr<SoundEffectInstance> loop;

	GroundManager*   ground;
	CameraManager*   camera;
	PlayerBase*      player;
	EnemyManager*    enemy;
	AudienceManager* audience;
	DialogueManager* dialogue;
	Observer*        observer;
	UIManager*       ui;

	SpotLight point;

	enum LightMode {
		IN_ZOOM,
		OUT_ZOOM
	};

	enum MusicMode {
		INTRO,
		MAIN,
		BOSS
	};

	int nusic_mode = INTRO;
	int light_mode = IN_ZOOM;

	bool music_flag = false;

	float range = 0.8f;

	float end_frame = 0.0f;
	const float max_end = 3.0f;
};