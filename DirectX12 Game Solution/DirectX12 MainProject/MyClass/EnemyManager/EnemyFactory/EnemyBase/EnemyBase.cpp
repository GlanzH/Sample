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

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	//!�A�j���[�V�������f���̍쐬
	if (enemy_tag == "S" || enemy_tag == "H") {
		anim_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
		anim_model->SetPosition(position);
		anim_model->SetRotation(0.0f, XMConvertToRadians(anim_init_rotate), 0.0f);

		anim_model->SetScale(0.01f);

		//������鏀��
		anim_box = anim_model->GetBoundingBox();
		anim_box.Extents = SimpleMath::Vector3(anim_box.Extents);
		//anim_box.Extents = SimpleMath::Vector3(anim_box.Extents) * anim_adjust_extents_col;

		//�R���W�������f���̍쐬
		anim_collision = DX9::Model::CreateBox(
			DXTK->Device9,
			anim_box.Extents.x * anim_box_size,
			anim_box.Extents.y * anim_box_size,
			anim_box.Extents.z * anim_box_size
		);

		anim_collision->SetMaterial(material);

		//anim_collision->SetScale(anim_adjust_extents_col);
		anim_box.Center = position;
	}
	else {
		//!���f���̍쐬
		model = DX9::Model::CreateFromFile(DXTK->Device9, model_name);
		model->SetPosition(position);
		model->SetRotation(0.0f, XMConvertToRadians(init_rotate), 0.0f);

		//������鏀��
		col.box = model->GetBoundingBox();

		//�R���W�������f���̍쐬
		collision = DX9::Model::CreateBox(
			DXTK->Device9,
			col.box.Extents.x * box_size,
			col.box.Extents.y * box_size,
			col.box.Extents.z * box_size
		);

		collision->SetMaterial(material);

		col.box.Center = position;
	}
}

int EnemyBase::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime)
{
	delta = deltaTime;

	if (enemy_tag == "S" || enemy_tag == "H") {
		EnemyAnimation();
		anim_box.Center = anim_model->GetPosition();
		anim_model->SetPosition(position);
		anim_collision->SetPosition(anim_model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
	}
	else {
		col.box.Center = model->GetPosition();
		model->SetPosition(position);
	}

	if (retreat_flg && retreat_count < max_retreat){
		if(player.x < position.x)
			position.x += retreat_dist * deltaTime;
		else
			position.x -= retreat_dist * deltaTime;

		retreat_count++;
	} 
	else {
		retreat_flg   = false;
		retreat_count = 0;
	}

	LifeDeathDecision();

	return 0;
}

void EnemyBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack)
{
	for (int i = 0; i < MAX_MOTION; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}

void EnemyBase::EnemyAnimation() {
	if (!IsDamage())
		SetAnimation(anim_model, WAIT);
	else
		SetAnimation(anim_model, DAMAGE);

	anim_model->AdvanceTime(delta / 1.0f);
}

void EnemyBase::Damage(int damage) {
	enemy_hp -= damage;
	damage_flag = true;
}

bool EnemyBase::IsDamage() {
	if (damage_flag && damage_frame < max_damage_frame) {
		damage_frame += delta;
		return true;
	}
	else {
		damage_frame = 0.0f;
		damage_flag = false;
		return false;
	}
}

bool EnemyBase::LifeDeathDecision() {
	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
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

