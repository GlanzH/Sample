#include "Base/pch.h"
#include "Base/dxtk.h"

#include "EnemyBase.h"
#include"MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/EnumManager/EnumManager.h"
bool EnemyBase::Initialize(SimpleMath::Vector3 Speed, int hp)
{
	
	return false;
}

void EnemyBase::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
	model->SetScale(0.04f);
	model->SetPosition(initial_position);
	model->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);

	box = model->GetBoundingBox();

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * 2,
		box.Extents.y * 2,
		box.Extents.z * 2
	);

	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	collision->SetMaterial(material);

	box.Center = initial_position;
}

int EnemyBase::Update(const float deltaTime) {
	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
	return LIVE;
}

void EnemyBase::Damage() {
	hp--;
}

void EnemyBase::Render() {
	if (!PlayerManager::Instance().GetHitFlag())
		for (int i = 0; i < 4; i++)
		{
			model->Draw();
		}
		

	//collision->Draw();
}