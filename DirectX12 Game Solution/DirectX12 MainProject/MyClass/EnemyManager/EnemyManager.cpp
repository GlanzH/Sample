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

int EnemyManager::Update(const float deltaTime, DX9::MODEL& ground)
{
	//model->Move(0.0f, 0.0f, 5.0f);
	//// ’nŒ`‚Ì‚‚³‚ð’²‚×‚é
	//	//FLT_MAX‚ÍfloatŒ^‚ÌÅ‘å”
     float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() +SimpleMath::Vector3(0, 100, 0), SimpleMath::Vector3::Down, &dist))
	{
		model->Move(0.0f, 100.0f - dist, 0.0f);
	}

	enemy_pos=model->GetPosition();
	return 0;
}

void EnemyManager::Render() 
{
	model->Draw();
}
