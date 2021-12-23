//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "EndingScene.h"

// Initialize member variables.
EndScene::EndScene()
{

}

// Initialize a variable and audio resources.
void EndScene::Initialize()
{
    begin_speed = 10.0f;
    end_speed   = 10.0f;
    continued_flag     = false;
    close_curtain_flag = false;
}

// Allocate all memory the Direct3D and Direct2D resources.
void EndScene::LoadAssets()
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

    end_0     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ending/END00.png");
    end_1     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ending/END01.png");
    end_2     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ending/END02.png");
    end_3     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ending/END03.png");
    continued = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ending/ToBeContinued.png");
    curtain = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Result/curtain_bright.png");

    bgm = make_unique<SoundEffect>(DXTK->AudioEngine, L"Ending/コンギョ.wav");
    loop = bgm->CreateInstance();
    loop->Play(false);
}

// Releasing resources required for termination.
void EndScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void EndScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void EndScene::OnRestartSound()
{
   // loop->Play(false);
}

// Updates the scene.
NextScene EndScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.
    
    scene_frame += deltaTime;

    if (draw_sprite == END_0) {
        if (draw_frame >= 14.0f) {
            end_0_pos.y -= begin_speed * deltaTime;
            begin_speed *= 1.08f;
        }
        if (draw_frame >= 15.5f) {
            draw_sprite = END_1;
            draw_frame = 0.0f;
        }
        else {
            draw_frame += deltaTime;
        }
    }

    switch (draw_sprite) {
    case END_1:
    case END_2:
    case END_3:
        draw_frame += deltaTime;
        if (draw_frame >= 5.0f) {
            draw_frame = 0.0f;
            ++draw_sprite;
            if (draw_sprite > END_3)
                draw_sprite = END_1;
        }
        break;
    }
    if (scene_frame >= 143.0f)
        close_curtain_flag = true;

    if (scene_frame >= 147.5f) {
        draw_sprite = END_3;
        continued_flag = true;
    }

    if (close_curtain_flag && curtain_pos.y <= -15.8f) {
        curtain_pos.y += end_speed * deltaTime;
        end_speed *= 1.04f;
    }

    if (DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED || DXTK->KeyEvent->pressed.B)
        return NextScene::TitleScene;

	return NextScene::Continue;
}

// Draws the scene.
void EndScene::Render()
{
	// TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(static_cast<D3DCOLOR>(DX9::Colors::RGBA(0, 0, 0, 255)));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

     
    DX9::SpriteBatch->DrawSimple(
        end_0.Get(),
        end_0_pos,
        RectWH(0, 0, 1280, 720)
    );

    DX9::SpriteBatch->DrawSimple(
        end_1.Get(),
        SimpleMath::Vector3(0,0,1),
        RectWH(0, 0, 1280, 720)
    );

    switch (draw_sprite)
    {
    case END_1:
        DX9::SpriteBatch->DrawSimple(
            end_1.Get(),
            SimpleMath::Vector3::Zero,
            RectWH(0, 0, 1280, 720)
        );
    break;

    case END_2:
        DX9::SpriteBatch->DrawSimple(
            end_2.Get(),
            SimpleMath::Vector3::Zero,
            RectWH(0, 0, 1280, 720)
        );
    break;

    case END_3:
        DX9::SpriteBatch->DrawSimple(
            end_3.Get(),
            SimpleMath::Vector3::Zero,
            RectWH(0, 0, 1280, 720)
        );
    break;
    }

    if (continued_flag) {
    DX9::SpriteBatch->DrawSimple(
        continued.Get(),
        SimpleMath::Vector3(0, 0, -10),
        RectWH(0, 0, 1280, 720)
    );
    }



    DX9::SpriteBatch->DrawSimple(
        curtain.Get(),
       curtain_pos,
        RectWH(0, 0, 1280, 720)
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
