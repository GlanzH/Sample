#include "Base/pch.h"
#include "Base/dxtk.h"
#include "PlayerManager.h"

bool PlayerManager::Initialize() 
{
	return true;
}

void PlayerManager::LoadAssets() 
{

	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Mikoto//mikoto.x");
	model->SetScale(0.04f);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, XMConvertToRadians(-90.0f), 0.0f);

}

int PlayerManager::Update(const float deltaTime) 
{
	//�v���C���[:�ړ�
	if (DXTK->KeyState->Right||DXTK->KeyState->D) {
		model->Move(0.0f, 0.0f, -10.0f * deltaTime);
		SetAnimation(model, Walk);
	}
	if (DXTK->KeyState->Left||DXTK->KeyState->A) {
		model->Move(0.0f, 0.0f, 10.0f * deltaTime);
	}

	//�v���C���[:�W�����v
	if (DXTK->KeyEvent->pressed.Space)
		jump_flag = true;

	if (jump_flag == true)
		player_pos.y = 10.0f * 5.0f * deltaTime - (0.5 * gravity * 5.0f * deltaTime);

	//�v���C���[:�U��
	if (DXTK->KeyEvent->pressed.L) {

	}

	//�����o�[�W���b�N




	return 0;
}

void PlayerManager::Render() 
{
	//�v���C���[�̕`��
	model->Draw();
}

//�w�肳�ꂽ���[�V������TRUE,����ȊO��FALSE
void PlayerManager::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}
