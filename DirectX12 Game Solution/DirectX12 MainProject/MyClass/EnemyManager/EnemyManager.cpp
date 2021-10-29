#include "Base/pch.h"

#include "Base/dxtk.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	std::unique_ptr<EnemyBase*> base = std::make_unique<EnemyBase*>();
	
}

bool EnemyManager::Initialize()
{
	return true;
}

void EnemyManager::LoadAsset()
{
	
}

int EnemyManager::Update(DX9::MODEL& ground, const float deltaTime) 
{
	/*if (!PlayerManager::Instance().GetHitFlag())
		Move(ground, deltaTime);*/
	return 0;
}

//void EnemyManager::Move(DX9::MODEL& ground, const float deltaTime)
//  {
//	model->Move(0.0f, 0.0f, -15.0f * deltaTime);
//
//	float dist = FLT_MAX;
//	if (ground->IntersectRay(model->GetPosition() + Vector3(0, 100, 0), Vector3::Down, &dist))
//		model->Move(0.0f, 100.0f - dist, 0.0f);
//
//	if (model->GetPosition().x > -95.0f)
//		model->SetPosition(model->GetPosition());
//	else
//		model->SetPosition(init_pos);
//}

void EnemyManager::Render()
{
	
}