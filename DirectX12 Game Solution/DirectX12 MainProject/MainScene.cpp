//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include<fstream>

// Initialize member variables.
MainScene::MainScene(): dx9GpuDescriptor{}
{
	player   = new PlayerBase;
	enemy    = new EnemyManager;
	audience = new AudienceManager;
	observer = new Observer;
}

MainScene::~MainScene() {
	delete player;
	delete enemy;
	delete audience;
	delete observer;

	Terminate();
}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
	//変数や関数の初期化はこちら
	player->Initialize();
	camera.Initialize();
	enemy->Initialize(player);
	SceneManager::Instance().Initialize();
	StatusManager::Instance().Initialize();
	UIManager::Instance().Initialize();
	time.Initialize();
	//フォント
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	point.Init(2);
	point.SetAmbientColor(Vector4(backcolor_x, backcolor_y, backcolor_z, 1.0f),0);
	point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
	/*point.SetLightColor(SimpleMath::Vector4(backlight_x, backlight_y, backlight_z, 1.0f), 0);*/

	point.SetAmbientColor(Vector4(backlightcolor_x, backlightcolor_y, backlightcolor_z, 1.0f), 1);
	point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
	//point.SetLightColor(SimpleMath::Vector4(lightColor_x, lightColor_y, lightColor_z, 1.0f), 1);

	texLight.Init();
	//Red
	lightColor_x = 255.0f;
	//Green
	lightColor_y = 255.0f;
	//Blue
	lightColor_z = 255.0f;
	//Red
	backlight_x = 255.0f;
	//Green
	backlight_y = 255.0f;
	//Blue
	backlight_z = 255.0f;
	//Red
	backcolor_x = 0.0f;
	//Green
	backcolor_y = 0.0f;
	//Blue
	backcolor_z = 0.0f;
	//Red
	backlightcolor_x = 0.0f;
	//Green
	backlightcolor_y = 0.0f;
	//Blue
	backlightcolor_z = 0.0f;

	
	std::ifstream infile("hiscore.dxt");

	infile >> lightColor_x >> lightColor_y >> lightColor_z >> backlight_x >> backlight_y >> backlight_z;

	enemy->StartTimeStop();
	end_frame = 0.0f;
}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
	descriptorHeap = DX12::CreateDescriptorHeap(DXTK->Device, 1);

	ResourceUploadBatch resourceUploadBatch(DXTK->Device);
	resourceUploadBatch.Begin();

	RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
	SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
	D3D12_VIEWPORT viewport = {
	0.0f, 0.0f, 1280.0f, 720.0f,
	D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
	};

	spriteBatch = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

	dx9GpuDescriptor = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap.get(), 0);

	auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
	uploadResourcesFinished.wait();

	DXTK->Direct3D9->SetRenderState(NormalizeNormals_Enable);
	DXTK->Direct3D9->SetRenderState(Specular_Enable);

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = DX9::VectorSet(0.0f, -1.0f, 1.0f);
	light.Diffuse = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light.Ambient = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	DXTK->Direct3D9->SetLight(100.0f, light);
	DXTK->Direct3D9->LightEnable(0, true);

	//画像やモデルの初期化はこちら
	DX12Effect.Initialize();

	introduct = make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/BGM/introduction_bgm.wav");
	main = make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/BGM/main_bgm.wav");
	boss = make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/BGM/introduction_bgm.wav");
	//music_flag = false;
	//ChangeBGM(INTRO);

	ground.LoadAsset();
	player->LoadAssets();
	audience->LoadAssets();
	dialogue.LoadAssets();
	UIManager::Instance().LoadAsset();
	SceneManager::Instance().LoadAsset();

	DX12Effect.SetCamera(camera.GetCamera());
}

// Releasing resources required for termination.
void MainScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{
	DX12Effect.Reset();
}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{
	loop->Play(true);
}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	//!終了時処理
	auto end_flag = StatusManager::Instance().GetScoreGauge() <= 0.0f;
	//auto end_flag = enemy->GetDeathEnemyCount() >= enemy->GetEnemyNum() || StatusManager::Instance().GetScoreGauge() <= 0.0f;
	//ground.Update(deltaTime);
	ChangeLightRenge(deltaTime);
	StatusManager::Instance().Update(deltaTime);
	UIManager::Instance().Update(deltaTime, camera.GetCamera()->GetPosition());

	if (!enemy->IsTimeStop()) {
		player->Update(deltaTime, enemy->GetTemporaryDeath());
		enemy->Update(player->GetModel()->GetPosition(),player->GetAttackTag(), player->GetEnemyDeathFlag(), deltaTime);
		camera.Update(player, OUT_ZOOM, deltaTime);
		observer->Update(player, enemy, audience);
		dialogue.ResetCount();
		time.Update(enemy,deltaTime);

		//ChangeBGM(MAIN);
		light_mode = OUT_ZOOM;
	}
	else {
		dialogue.AddCount(enemy->IsTimeStop());
		camera.Update(player, IN_ZOOM, deltaTime);
		light_mode = IN_ZOOM;
	}
	Writing();
	
	backlight_z = std::clamp(backlight_z, 0.0f, 255.0f);

	

	if (end_flag) {
		end_frame += deltaTime;
	
		max_end = 2.0f;

		if(end_frame > max_end) {
			DX12Effect.AllStop();
			if (SceneManager::Instance().ReturnSceneFlag())
				return NextScene::ResultScene;
		}
	}
	SceneManager::Instance().Update(deltaTime);

	if (end_frame < max_end)
		DX12Effect.Update(deltaTime);

	enemy->EndTimeStop();

	auto pos = player->GetModel()->GetPosition();

	point.SetPosition(Vector3(pos.x, 30, pos.z),0);

	return NextScene::Continue;
}

void MainScene::ChangeLightRenge(const float deltaTime) {
		if (DXTK->KeyState->W || light_mode == IN_ZOOM)
			range += 6.f * deltaTime;
		else
			range -= 30.f * deltaTime;

		range = std::clamp(range,0.8f,50.0f);

		point.SetCone(range, 0);
}

void MainScene::TestChangeColor(){
	
}

void MainScene::ChangeLightColor()
{
	switch (StatusManager::Instance().GetWave())
	{
	case 1:
		point.SetAmbientColor(Vector4(224, 255, 255, 1.0f), 0);
		point.SetAtt(Vector3(0.65f, 0.001f, 0), 0);
		point.SetLightColor(SimpleMath::Vector4(75, 0, 130, 1.0f), 0);
		break;
	case 2:
		point.SetAmbientColor(Vector4(0, 0, 255, 1.0f), 0);
		point.SetAtt(Vector3(0.65f, 0.001f, 0), 0);
		point.SetLightColor(SimpleMath::Vector4(255, 189, 76, 1.0f), 0);
		break;
	case 3:
		point.SetAmbientColor(Vector4(153, 50, 204, 1.0f), 0);
		point.SetAtt(Vector3(0.65f, 0.001f, 0), 0);
		point.SetLightColor(SimpleMath::Vector4(240, 128, 128, 1.0f), 0);
		break;
	default:
		break;
	}
}

void MainScene::Writing()
{
		if (DXTK->KeyState->F1) {
			backlightcolor_x += 1.0f;
		}

		if (DXTK->KeyState->F2) {
			backlightcolor_x -= 1.0f;
		}
		backlightcolor_x = std::clamp(backlightcolor_x, 0.0f, 255.0f);
		//Green
		if (DXTK->KeyState->F3) {
			backlightcolor_y += 1.0f;
		}

		if (DXTK->KeyState->F4){
			backlightcolor_y -= 1.0f;
		}
		backlightcolor_y = std::clamp(backlightcolor_y, 0.0f, 255.0f);
		//Blue
		if (DXTK->KeyState->F5) {
			backlightcolor_z += 1.0f;
		}

		if (DXTK->KeyState->F6) {
			backlightcolor_z -= 1.0f;
		}
		backlightcolor_z = std::clamp(backlightcolor_z, 0.0f, 255.0f);

		//全体
		//Red
		if (DXTK->KeyState->F7) {
			backcolor_x += 1.0f;
		}

		if (DXTK->KeyState->F8) {
			backcolor_x -= 1.0f;
		}
		backcolor_x = std::clamp(backcolor_x, 0.0f, 255.0f);
		//Green
		if (DXTK->KeyState->F9) {
			backcolor_y += 1.0f;
		}

		if (DXTK->KeyState->F10) {
			backcolor_y -= 1.0f;
		}
		backcolor_y = std::clamp(backcolor_y, 0.0f, 255.0f);
		//Blue
		if (DXTK->KeyState->F11) {
			backcolor_z += 1.0f;
		}

		if (DXTK->KeyState->F12) {
			backcolor_z -= 1.0f;
		}
		backcolor_z = std::clamp(backcolor_z, 0.0f, 255.0f);
	
	//スポットライト
	//Red
		if (DXTK->KeyState->R) {
			lightColor_x += 1.0f;
		}

		if (DXTK->KeyState->T) {
			lightColor_x -= 1.0f;
		}
		lightColor_x = std::clamp(lightColor_x, 0.0f, 255.0f);
		//Green
		if (DXTK->KeyState->Y) {
			lightColor_y += 1.0f;
		}

		if (DXTK->KeyState->U) {
			lightColor_y -= 1.0f;
		}
		lightColor_y = std::clamp(lightColor_y, 0.0f, 255.0f);
		//Blue
		if (DXTK->KeyState->I) {
			lightColor_z += 1.0f;
		}

		if (DXTK->KeyState->O) {
			lightColor_z -= 1.0f;
		}
		lightColor_z = std::clamp(lightColor_z, 0.0f, 255.0f);

		//全体
		//Red
		if (DXTK->KeyState->P) {
			backlight_x += 1.0f;
		}

		if (DXTK->KeyState->G) {
			backlight_x -= 1.0f;
		}
		backlight_x = std::clamp(backlight_x, 0.0f, 255.0f);
		//Green
		if (DXTK->KeyState->H) {
			backlight_y += 1.0f;
		}

		if (DXTK->KeyState->J) {
			backlight_y -= 1.0f;
		}
		backlight_y = std::clamp(backlight_y, 0.0f, 255.0f);
		//Blue
		if (DXTK->KeyState->K) {
			backlight_z += 1.0f;
		}

		if (DXTK->KeyState->L) {
			backlight_z -= 1.0f;
		}
}


void MainScene::ChangeBGM(int music_num) {
	if (!music_flag) {
		switch (music_num) {
		case INTRO:
			loop = introduct->CreateInstance();
			loop->Play(true);
			break;
		case MAIN:
			loop = main->CreateInstance();
			loop->Play(true);
			break;
		case BOSS:
			loop = boss->CreateInstance();
			loop->Play(true);
			break;
		}
		music_flag = true;
	}
}

// Draws the scene.
void MainScene::Render()
{
	// TODO: Add your rendering code here.
	DXTK->Direct3D9->Clear(DX9::Colors::CornflowerBlue);

	DXTK->Direct3D9->BeginScene();

	//3D描画
	camera.Render();
	ground.Render();
	DX12Effect.SetCameraPosition(camera.GetCamera());
	
	point.SetPower(1.0f,0);
	point.SetPower(2.0f, 1);
	point.SetPosition(player->GetModel()->GetPosition() + Vector3(0, 50, 0), 1);
	point.SetCone(30.0f, 1);
	point.PointRender(*camera.GetCamera(), ground.GetModel());
	point.SetLightColor(SimpleMath::Vector4(backlight_x, backlight_y, backlight_z, 1.0f), 0);
	point.SetAmbientColor(Vector4(backcolor_x, backcolor_y, backcolor_z, 1.0f), 0);
	point.SetAmbientColor(Vector4(backlightcolor_x, backlightcolor_y, backlightcolor_z, 1.0f), 1);
	point.SetLightColor(SimpleMath::Vector4(lightColor_x, lightColor_y, lightColor_z, 1.0f), 1);
	
	//point.PointRender(*camera.GetCamera(), player->GetModel());
	
	point.ShadeRender(player->GetModel(),SimpleMath::Vector4(0,0,1,0.3f));

	player->Render();
	enemy->Render();
	audience->Render();

	DX9::SpriteBatch->Begin();

	//2D描画
	UIManager::Instance(). Render();
	time.Render();
	player->Debug();
	SceneManager::Instance().Render();

	if (enemy->IsTimeStop())
		dialogue.Render(enemy->GetTimeStopCount());

	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(950.0f, 240.0f), DX9::Colors::BlueViolet, L"キャラライト");
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(950.0f, 290.0f), DX9::Colors::BlueViolet,L"%.2f",lightColor_x);
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(950.0f, 340.0f), DX9::Colors::BlueViolet, L"%.2f", lightColor_y );
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(950.0f, 390.0f), DX9::Colors::BlueViolet, L"%.2f", lightColor_z );

	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(950.0f, 440.0f), DX9::Colors::BlueViolet, L"全体ライト");
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(950.0f, 540.0f), DX9::Colors::BlueViolet, L"%.2f", backlight_x  );
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(950.0f, 590.0f), DX9::Colors::BlueViolet, L"%.2f", backlight_y  );
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(950.0f, 640.0f), DX9::Colors::BlueViolet, L"%.2f", backlight_z  );

	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(1100.0f, 240.0f), DX9::Colors::BlueViolet, L"キャラライトの環境色");
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(1200.0f, 290.0f), DX9::Colors::BlueViolet, L"%.2f", backcolor_x);
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(1200.0f, 340.0f), DX9::Colors::BlueViolet, L"%.2f", backcolor_y);
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(1200.0f, 390.0f), DX9::Colors::BlueViolet, L"%.2f", backcolor_z);

	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(1100.0f, 440.0f), DX9::Colors::BlueViolet, L"全体ライトの環境色");
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(1200.0f, 540.0f), DX9::Colors::BlueViolet, L"%.2f", backlightcolor_x);
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(1200.0f, 590.0f), DX9::Colors::BlueViolet, L"%.2f", backlightcolor_y);
	DX9::SpriteBatch->DrawString(font.Get(), SimpleMath::Vector2(1200.0f, 640.0f), DX9::Colors::BlueViolet, L"%.2f", backlightcolor_z);

	DX9::SpriteBatch->End();
	DXTK->Direct3D9->EndScene();


	DXTK->Direct3D9->UpdateResource();

	DXTK->ResetCommand();
	DXTK->ClearRenderTarget(DirectX::Colors::CornflowerBlue);
	texLight.Render();

	const auto heapes = descriptorHeap->Heap();
	DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

	spriteBatch->Begin(DXTK->CommandList);
	spriteBatch->Draw(
		dx9GpuDescriptor,
		XMUINT2(1280, 720),
		SimpleMath::Vector2(0.0f, 0.0f)
	);

	spriteBatch->End();

	DX12Effect.Renderer();

	DXTK->ExecuteCommandList();
	DXTK->Direct3D9->WaitUpdate();
}