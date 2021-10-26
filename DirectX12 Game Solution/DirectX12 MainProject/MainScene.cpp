//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{

	pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

	//�J�����̈ʒu
	mainCamera->SetView(SimpleMath::Vector3(0.0f, 0.0f, -10.0f),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f)
	);
	//�J�����̌����E�f������
	mainCamera->SetPerspectiveFieldOfView(
		XMConvertToRadians(60.0f), 16.0f / 9.0f, 1.0f, 10000.0f
	);

//�ϐ���֐��̏������͂�����
	text.Initialize();
	text.LoadText();
	camera.Initialize();

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

	mikoto = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Mikoto//mikoto.x");


	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = DX9::VectorSet(0.0f, -1.0f, 1.0f);
	light.Diffuse = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light.Ambient = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
	DXTK->Direct3D9->SetLight(0, light);
	DXTK->Direct3D9->LightEnable(0, true);


	//�摜�⃂�f���̏������͂�����
	ground.LoadAsset();
	player.LoadAssets();
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

	if (DXTK->KeyState->Up || DXTK->GamePadState->IsLeftThumbStickUp())
		pos.y -= 3.0f;
	if (DXTK->KeyState->Down || DXTK->GamePadState->IsLeftThumbStickDown())
		pos.y += 3.0f;
	if (DXTK->KeyState->Left || DXTK->GamePadState->IsLeftThumbStickLeft())
		pos.x -= 3.0f;
	if (DXTK->KeyState->Right || DXTK->GamePadState->IsLeftThumbStickRight())
		pos.x += 3.0f;
	
	mikoto->AdvanceTime(deltaTime / 100.0f);


	text.Update(deltaTime);
	player.Update(deltaTime);
	enemy.Update(deltaTime,ground.GetModel());
	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{

	DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

	DXTK->Direct3D9->BeginScene();

	DXTK->Direct3D9->SetCamera(mainCamera);

	DX9::SpriteBatch->Begin();

	mikoto->Draw();

	// TODO: Add your rendering code here.
	DXTK->Direct3D9->Clear(DX9::Colors::CornflowerBlue);

	DXTK->Direct3D9->BeginScene();

	//3D�`��
	camera.Render(player.GetModel()->GetPosition());
	ground.Render();

	player.Render();

	DX9::SpriteBatch->Begin();

	//2D�`��
	text.Render2D();

	DX9::SpriteBatch->End();
	DXTK->Direct3D9->EndScene();


	DXTK->Direct3D9->UpdateResource();

	DXTK->ResetCommand();
	DXTK->ClearRenderTarget(DirectX::Colors::CornflowerBlue);

	const auto heapes = descriptorHeap->Heap();
	DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

	spriteBatch->Begin(DXTK->CommandList);

	spriteBatch->Draw(dx9GpuDescriptor,XMUINT2(1280, 720),SimpleMath::Vector3(400.0f,0.0f, 0.0f));

	spriteBatch->Draw(
		dx9GpuDescriptor,
		XMUINT2(1280, 720),
		SimpleMath::Vector2(0.0f, 0.0f)
	);

	spriteBatch->End();


	spriteBatch->End();

	DXTK->Direct3D9->WaitUpdate();
	DXTK->ExecuteCommandList();
	// TODO: Add your rendering code here.
}
//	DXTK->Direct3D9->WaitUpdate();
//}

