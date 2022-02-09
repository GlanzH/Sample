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
	DX9::SPRITE curtain;	//�J�[�e��
	DX9::SPRITE title_logo;	//�^�C�g�����S
	DX9::SPRITE shadow;	//�e


	SimpleMath::Vector3 curtain_pos;
	SimpleMath::Vector3 shadow_pos;


	float title_logo_alpha;	//�^�C�g�����S�̃A���t�@�l
	float shadow_alpha;	//�e�̃A���t�@�l
	float time_delta;
	float wait_time;	//�Ԃ����̂Ɏg�p

	bool opening_start_flag;	//�R���[�`�������t���O
	bool game_start_flag;	//�V�[���؂�ւ��t���O
	
	
	const float ALPHA_SPEED = 200.0f;	//�A���t�@�l�����X�s�[�h
	const float CURTAIN_UP_SPEED = 130.0f;	//�J�[�e���̏オ��X�s�[�h

	//BGM
	DX9::MEDIARENDERER zawa;	//�������
	int zawa_volume;	//������̑傫��

	//SE
	XAudio::SOUNDEFFECT buzzer;	//�u�U�[��
	XAudio::SOUNDEFFECT start_se;	//�Q�[���X�^�[�g��

	// �R���[�`���̃v���g�^�C�v�錾
	cppcoro::generator<int> Opening();	//�I�[�v�j���O���o
	cppcoro::generator<int>                  co_opening;
	cppcoro::detail::generator_iterator<int> co_opening_it;
};