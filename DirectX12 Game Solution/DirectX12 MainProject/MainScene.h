//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "MyClass/Ground/Ground.h"
#include "MyClass/Camera/C_Camera.h"
#include "MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/AudianceManager/AudianceManager.h"
#include "MyClass/EnemyManager/EnemyManager.h"
#include "MyClass/Observer/Observer.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/GameSceneManager/SceneManager.h"
#include "MyClass/DialogueManager/DialogueManager.h"
#include "MyClass/UIManager/UIManager.h"
#include "MyClass/Shader//SpotLight.h"
#include "MyClass/Shader/TextureLight.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

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
	DX9::SPRITEFONT font;
	std::unique_ptr<SoundEffect> se;

	unique_ptr<SoundEffect> introduct,main,boss;
	unique_ptr<SoundEffectInstance> loop;

	Ground           ground;
	C_Camera         camera;
	PlayerBase*      player;
	EnemyManager*    enemy;
	AudienceManager* audience;
	DialogueManager  dialogue;
	Observer*        observer;
	UIManager*       ui;

	SpotLight point;
	TextureLight texLight;

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
	bool se_flag = false;
	bool end_a_play_flag = false;

	float range = 0.8f;

	float end_frame = 0.0f;
	float max_end = FLT_MAX;
};