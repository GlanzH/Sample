#include "Base/pch.h"
#include "Base/dxtk.h"

#include "EnemyBase.h"

bool EnemyBase::Initialize(SimpleMath::Vector3 speed, int hp)
{
	enemy_speed = speed;
	enemy_hp    = hp;
	return true;
}

void EnemyBase::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	position = initial_position;

	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
	model->SetPosition(position);
	model->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);

	model->SetScale(50.0f);
	
	box = model->GetBoundingBox();

	//boxの半径の大きさ変更
	box.Extents = SimpleMath::Vector3(box.Extents) * 0.01f;

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
	collision->SetScale(0.01f);

	box.Center = position;
}

int EnemyBase::Update(DX9::MODEL& ground, PlayerManager* player, const float deltaTime){

	//count = (count++) % 5;
	return 0;
}

void EnemyBase::Damage() {
	enemy_hp--;
}

void EnemyBase::Retreat() {
	model->SetPosition(position.x += 15.0f, position.y, position.z);

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
}

void EnemyBase::Render() {
		//if (count<2)
		//{
			model->Draw();
		//}

	collision->Draw();
}