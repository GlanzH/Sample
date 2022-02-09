//
// TitleScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
TitleScene::TitleScene()
{

}

// Initialize a variable and audio resources.
void TitleScene::Initialize()
{
    curtain_pos = SimpleMath::Vector3(0.0f, 0.0f, 1.0f);
    shadow_pos  = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

    title_logo_alpha = 255.0f;
    shadow_alpha     = 255.0f;
    wait_time = 0.0f;

    opening_start_flag = false;
    game_start_flag    = false;

    zawa_volume = 0;
}

// Allocate all memory the Direct3D and Direct2D resources.
void TitleScene::LoadAssets()
{
    descriptorHeap = DX12::CreateDescriptorHeap(DXTK->Device, 1);

    ResourceUploadBatch resourceUploadBatch(DXTK->Device);
    resourceUploadBatch.Begin();

    RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
    SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
    D3D12_VIEWPORT viewport = {
        0.0f, 0.0f, static_cast<int>(screen::width), static_cast<int>(screen::height),
        D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
    };

    spriteBatch = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

    dx9GpuDescriptor = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap.get(), 0);

    auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
    uploadResourcesFinished.wait();

    // グラフィックリソースの初期化処理
    curtain    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Curtain.png");
    title_logo = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/TitleLogo2.png");
    shadow     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/vinette_2.png");

    zawa = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM_SE/Title/before_the_performance.mp3");
    zawa->Play();

    buzzer   = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/Title/opening_buzzer.wav");
    start_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/Title/decision.wav");
}

// Releasing resources required for termination.
void TitleScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void TitleScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void TitleScene::OnRestartSound()
{

}

// Updates the scene.
NextScene TitleScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);
    
	// TODO: Add your game logic here.
    
    time_delta = deltaTime;
            
    zawa->SetVolume(zawa_volume);


    if (zawa->isComplete())
        zawa->Replay();

    if (!opening_start_flag)
    {
        if (DXTK->KeyEvent->pressed.Space ||
            DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED ||
            DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED)
        {
            co_opening    = Opening();        // コルーチンの生成
            co_opening_it = co_opening.begin(); // コルーチンの実行開始
            opening_start_flag = true;
            start_se->Play();
        }
    }
   
        
    if (co_opening_it != co_opening.end()) {
        co_opening_it++;
    }

    if (co_opening_it != co_opening.end()) {
        co_opening.begin();
    }

    
    if (game_start_flag) 
    {
        return NextScene::MainScene;
    }
    
	return NextScene::Continue;
}

// Draws the scene.
void TitleScene::Render()
{
	// TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(static_cast<D3DCOLOR>(DX9::Colors::RGBA(0, 0, 0, 255)));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    DX9::SpriteBatch->DrawSimple(curtain.Get(), curtain_pos);
    
    DX9::SpriteBatch->DrawSimple(
        title_logo.Get(),
        SimpleMath::Vector3(0.0f, -100.0f, 0.0f),
        nullptr,
        DX9::Colors::RGBA(255, 255, 255, title_logo_alpha)
    );

    DX9::SpriteBatch->DrawSimple(
        shadow.Get(),
        shadow_pos,
        nullptr,
        DX9::Colors::RGBA(255, 255, 255, shadow_alpha)
    );
   

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
        XMUINT2(static_cast<int>(screen::width), static_cast<int>(screen::height)),
        SimpleMath::Vector2(0.0f, 0.0f)
    );
    spriteBatch->End();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}

cppcoro::generator<int> TitleScene::Opening() {
    co_yield 0;

    //タイトルロゴ、影をフェードアウト
    while (shadow_alpha > 0.0f) {
        title_logo_alpha = std::max(title_logo_alpha - ALPHA_SPEED * time_delta, 0.0f);
        shadow_alpha = std::max(shadow_alpha - ALPHA_SPEED * time_delta, 0.0f);
        co_yield 1;
    }

    //間
    while (wait_time < 1.0f) {
        wait_time += time_delta;
        co_yield 2;
    }
    wait_time = 0.0f;
    
    buzzer->Play();
    //間
    while (wait_time < 9.0f) {
        zawa_volume -= 1000 * time_delta;
        wait_time += time_delta;
        co_yield 3;
    }
    wait_time = 0.0f;
    zawa_volume = -1500;


    //カーテンを上げる
    while (shadow_pos.y > -770.0f) {
        curtain_pos.y -= CURTAIN_UP_SPEED * time_delta;
        shadow_pos.y -= CURTAIN_UP_SPEED * time_delta;
        co_yield 4;
    }
    
    game_start_flag = true;

    co_return;
}

