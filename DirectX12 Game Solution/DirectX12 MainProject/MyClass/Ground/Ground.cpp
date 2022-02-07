#include "Ground.h"
#include "MyClass/WaveProcess/WaveProcess.h"

void Ground::LoadAsset() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\BackGround\\stage.X");
	//
	model_forest = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\BackGround\\stage.X");
	model_ruins  = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\BackGround\\bg_remains.X");
	model_town   = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\BackGround\\town.X");
	//
	bg_forest = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\Forest\\forest.X");
	bg_ruins  = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\Forest\\ruins.X");
	bg_town   = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\Forest\\town.X");

	

	model->SetPosition(0.0f, -23.0, 0.0f);
	bg_forest->SetPosition(0, -25, 0);
	//a->SetScale(0.4f);
	bg_forest->SetPosition(0, -pos_y, 20.0f);
	pos = SimpleMath::Vector3::Zero;
}

/**
 * @fn �����ɂ���ă��[�V������؂�ւ���
 * @return �Ȃ�
 * @detail �ϐ���deltaTime�������āA�����ɂ���ă��[�V������؂�ւ���
 *         (��)30�t���[���@= �ϐ��̒l��0.3
 */
int Ground::Update(const float deltaTime) {
	/*if (DXTK->KeyState->J)
		pos.x -= 0.1f;

	if (DXTK->KeyState->U)
		pos.x += 0.1f;

	if (DXTK->KeyState->K)
		pos.y -= 0.1f;

	if (DXTK->KeyState->I)
		pos.y += 0.1f;

	if (DXTK->KeyState->L)
		pos.z -= 0.1f;

	if (DXTK->KeyState->O)
		pos.z += 0.1f;*/
	/*StatusManager::Instance().GetWave();
	if (StatusManager::Instance().GetWave()= 0 && �E�F�[�u�� �� = 3)*/
	//	�X�̔w�i���[�V�������Đ�����֐�

	//	if (�E�F�[�u���� = 4 && �E�F�[�u�� �� = 6)
	//		�X�̔w�i���[�V�������Đ�����֐�

	//		if (�E�F�[�u���� = 7 && �E�F�[�u�� �� = 9)
	//			��Ղ̔w�i���[�V�������Đ�����֐�

	//SetAnimation(a, (int)Forest::PLAY, (int)Forest::MAX_MOTION);
	//a->AdvanceTime(deltaTime / 1.0f);
	//a->SetPosition(pos);
	auto a = model->GetPosition();
	return 0;
}

void Ground::Render() {
	//model->Draw();
	//a->Draw();
}

/**
 * @fn ���f����n���֐�
 * @return �w�i���f��
 * @detail �V�[���ɂ���đΉ��������f����Ԃ��悤�ɂ���
 */

//DX9::SKINNEDMODEL& Ground::GetModel() {
//	
// if()
// {
// }
// 
// 
// 
// 
// 
// 
// 
// 
//	return town;
//	//return forest;
//	//return ruins;
//}
DX9::MODEL& Ground::GetModel() 
{
	if (StatusManager::Instance().GetWave() >=0 && StatusManager::Instance().GetWave() <= 3)
	{
		return model_forest;
	}
	if (StatusManager::Instance().GetWave() >= 0 && StatusManager::Instance().GetWave() <= 6)
	{
		return bg_town;
	}
	if (StatusManager::Instance().GetWave() >= 0 && StatusManager::Instance().GetWave() <= 9)
	{
		return bg_forest;
	}
	if (StatusManager::Instance().GetWave() >= 0 && StatusManager::Instance().GetWave() <= 12)
	{
		return bg_ruins;
	}
}


void Ground::SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack, int max_motion)
{
	for (int i = 0; i < max_motion; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}

