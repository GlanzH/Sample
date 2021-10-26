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
	//// �n�`�̍����𒲂ׂ�
	//	//FLT_MAX��float�^�̍ő吔
	//	float dist = FLT_MAX;
	//if (/*�n�ʂ�MODEL�^�ϐ�*/->IntersectRay(/*�v���C���[��SKINNEDMODEL�ϐ�:*/->GetPosition() + Vector3(0, 100, 0), Vector3_Down, &dist)) {
	//	mikoto->Move(0.0f, 100.0f - dist, 0.0f);
	//}
	return 0;
}

void EnemyManager::Render() 
{
	model->Draw();
}