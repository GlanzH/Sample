#include "Base/pch.h"
#include "Base/dxtk.h"

#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

bool EnemyBase::Initialize(std::string tag,SimpleMath::Vector3 speed, int hp)
{
	enemy_tag   = tag;
	enemy_speed = speed;
	enemy_hp    = hp;
	retreat_flg = false;
	
	return true;
}

void EnemyBase::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	position = initial_position;

	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	//!アニメーションモデルの作成
	if (enemy_tag == "S" || enemy_tag == "H") {
		anim_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
		anim_model->SetPosition(position);
		anim_model->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);

		//箱を作る準備
		anim_box = anim_model->GetBoundingBox();
		anim_box.Extents = SimpleMath::Vector3(anim_box.Extents) * 0.01f;

		//コリジョンモデルの作成
		anim_collision = DX9::Model::CreateBox(
			DXTK->Device9,
			anim_box.Extents.x * 2,
			anim_box.Extents.y * 2,
			anim_box.Extents.z * 2
		);

		anim_collision->SetMaterial(material);

		anim_collision->SetScale(0.01);
		anim_box.Center = position;
	}
	else {
		//!モデルの作成
		model = DX9::Model::CreateFromFile(DXTK->Device9, model_name);
		model->SetPosition(position);
		model->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);

		//箱を作る準備
		col.box = model->GetBoundingBox();

		//コリジョンモデルの作成
		collision = DX9::Model::CreateBox(
			DXTK->Device9,
			col.box.Extents.x * 2,
			col.box.Extents.y * 2,
			col.box.Extents.z * 2
		);

		collision->SetMaterial(material);

		col.box.Center = position;
	}
}

int EnemyBase::Update(SimpleMath::Vector3 player, const float deltaTime)
{
	if (enemy_tag == "S" || enemy_tag == "H") {
		anim_box.Center = anim_model->GetPosition();
		anim_model->SetPosition(position);
		anim_collision->SetPosition(anim_model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
	}
	else {
		col.box.Center = model->GetPosition();
		model->SetPosition(position);
		collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
	}

	if (retreat_flg && parry_count < 30){
		position.x += 15.0f * deltaTime;
		//if (enemy_tag == "S" || enemy_tag == "H") {

		//}

		parry_count++;
	} 
	else {
		retreat_flg = false;
		parry_count = 0;
	}
	return 0;
}

void EnemyBase::Damage(const float deltaTime,int damage) {
	enemy_hp -= damage;
	IsDamage();
}

bool EnemyBase::IsDamage() {
	if (damage_count < 30) {
		count++;
		return true;
	}
	else {
		count = 0;
		return false;
	}
}

void EnemyBase::Retreat()
{
	retreat_flg = true;
	//model->SetPosition(position.x += 15.0f, position.y, position.z);

	//box.Center = model->GetPosition();
	//model->SetPosition(position);
	//collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
}

void EnemyBase::Render() {
	if (enemy_tag == "S" || enemy_tag == "H") {
		anim_model->Draw();
		anim_collision->Draw();
	}
	else {
		model->Draw();
		//collision->Draw();
	}
}
void EnemyBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack)
{
	for (int i = 0; i < MAX_MOTION; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}

