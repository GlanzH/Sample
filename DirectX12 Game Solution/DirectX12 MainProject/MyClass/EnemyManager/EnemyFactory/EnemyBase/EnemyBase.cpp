#include "Base/pch.h"
#include "Base/dxtk.h"

#include "EnemyBase.h"

EnemyBase::EnemyBase()
{

}

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
	


	//” ‚ðì‚é€”õ
	box = model->GetBoundingBox();

	//ƒRƒŠƒWƒ‡ƒ“ƒ‚ƒfƒ‹‚Ìì¬
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

void EnemyBase::Damage(const float deltaTime,int damage) {
	//model->AdvanceTime(deltaTime / 1.0f);
	//SetAnimesion(model, DAMAGE);
	enemy_hp -= damage;
}

void EnemyBase::Retreat() {
	model->SetPosition(position.x += 15.0f, position.y, position.z);

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
}

void EnemyBase::Render() {
	model->Draw();

	//collision->Draw();
}
void EnemyBase::SetAnimesion(DX9::SKINNEDMODEL& model, const int enabletack)
{
	for (int i = 0; i < MAX_MOSION; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}

