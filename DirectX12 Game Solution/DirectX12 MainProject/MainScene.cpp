//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
MainScene::MainScene(): dx9GpuDescriptor{}
{
	camera   = new CameraManager;
	ground   = new GroundManager;
	player   = new PlayerBase;
	enemy    = new EnemyManager;
	audience = new AudienceManager;
	dialogue = new DialogueManager;
	observer = new Observer;
	ui       = new UIManager;
}

MainScene::~MainScene() {
	delete camera;
	delete ground;
	delete player;
	delete enemy;
	delete audience;
	delete dialogue;
	delete observer;
	delete ui;

	Terminate();
}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
	//変数や関数の初期化はこちら
	player->Initialize();
	camera->Initialize();
	enemy->Initialize(player);
	SceneManager::Instance().Initialize();
	StatusManager::Instance().Initialize();

	point.Init(1);
	point.SetAmbientColor(Vector4(0, 0, 255, 1.0f),0);
	point.SetAtt(Vector3(0.65f, 0.001f, 0), 0);
	point.SetLightColor(SimpleMath::Vector4(255.0f, 189, 76, 1.0f), 0);

	font   = DX9::SpriteFont::CreateFromFontFile(DXTK->Device9,L"衡山毛筆フォント.ttf", L"衡山毛筆フォント", 250);
	se     = std::make_unique<SoundEffect>(DXTK->AudioEngine,L"dora.wav");

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

	ground->LoadAsset();
	player->LoadAssets();
	audience->LoadAssets();
	dialogue->LoadAssets();
	ui->LoadAsset();
	SceneManager::Instance().LoadAsset();
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
	enemy->OnDeviceLost();
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
	auto end_flag = enemy->GetDeathEnemyCount() >= enemy->GetEnemyNum() || StatusManager::Instance().ReturnAudience() <= 0.0f;

	ChangeLightRenge(deltaTime);

	if (!enemy->IsTimeStop()) {
		player->Update(deltaTime);
		enemy->Update(player->GetModel()->GetPosition(), player->IsDeathbrow(), audience->GetThrowThingsFlag(), deltaTime);
		audience->Update(player->GetAppielTime(), player->GetAppealCoolFlag(), player->GetSpecialAttackFlag(), deltaTime);
		camera->Update(player, OUT_ZOOM, deltaTime);
		observer->Update(player, enemy, audience);
		dialogue->ResetCount();

		//ChangeBGM(MAIN);
		light_mode = OUT_ZOOM;
	}
	else {
		dialogue->AddCount(enemy->IsTimeStop());
		camera->Update(player, IN_ZOOM, deltaTime);
		light_mode = IN_ZOOM;
	}
	
	if (end_flag) {
		end_frame += deltaTime;
		end_a_play_flag = true;

		if (!se_flag) {
			se->Play();
			se_flag = true;
		}

		if (enemy->GetDeathEnemyCount() >= enemy->GetEnemyNum())
			max_end = 10.0f;
		else
			max_end = 2.0f;

		if(end_frame > max_end) {
			DX12Effect.AllStop();

			SceneManager::Instance().Update(deltaTime);
			if (SceneManager::Instance().ReturnSceneFlag())
				return NextScene::ResultScene;
		}
	}

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
	DX12Effect.SetCamera((DX12::CAMERA)camera->GetCamera());
	camera->Render();

	
	point.SetPower(1.0f,0);
	point.PointRender(camera->GetCamera(), ground->GetModel());
	
	point.ShadeRender(player->GetModel(),SimpleMath::Vector4(0,0,1,0.3f));

	player->Render();
	enemy->Render();
	audience->Render();

	DX9::SpriteBatch->Begin();

	//2D描画
	ui->Render(StatusManager::Instance().ReturnAudience(),StatusManager::Instance().ReturnRenderHeart());
	player->_2DRender();
	player->BrackImage();
	SceneManager::Instance().Render();

	if (end_a_play_flag) {
		DX9::SpriteBatch->DrawString(font.Get(),
			SimpleMath::Vector2(130.0f, 200.0f),
			DX9::Colors::Red,
			L"劇 終"
		);
	}

	if (enemy->IsTimeStop())
		dialogue->Render(enemy->GetTimeStopCount());

	DX9::SpriteBatch->End();
	DXTK->Direct3D9->EndScene();


	DXTK->Direct3D9->UpdateResource();

	DXTK->ResetCommand();
	DXTK->ClearRenderTarget(DirectX::Colors::CornflowerBlue);

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