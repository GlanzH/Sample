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
	observer = new Observer;
	ui       = new UIManager;
}

MainScene::~MainScene() {
	delete camera;
	delete ground;
	delete player;
	delete enemy;
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

	point.Init();
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

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = DX9::VectorSet(0.0f, -1.0f, 1.0f);
	light.Diffuse = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light.Ambient = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	DXTK->Direct3D9->SetLight(100.0f, light);
	DXTK->Direct3D9->LightEnable(0, true);

	//画像やモデルの初期化はこちら
	DX12Effect.Initialize();
	ground->LoadAsset();
	player->LoadAssets();
	ui->LoadAsset();
	
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

}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

	DX12Effect.Update(deltaTime);
	player->Update(deltaTime);
	camera->Update(player->GetModel()->GetPosition());
	enemy->Update(player->GetModel()->GetPosition(),deltaTime);
	observer->Update(player, enemy);

	return NextScene::Continue;
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

	point.SetLightPower(100.0f,0);
	point.PointRender(camera->GetCamera(), ground->GetModel(), player->GetModel());

	point.ShadeRender(player->GetModel(),SimpleMath::Vector4(0,0,1,0.3f));

	player->Render();
	enemy->Render();




	DX9::SpriteBatch->Begin();

	//2D描画
	//ui->Render(StatusManager::Instance().ReturnVolt(),StatusManager::Instance().ReturnParry());
	player->_2DRender();

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