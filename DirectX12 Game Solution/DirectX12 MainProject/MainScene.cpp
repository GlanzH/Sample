//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include"MyClass/StatusManager/StatusManager.h"

// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{
	player = new PlayerBase;
	enemy = new EnemyManager;
//	audience = new AudienceManager;
	observer = new Observer;
}

MainScene::~MainScene() {
	delete player;
	delete enemy;
	//delete audience;
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
	process.Initialize();

	point.Init(2);
	//TestChangeColor();
	if (StatusManager::Instance().GetWave() >= 0 && StatusManager::Instance().GetWave() <= 3)
	{
		////全体ライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
		point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
		point.SetLightColor(SimpleMath::Vector4(0.0f, 147.0f, 165.0f, 1.0f), 0);
		////キャラのライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
		point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
		point.SetLightColor(SimpleMath::Vector4(175.0f, 74.0f, 94.0f, 1.0f), 1);
	}

	if (StatusManager::Instance().GetWave() >= 4 && StatusManager::Instance().GetWave() <= 6)
	{
		//全体ライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
		point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
		point.SetLightColor(SimpleMath::Vector4(97.0f, 67.0f, 167.0f, 1.0f), 0);
		//キャラのライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
		point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
		point.SetLightColor(SimpleMath::Vector4(110.0f, 71.0f, 47.0f, 1.0f), 1);
	}

	if (StatusManager::Instance().GetWave() >= 7 && StatusManager::Instance().GetWave() <= 9)
	{
		////全体ライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
		point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
		point.SetLightColor(SimpleMath::Vector4(127.0f, 0.0f, 187.0f, 1.0f), 0);
		////キャラのライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
		point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
		point.SetLightColor(SimpleMath::Vector4(69.0f, 108.0f, 0.0f, 1.0f), 1);
	}

	if (StatusManager::Instance().GetWave() >= 10 && StatusManager::Instance().GetWave() <= 12)
	{
		////全体ライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
		point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
		point.SetLightColor(SimpleMath::Vector4(198.0f, 91.0f, 39.0f, 1.0f), 0);
		////キャラのライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
		point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
		point.SetLightColor(SimpleMath::Vector4(63.0f, 65.0f, 0.0f, 1.0f), 1);
	}

	////全体ライト
	//point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
	//point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
	//point.SetLightColor(SimpleMath::Vector4(0.0f, 147.0f, 165.0f, 1.0f), 0);
	////キャラのライト

	//point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
	//point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
	//point.SetLightColor(SimpleMath::Vector4(175.0f, 74.0f, 94.0f, 1.0f), 1);
	texLight.Init();

	
	//enemy->StartTimeStop();
	end_frame = 0.0f;
}
void MainScene::TestChangeColor()
{
	if(StatusManager::Instance().GetWave() >= 0 && StatusManager::Instance().GetWave() <= 3)
	{
	////全体ライト
	point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
	point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
	point.SetLightColor(SimpleMath::Vector4(0.0f, 147.0f, 165.0f, 1.0f), 0);
	////キャラのライト
	point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
	point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
	point.SetLightColor(SimpleMath::Vector4(175.0f, 74.0f, 94.0f, 1.0f), 1);
	}

	if (StatusManager::Instance().GetWave() >= 4 && StatusManager::Instance().GetWave() <= 6)
	{
		//全体ライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
		point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
		point.SetLightColor(SimpleMath::Vector4(97.0f, 67.0f, 167.0f, 1.0f), 0);
		//キャラのライト
		point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
		point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
		point.SetLightColor(SimpleMath::Vector4(110.0f, 71.0f, 47.0f, 1.0f), 1);
	}

	if(StatusManager::Instance().GetWave() >= 7 && StatusManager::Instance().GetWave() <= 9)
	{
	////全体ライト
	point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
	point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
	point.SetLightColor(SimpleMath::Vector4(127.0f, 0.0f, 187.0f, 1.0f), 0);
	////キャラのライト
	point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
	point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
	point.SetLightColor(SimpleMath::Vector4(69.0f, 108.0f, 0.0f, 1.0f), 1);
	}

	if(StatusManager::Instance().GetWave() >= 10 && StatusManager::Instance().GetWave() <= 12)
	{
	////全体ライト
	point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f), 0);
	point.SetAtt(Vector3(0.25f, 0.01f, 0), 0);
	point.SetLightColor(SimpleMath::Vector4(198.0f, 91.0f, 39.0f, 1.0f), 0);
	////キャラのライト
	point.SetAmbientColor(Vector4(0.0f, 0.0f, 0.0f, 1.0f), 1);
	point.SetAtt(Vector3(0.05f, 0.01f, 0), 1);
	point.SetLightColor(SimpleMath::Vector4(63.0f, 65.0f, 0.0f, 1.0f), 1);
	}
	
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
	//audience->LoadAssets();
	dialogue.LoadAssets();
	process.LoadAssets();
	coin.LoadAssets();
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
	// TODO: Add your game logic here.

	//ヒットストップ(ベース)
	float delta_time = deltaTime;
	if (observer->GetHitStop())
		delta_time *= 0.001f;

	//!終了時処理
	auto end_flag = StatusManager::Instance().GetScoreGauge() <= 0.0f;
	//auto end_flag = enemy->GetDeathEnemyCount() >= enemy->GetEnemyNum() || StatusManager::Instance().GetScoreGauge() <= 0.0f;
	//ground.Update(deltaTime);
	ChangeLightRenge(deltaTime);
	StatusManager::Instance().Update(deltaTime, enemy->GetRemainEnemy());
	UIManager::Instance().Update(deltaTime, enemy->GetWaveEnemy(), enemy->GetDeathEnemyCount());
	UIManager::Instance().SetUICamera(camera.GetCamera());
	if (StatusManager::Instance().GetWave() > 0 && StatusManager::Instance().GetTime() > StatusManager::Instance().GetOnceExec())
		enemy->StartTimeStop();

	if (process.GetAnimEndFlag()) {
		enemy->EndTimeStop();
	}

	if (!enemy->IsTimeStop()) {
		player->Update(delta_time, enemy->GetTemporaryDeath());
		enemy->Update(player->GetModel()->GetPosition(), player->GetAttackTag(), player->GetEnemyDeathFlag(), delta_time);
		camera.Update(player, OUT_ZOOM, delta_time);
		observer->Update(player, enemy, coin);
		dialogue.ResetCount();
		process.Update(enemy, deltaTime);
		coin.Update(player->GetModel()->GetPosition(), enemy->GetDeathFlag(), enemy->GetDeathEnemyCount(), deltaTime);
		observer->Hit_Stop(deltaTime);

		//ChangeBGM(MAIN);
		light_mode = OUT_ZOOM;
	}
	else {
		process.WaveAnimation(deltaTime);
		if (process.GetAnimEndFlag()) {
			dialogue.AddCount(enemy->IsTimeStop());
			camera.Update(player, IN_ZOOM, deltaTime);
			light_mode = IN_ZOOM;
		}
	}


	if (end_flag) {
		end_frame += deltaTime;

		//max_end = 2.0f;

		if (end_frame > 2.0f) {
			DX12Effect.AllStop();
			//if (SceneManager::Instance().ReturnSceneFlag())
			//	return NextScene::ResultScene;
		}
	}

	if (SceneManager::Instance().ReturnSceneFlag())
		return NextScene::ResultScene;

	SceneManager::Instance().Update(deltaTime, process.GetClearFlag());

	if (end_frame < max_end)
		DX12Effect.Update(deltaTime);

	enemy->EndTimeStop();

	auto pos = player->GetModel()->GetPosition();

	point.SetPosition(Vector3(pos.x, 30, pos.z), 0);

	return NextScene::Continue;
}

void MainScene::ChangeLightRenge(const float deltaTime) {
	if (DXTK->KeyState->W || light_mode == IN_ZOOM)
		range += 6.f * deltaTime;
	else
		range -= 30.f * deltaTime;

	range = std::clamp(range, 0.8f, 50.0f);

	point.SetCone(range, 0);
}



void MainScene::ChangeLightColor()
{
	if (StatusManager::Instance().GetWave() >= 0 && StatusManager::Instance().GetWave() <= 3)
	{
		point.SetPower(1.5f, 0);
		point.SetPower(2.5f, 1);
		point.SetPosition(Vector3(0.0f, 0.0f, 0.0f), 0);
		point.SetPosition(player->GetModel()->GetPosition() + Vector3(0, 50, 16.0f), 1);
		point.SetCone(0.0f, 0);
		point.SetCone(6.0f, 1);
		point.PointRender(*camera.GetCamera(), ground.GetModel());

		point.ShadeRender(player->GetModel(), SimpleMath::Vector4(0, 0, 1, 0.3f));
	}

	if (StatusManager::Instance().GetWave() >= 4 && StatusManager::Instance().GetWave() <= 6)
	point.SetPower(1.5f, 0);
	point.SetPower(2.5f, 1);
	point.SetPosition(Vector3(0.0f, 170.0f, 87.0f), 0);
	point.SetPosition(player->GetModel()->GetPosition() + Vector3(0, 50, 9.0f), 1);
	point.SetCone(2.39f, 0);
	point.SetCone(9.0f, 1);
	point.PointRender(*camera.GetCamera(), ground.GetModel());

	point.ShadeRender(player->GetModel(), SimpleMath::Vector4(0, 0, 1, 0.3f));
	if (StatusManager::Instance().GetWave() >= 7 && StatusManager::Instance().GetWave() <= 9)
		point.SetPower(1.5f, 0);
	point.SetPower(2.5f, 1);
	point.SetPosition(Vector3(0.0f, 0.0f, 0.0f), 0);
	point.SetPosition(player->GetModel()->GetPosition() + Vector3(0, 50, 17.0f), 1);
	point.SetCone(0.0f, 0);
	point.SetCone(3.0f, 1);
	point.PointRender(*camera.GetCamera(), ground.GetModel());

	point.ShadeRender(player->GetModel(), SimpleMath::Vector4(0, 0, 1, 0.3f));
	if (StatusManager::Instance().GetWave() >= 10 && StatusManager::Instance().GetWave() <= 12)
		point.SetPower(1.5f, 0);
	point.SetPower(2.5f, 1);
	point.SetPosition(Vector3(0.0f, 0.0f, 0.0f), 0);
	point.SetPosition(player->GetModel()->GetPosition() + Vector3(0, 50, 21.0f), 1);
	point.SetCone(0.0f, 0);
	point.SetCone(4.0f, 1);
	point.PointRender(*camera.GetCamera(), ground.GetModel());

	point.ShadeRender(player->GetModel(), SimpleMath::Vector4(0, 0, 1, 0.3f));

	point.SetPower(1.5f, 0);
	point.SetPower(2.5f, 1);
	point.SetPosition(Vector3(0.0f, 0.0f, 0.0f), 0);
	point.SetPosition(player->GetModel()->GetPosition() + Vector3(0, 50, 16.0f), 1);
	point.SetCone(0.0f, 0);
	point.SetCone(6.0f, 1);
	point.PointRender(*camera.GetCamera(), ground.GetModel());

	point.ShadeRender(player->GetModel(), SimpleMath::Vector4(0, 0, 1, 0.3f));
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
	ChangeLightColor();
	//3D描画
	camera.Render();
	ground.Render();
	DX12Effect.SetCameraPosition(camera.GetCamera());
	


	player->Render();
	enemy->Render();
	//audience->Render();

	DX9::SpriteBatch->Begin();

	//2D描画
	UIManager::Instance().Render();
	process.Render();
	player->Debug();
	SceneManager::Instance().Render();

	if (enemy->IsTimeStop() && process.GetAnimEndFlag())
		dialogue.Render(enemy->GetTimeStopCount());

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
	UIManager::Instance().EfkRender();
	DXTK->ExecuteCommandList();
	DXTK->Direct3D9->WaitUpdate();
}