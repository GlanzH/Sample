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

	town = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_notanim\\bg_town_notanim.X");
	forest = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_notanim\\bg_forest_notanim.X");
	ruins = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_notanim\\bg_remains_notanim.X");
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\BackGround\\stage.X");
	/*town   = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_anim\\bg_town.X");
	forest = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_anim\\bg_forest.X");
	ruins  = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Theater\\bg_anim\\bg_remains.X");*/
	model->SetPosition(0.0f, -23.5f, -5.0f);
	town->SetPosition(0.0f,-25.0f,20.0f);
	forest->SetPosition(0.0f, -25.0f, 20.0f);
	ruins->SetPosition(0.0f, -25.0f, 20.0f);
	/*model_forest->SetPosition(0.0f, -23.0, 0.0f);
	bg_forest->SetPosition(0, -25, 0);

	model_ruins->SetPosition(0.0f, -23.0, 0.0f);
	bg_ruins->SetPosition(0, -25, 0);

	model_town->SetPosition(0.0f, -23.0, 0.0f);
	bg_town->SetPosition(0, -25, 0);*/
	//bg_forest->SetPosition(0, -pos_y, 20.0f);
	pos = SimpleMath::Vector3::Zero;
}

/**
 * @fn 条件によってモーションを切り替える
 * @return なし
 * @detail 変数にdeltaTimeを代入して、条件によってモーションを切り替える
 *         (例)30フレーム　= 変数の値が0.3
 */
int Ground::Update(const float deltaTime) {
	
	auto a = model->GetPosition();
	return 0;
}

void Ground::Render() {
	model->Draw();
	//a->Draw();
	/*GetModel()->Draw();*/
}

/**
 * @fn モデルを渡す関数
 * @return 背景モデル
 * @detail シーンによって対応したモデルを返すようにする
 */


//MODEL型
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

