#include "Base/pch.h"
#include "Base/dxtk.h"

#include "EnemyBase.h"
#include"MyClass/PlayerManager/PlayerManager.h"

bool EnemyBase::Initialize(SimpleMath::Vector3 speed, int hp)
{
	enemy_speed = speed;
	enemy_hp    = hp;
	return true;
}

void EnemyBase::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	position = initial_position;

	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
	model->SetScale(0.04f);
	model->SetPosition(position);
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

	box.Center = position;
}

int EnemyBase::Update(DX9::MODEL& ground, const float deltaTime) {

	return 0;
}

void EnemyBase::Damage() {
	enemy_hp--;
}

void EnemyBase::Render() {
	if (!PlayerManager::Instance().GetHitFlag())
		model->Draw();

	//collision->Draw();
}