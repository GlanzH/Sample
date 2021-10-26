#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyManager.h"

bool EnemyManager::Initialize()
{
	
	return true;
}

void EnemyManager::LoadAsset()
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Mikoto\\mikoto.x");
	model->SetScale(0.04f);
	model->SetPosition(enemy_pos);
	model->SetRotation(0.0f, XMConvertToRadians(-90.0f), 0.0f);
}

int EnemyManager::Update()
{
	model->Move(0.0f, 0.0f, 5.0f);
	//// 地形の高さを調べる
	//	//FLT_MAXはfloat型の最大数
	//	float dist = FLT_MAX;
	//if (/*地面のMODEL型変数*/->IntersectRay(/*プレイヤーのSKINNEDMODEL変数:*/->GetPosition() + Vector3(0, 100, 0), Vector3_Down, &dist)) {
	//	mikoto->Move(0.0f, 100.0f - dist, 0.0f);
	//}
	return 0;
}

void EnemyManager::Render() 
{
	model->Draw();
}