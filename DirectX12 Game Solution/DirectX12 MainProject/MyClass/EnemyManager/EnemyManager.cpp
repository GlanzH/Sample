#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyManager.h"

bool EnemyManager::Initialize() {
	return true;
}

void EnemyManager::LoadAsset() {
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Mikoto//mikoto.x");
	model->SetScale(0.04f);
	model->SetPosition(init_pos);
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

	box.Center = init_pos;
}

int EnemyManager::Update(DX9::MODEL& ground, const float deltaTime) {
	if (!player.GetHitFlag())
		Move(ground, deltaTime);
	return 0;
}

void EnemyManager::Move(DX9::MODEL& ground, const float deltaTime) {
	model->Move(0.0f, 0.0f, -15.0f * deltaTime);

	float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() + Vector3(0, 100, 0), Vector3::Down, &dist))
		model->Move(0.0f, 100.0f - dist, 0.0f);

	if (model->GetPosition().x > -95.0f)
		model->SetPosition(model->GetPosition());
	else
		model->SetPosition(init_pos);

	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + Vector3(0, 4, 0));
}

void EnemyManager::Render() {
	if(!player.GetHitFlag())
	model->Draw();
	
	//collision->Draw();
}