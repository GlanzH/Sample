//
// TitleScene.h
//

#pragma once
#include "cppcoro/generator.h"

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TitleScene final : public Scene {
public:
	TitleScene();
	virtual ~TitleScene() { Terminate(); }

	TitleScene(TitleScene&&) = default;
	TitleScene& operator= (TitleScene&&) = default;

	TitleScene(TitleScene const&) = delete;
	TitleScene& operator= (TitleScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;
private:
    DX12::DESCRIPTORHEAP descriptorHeap;
    DX12::SPRITEBATCH    spriteBatch;
    DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

private:
	DX9::SPRITE curtain;	//カーテン
	DX9::SPRITE title_logo;	//タイトルロゴ
	DX9::SPRITE shadow;	//影


	SimpleMath::Vector3 curtain_pos;
	SimpleMath::Vector3 shadow_pos;


	float title_logo_alpha;	//タイトルロゴのアルファ値
	float shadow_alpha;	//影のアルファ値
	float time_delta;
	float wait_time;	//間を作るのに使用

	bool opening_start_flag;	//コルーチン生成フラグ
	bool game_start_flag;	//シーン切り替えフラグ
	
	
	const float ALPHA_SPEED = 200.0f;	//アルファ値増減スピード
	const float CURTAIN_UP_SPEED = 130.0f;	//カーテンの上がるスピード

	//BGM
	DX9::MEDIARENDERER zawa;	//ざわつき音
	int zawa_volume;	//ざわつきの大きさ

	//SE
	XAudio::SOUNDEFFECT buzzer;	//ブザー音
	XAudio::SOUNDEFFECT start_se;	//ゲームスタート音

	// コルーチンのプロトタイプ宣言
	cppcoro::generator<int> Opening();	//オープニング演出
	cppcoro::generator<int>                  co_opening;
	cppcoro::detail::generator_iterator<int> co_opening_it;
};