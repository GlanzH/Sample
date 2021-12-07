#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

bool EnemyBase::EffectInit() {
	DX12Effect.Initialize();
	DX12Effect.Create(L"Effect/EnemyEffect/hit/hit.efk", "hit_eff");
	DX12Effect.Create(L"Effect/EnemyEffect/die/die.efk", "die");
	death_effect_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
	hit_effect_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
	return true;
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

	//!アニメーションモデルの作成
	if (enemy_tag == "S" || enemy_tag == "H") {
		anim_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
		anim_model->SetPosition(position);
		anim_model->SetRotation(0.0f, XMConvertToRadians(anim_init_rotate), 0.0f);

		anim_model->SetScale(0.1f);

		//箱を作る準備
		anim_box = anim_model->GetBoundingBox();
		anim_box.Extents = SimpleMath::Vector3(anim_box.Extents);
		//anim_box.Extents = SimpleMath::Vector3(anim_box.Extents) * anim_adjust_extents_col;

		//コリジョンモデルの作成
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
		//!モデルの作成
		model = DX9::Model::CreateFromFile(DXTK->Device9, model_name);
		model->SetPosition(position);
		model->SetRotation(0.0f, XMConvertToRadians(init_rotate), 0.0f);

		//箱を作る準備
		col.box = model->GetBoundingBox();

		//コリジョンモデルの作成
		collision = DX9::Model::CreateBox(
			DXTK->Device9,
			col.box.Extents.x * box_size,
			col.box.Extents.y * box_size,
			col.box.Extents.z * box_size
		);

		collision->SetMaterial(material);

		col.box.Center = position;
	}

	explode.LoadAssets(initial_position.x);
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

	if (retreat_flg && retreat_count < max_retreat) {
		if (player.x < position.x)
			position.x += retreat_dist * deltaTime;
		else
			position.x -= retreat_dist * deltaTime;

		retreat_count++;
	}
	else {
		retreat_flg = false;
		retreat_count = 0;
	}

	if (position.z < 15.0f) {
		explode.Update(position, delta);

		if (!reduce_audience_flag) {
			if(enemy_tag == "S")
				StatusManager::Instance().AddAudience(3);
	   else if (enemy_tag == "H")
				StatusManager::Instance().AddAudience(5);
			reduce_audience_flag = true;
		}
	}

	StatusManager::Instance().DownAudience(delta);

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

void EnemyBase::HitEffect() {
	//if (enemy_hp > 0) {
		hit_effect_pos = position;
		DX12Effect.PlayOneShot("hit_eff", hit_effect_pos);
	//}
}

void EnemyBase::DeathEffect() {
	death_effect_pos = position;

	if (death_effect_pos.z > 40)
		DX12Effect.PlayOneShot("die", death_effect_pos);
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
	if (enemy_tag == "S" || enemy_tag == "H") {
		if (enemy_hp < 0 && dead_frame < max_dead) {
			if (dead_frame == 0.0f)
				Retreat();

			SetAnimation(anim_model, DAMAGE);
			anim_model->AdvanceTime(delta / 1.0f);

			dead_frame += delta;
		}
		else if (enemy_hp < 0 && dead_frame > max_dead) {
			return DEAD;
		}
	}
	else {
		if (enemy_hp < 0) 
			return DEAD;
	}

	 if (position.z <= 15.0f && auto_destroy_frame < max_auto_destroy) {
		 auto_destroy_frame += delta;
	 }
	 else if (position.z <= 15.0f && auto_destroy_frame > max_auto_destroy) {
		return AUTO;
 	 }

	return LIVE;
}

void EnemyBase::Retreat(){
	retreat_flg = true;
}

void EnemyBase::Render() {
	if (enemy_tag == "S" || enemy_tag == "H") {
		anim_model->Draw();

		if (position.z < 15.0f)
			explode.Render();
		//anim_collision->Draw();
	}
	else {
		model->Draw();
		//collision->Draw();
	}
}