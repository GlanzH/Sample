//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "MyClass/Ground/Ground.h"
#include "MyClass/Camera/C_Camera.h"
#include "MyClass/PlayerManager/PlayerManager.h"
//#include "MyClass/AudianceManager/AudianceManager.h"
#include "MyClass/EnemyManager/EnemyManager.h"
#include "MyClass/CoinManager/CoinManager.h"
#include "MyClass/Observer/Observer.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/GameSceneManager/SceneManager.h"
#include "MyClass/DialogueManager/DialogueManager.h"
#include "MyClass/UIManager/UIManager.h"
#include "MyClass/Shader//SpotLight.h"
#include "MyClass/Shader/TextureLight.h"
#include "MyClass/WaveProcess/WaveProcess.h"

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
	void ChangeBGM();
	void ChangeLightRenge(const float deltaTime);
	void TestChangeColor();
	void ChangeLightColor();
	
	void Writing();

	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	D3DLIGHT9 light{};

	DX9::SHADER shader;
	//DX9::SPRITEFONT font;
	std::unique_ptr<SoundEffect> se;

	unique_ptr<SoundEffect> introduct,main,boss;
	unique_ptr<SoundEffectInstance> loop;

	Ground           ground;
	C_Camera         camera;
	PlayerBase*      player;
	EnemyManager*    enemy;
	DialogueManager  dialogue;
	CoinManager      coin;
	Observer*        observer;
	WaveProcess      process;

	StatusManager status;
	SpotLight point;
	TextureLight texLight;

	DX9::MEDIARENDERER stage1;
	DX9::MEDIARENDERER stage2;
	DX9::MEDIARENDERER stage3;
	DX9::MEDIARENDERER stage4;
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
	int music_count;
	bool music_flag = false;
	bool se_flag = false;
	bool end_a_play_flag = false;

	bool Change_flag;

	bool mugic_loop_flag;

	//キャラライト
	float  lightColor_x, lightColor_y, lightColor_z;
	//背景ライト座標
	float  backlight_x, backlight_y, backlight_z;
	//全体ライト
	float backcolor_x, backcolor_y, backcolor_z;
	//キャラライトの環境色
	float backlightcolor_x, backlightcolor_y, backlightcolor_z;
	//全体ライトの環境色
	float backenvironmentalcolor_x, backenvironmentalcolor_y, backenvironmentalcolor_z;

	float playercone, backcone;
	float playerback;

	float range = 0.8f;
	float end_frame = 0.0f;
	float max_end = FLT_MAX;
};