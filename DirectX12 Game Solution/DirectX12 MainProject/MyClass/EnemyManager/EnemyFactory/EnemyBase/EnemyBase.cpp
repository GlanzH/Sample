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

	//!�A�j���[�V�������f���̍쐬
	if (enemy_tag == "S" || enemy_tag == "H") {
		anim_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
		anim_model->SetPosition(position);
		anim_model->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);

		//������鏀��
		anim_box = anim_model->GetBoundingBox();
		anim_box.Extents = SimpleMath::Vector3(anim_box.Extents) * 0.01f;

		//�R���W�������f���̍쐬
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
		//!���f���̍쐬
		model = DX9::Model::CreateFromFile(DXTK->Device9, model_name);
		model->SetPosition(position);
		model->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);

		//������鏀��
		col.box = model->GetBoundingBox();

		//�R���W�������f���̍쐬
		collision = DX9::Model::CreateBox(
			DXTK->Device9,
			col.box.Extents.x * 1.5,
			col.box.Extents.y * 1.5,
			col.box.Extents.z * 1.5
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
	}

	if (retreat_flg && parry_count < 30){
		position.x += 15.0f * deltaTime;
		parry_count++;
	} 
	else {
		retreat_flg = false;
		parry_count = 0;
	}

	LifeDeathDecision();

	return 0;
}

void EnemyBase::Damage(const float deltaTime,int damage) {
	enemy_hp -= damage;
	damage_flag = true;
}

bool EnemyBase::LifeDeathDecision() {
	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void EnemyBase::BulletParry() {
	bullet_parry_flag = true;
}

void EnemyBase::Retreat()
{
	retreat_flg = true;
}

void EnemyBase::Render() {
	if (enemy_tag == "S" || enemy_tag == "H") {
		anim_model->Draw();
		//anim_collision->Draw();
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

