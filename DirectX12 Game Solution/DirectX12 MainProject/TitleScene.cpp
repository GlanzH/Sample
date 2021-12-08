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

    opening_flag = false;
    start_flag = false;

    ui_alpha = 255.0f;
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
    title = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/curtain.png");
    title_ui = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/title_ui.png");
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

    if (opening_flag == false) {
        if (DXTK->KeyEvent->pressed.Enter ||
            DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED) {

            co_opening = Opening();        // コルーチンの生成
            co_opening_it = co_opening.begin(); // コルーチンの実行開始
            
            opening_flag = true;
        }
    }


    if (co_opening_it != co_opening.end()) {
        co_opening_it++;
    }

    if (co_opening_it != co_opening.end()) {
        co_opening.begin();
    }

    if (start_flag == true) {
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
        title_ui.Get(),
        SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
        RectWH(0, 0, 1280, 720),
        DX9::Colors::RGBA(255, 255, 255, ui_alpha)
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

    while (ui_alpha > 0.0f) {
        ui_alpha = std::max(ui_alpha - ALPHA_SPEED * time_delta, 0.0f);
        co_yield 1;
    }

    while (time_stop < 1.0f) {
        time_stop += time_delta;
        co_yield 2;
    }
    time_stop = 0.0f;

    while (title_pos.y > -730.0f) {
        title_pos.y -= CURTAIN_UP_SPEED * time_delta;
        co_yield 3;
    }
    
    start_flag = true;

    co_return;
}