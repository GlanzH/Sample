#include "Ground.h"
#include "MyClass/WaveProcess/WaveProcess.h"

void Ground::LoadAsset() {

	ruins =  DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_notanim\\bg_remains.X");
	forest = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_notanim\\bg_forest.X");
	town = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_notanim\\bg_town.X");
	
	forest->SetPosition(0.0f, -25.0f, 20.0f);
	ruins->SetPosition(0, -25, 7.0f);
	town->SetPosition(0, -25, 7.0f);
	pos = SimpleMath::Vector3::Zero;
}
int Ground::Update(const float deltaTime) {
	

	return 0;
}

void Ground::Render() {
	
}
//MODELŒ^
DX9::MODEL& Ground::GetModel() 
{
	if (StatusManager::Instance().GetWave() >= 0 && StatusManager::Instance().GetWave() <= 3)
	{
		return forest;
	}
	if (StatusManager::Instance().GetWave() >= 4 && StatusManager::Instance().GetWave() <= 6)
	{
		return town;
	}
	if (StatusManager::Instance().GetWave() >= 7 && StatusManager::Instance().GetWave() <= 9)
	{
		return forest;
	}
	if (StatusManager::Instance().GetWave() >= 10 && StatusManager::Instance().GetWave() <= 12)
	{
		return ruins;
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

