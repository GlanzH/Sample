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
    title_pos.x = 0.0f;
    title_pos.y = 0.0f;
    title_pos.z = 1.0f;

    annouce_frame = 0;
    buzzer_frame = 0;
    flashing_alpha = 0.0f;
    flashing = 0;
    opening_flag = false;
    start_flag = false;
    flashing_alpha_flag = true;
    announce_flag = false;

    buzzer_flag = false;

    opencurtain_flag = false;

    ui_alpha = 255.0f;
    vinette_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    vinette_alpha = 255.0f;
    time_stop = 0.0f;
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
    title = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Curtain.png");
    title_logo = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/TitleLogo2.png");
    vinette = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/vinette_2.png");
    opening_buzzer = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/OpeningBuzzer.png");
    buzzer = std::make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/opening_buzzer.wav");
    announce = std::make_unique<SoundEffect>(DXTK->AudioEngine, L"BGM_SE/kaien.wav");
     buzzer_end = buzzer->CreateInstance();
     announce_end = announce->CreateInstance();
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
    if (flashing_alpha_flag)
    {
        flashing_alpha += 5;
    }
    
	// TODO: Add your game logic here.
    
    time_delta = deltaTime;
            
    if (opening_flag == false)
    {
        if (DXTK->KeyEvent->pressed.Space ||DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED) 
        {
            announce_flag = true;
            flashing_alpha_flag = false;
            if (opencurtain_flag)
            {
                co_opening = Opening();        // コルーチンの生成
                co_opening_it = co_opening.begin(); // コルーチンの実行開始
            }
        } 
        if (announce_flag && annouce_frame < annouce_max)
        {
            if (annouce_frame == 0.0)
            {
                announce->Play();
            }
            annouce_frame += deltaTime;
        }
        else if( annouce_frame >= annouce_max)
        {
            buzzer_flag = true;
        }

        if (buzzer_flag && buzzer_frame < buzzer_max)
        {
            if (buzzer_frame == 0.0)
            {
                buzzer->Play();
            }
            buzzer_frame += deltaTime;
        }
        else if( buzzer_frame >= buzzer_max)
        {
            opencurtain_flag = true;
        }

    }
   
        
    if (co_opening_it != co_opening.end()) {
        co_opening_it++;
    }

    if (co_opening_it != co_opening.end()) {
        co_opening.begin();
    }

    
    if (start_flag == true) 
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

    DX9::SpriteBatch->DrawSimple(title.Get(), title_pos);
    
    DX9::SpriteBatch->DrawSimple(
        title_logo.Get(),
        SimpleMath::Vector3(0.0f, -100.0f, 0.0f),
        RectWH(0, 0, 1280, 720),
        DX9::Colors::RGBA(255, 255, 255, ui_alpha)
    );

    DX9::SpriteBatch->DrawSimple(vinette.Get(), vinette_pos,
        Rect(0, 0, 1280, 720), DX9::Colors::RGBA(255, 255, 255, vinette_alpha));
    if (flashing_alpha_flag)
    {
        DX9::SpriteBatch->DrawSimple(opening_buzzer.Get(), SimpleMath::Vector3(550.0f, 500.0f, 0.0f), RectWH(0, 0, 1280, 720)
            , DX9::Colors::RGBA(255, 255, 255, flashing_alpha));
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

void TitleScene::Sound()
{
    if (announce_flag)
    {
        auto state = announce_end->GetState();
        // announce->Play();
        if (state == SoundState::STOPPED)
        {
            announce_flag = false;
            buzzer_flag = true;
        }
    }
    if (buzzer_flag)
    {
        auto a = buzzer_end->GetState();
        //  buzzer->Play();
        if (a == SoundState::STOPPED)
        {
            buzzer_flag = false;
            opencurtain_flag = true;
        }
    }
}

cppcoro::generator<int> TitleScene::Opening() {
    co_yield 0;

    while (ui_alpha > 0.0f) {
        ui_alpha = std::max(ui_alpha - ALPHA_SPEED * time_delta, 0.0f);
        vinette_alpha = std::max(vinette_alpha - ALPHA_SPEED * time_delta, 0.0f);
        co_yield 1;
    }
    

    while (time_stop < 1.0f) {
        time_stop += time_delta;
        co_yield 2;
    }
    time_stop = 0.0f;

    while (vinette_pos.y > -770.0f) {
        title_pos.y -= CURTAIN_UP_SPEED * time_delta;
        vinette_pos.y -= CURTAIN_UP_SPEED * time_delta;
        co_yield 3;
    }
    
    start_flag = true;

    co_return;
}

