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

    title_logo_alpha = 255.0f;
    pro_text_alpha = 0.0f;
    wait_time = 0.0f;

    opening_start_flag = false;
    game_start_flag    = false;

    zawa_volume = 0;

    pv_play_flag = false;
    pv_play_waittime = 0.0f;

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
    title_logo = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Title/TitleLogo.png");

    zawa = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM_SE/Title/before_the_performance.mp3");
    zawa->Play();

    buzzer   = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/Title/opening_buzzer.wav");
    start_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/Title/decision.wav");

    prologue_text = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/dialogue_01_01.png");

    pv = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"Scene/Title/play_demo_1.wmv");
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

    if (DXTK->KeyEvent->pressed.B ||
        DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED ||
        DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED
        )
    {
        if (!opening_start_flag && !pv_play_flag)
        {
            co_opening = Opening();        // コルーチンの生成
            co_opening_it = co_opening.begin(); // コルーチンの実行開始
            opening_start_flag = true;
            start_se->Play();
        }
        pv_play_flag = false;
        pv_play_waittime = 0.0f;
        pv->Stop();

    }

    if (!opening_start_flag) {
        pv_play_waittime += deltaTime;

        //PV再生が終わったらフラグを降ろす
        if (pv->isComplete() && pv_play_flag) {
            pv_play_flag = false;
            pv_play_waittime = 0.0f;
        }

        //一定時間放置したらPV再生
        if (pv_play_waittime > 3.0f && !pv_play_flag) {
            pv_play_flag = true;
            if (!pv->isComplete()) {
                pv->Play();
            }
            else {
                pv->Replay();
            }
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
        prologue_text.Get(),
        SimpleMath::Vector3(0.0f, 0.0f, 4.0f),
        nullptr,
        DX9::Colors::RGBA(255, 255, 255, pro_text_alpha)
    );

    if (pv_play_flag) {
        DX9::SpriteBatch->DrawSimple(
            pv->Get(),
            SimpleMath::Vector3(0.0f, 0.0f, -20.0f)
        );
    }

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
    while (title_logo_alpha > 0.0f) {
        title_logo_alpha = std::max(title_logo_alpha - ALPHA_SPEED * time_delta, 0.0f);
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
    while (wait_time < 5.0f) {
        zawa_volume -= 1000 * time_delta;
        wait_time += time_delta;
        co_yield 3;
    }
    wait_time = 0.0f;
    zawa_volume = -1500;


    //カーテンを上げる
    while (curtain_pos.y > -770.0f) {
        curtain_pos.y -= CURTAIN_UP_SPEED * time_delta;
        co_yield 4;
    }

    //間
    while (wait_time < 1.0f) {
        wait_time += time_delta;
        co_yield 5;
    }
    wait_time = 0.0f;


    //テキスト表示
    while (true) {

        if(!game_start_flag)
            pro_text_alpha = std::min(pro_text_alpha + 100.0f * time_delta, 255.0f);

        if (DXTK->KeyEvent->pressed.B ||
            DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED ||
            DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED
            ) {
            game_start_flag = true;
        }

        co_yield 6;
    }
    co_return;
}

