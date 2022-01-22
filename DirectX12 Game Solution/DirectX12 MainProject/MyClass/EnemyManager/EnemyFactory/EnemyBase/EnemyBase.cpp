#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/ResourceManager/ResourceManager.h"
#include "EnemyBase.h"

bool EnemyBase::Initialize(
	std::string tag, double init_wait,double stop_pos, std::string time_stop_flag,
	double speed,std::string direct ,std::string posture, int hp
)
{
	enemy_tag     = tag;
	enemy_hp      = hp;
	enemy_stop    = stop_pos;
	enemy_direct  = direct;
	enemy_posture = posture;
	move_speed    = speed;
	max_init_wait = init_wait;


	enemy_stop_flag = time_stop_flag;
	retreat_flag    = false;
	
	hit          = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/hit/hit.efk");
	normal_die   = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/confetti/confetti.efk");
	//special_die  = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/die2/die2.efk");
	star		 = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/star/star.efk");
	love		 = ResourceManager::Instance().LoadEffect(L"Effect/AudienceEffect/heart/heart.efk");

	return true;
}

void EnemyBase::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	position = initial_position;

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.0f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	//!アニメーションモデルの作成
	anim_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
	anim_model->SetPosition(position);

	//箱を作る準備
	col.box = anim_model->GetBoundingBox();
	col.box.Extents = SimpleMath::Vector3(col.box.Extents) * anim_adjust_extents_col;

	//コリジョンモデルの作成
	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.box.Extents.x * box_size,
		col.box.Extents.y * 5,
		col.box.Extents.z * box_size
	);

	collision->SetMaterial(material);
	col.box.Center = position;

	explode.LoadAssets(initial_position.x);

}

void EnemyBase::LoadModel(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	position = initial_position;
	init_pos = initial_position;

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.0f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	//!アニメーションモデルの作成
	model = DX9::Model::CreateFromFile(DXTK->Device9, model_name);
	model->SetPosition(position);

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

int EnemyBase::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime)
{
	delta      = deltaTime;
	player_pos = player;
	
	IsDamage();
	IsRetreat();

	if (position.z < 15.0f) {
		explode.Update(position, delta);
	}

	return 0;
}

void EnemyBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack, int max_motion)
{
	for (int i = 0; i < max_motion; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}

void EnemyBase::AdjustAnimCollision() {
	col.box.Center = anim_model->GetPosition();
	anim_model->SetPosition(position);
	anim_model->AdvanceTime(delta / 1.0f);
	collision->SetPosition(anim_model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}

void EnemyBase::HitEffect() {
	//if (enemy_hp > 0) {

	if (!DX12Effect.CheckAlive(hit_handle))
		hit_handle = DX12Effect.Play(hit, SimpleMath::Vector3(position.x , position.y ,200));
	//}
}

void EnemyBase::NormalDeathEffect() {
		normal_die_handle = DX12Effect.Play(normal_die, position);
}

void EnemyBase::SpecialDeathEffect() {
	//if (enemy_hp <= 0)
	//	special_die_handle = DX12Effect.Play(special_die, position);
}

void EnemyBase::TimeStopDecision() {
	if (enemy_stop_flag == "T")
		do_time_stop_flag = true;
}

void EnemyBase::Retreat() {
	retreat_flag = true;
}

void EnemyBase::IsRetreat() {
	if(enemy_hp <= 0)
		return;

	if (retreat_flag && retreat_count < max_retreat) {
		if (player_pos.x < position.x)
			position.x += retreat_dist * delta;
		else
			position.x -= retreat_dist * delta;

		retreat_count++;
	}
	else {
		retreat_flag = false;
		retreat_count = 0;
	}
}

void EnemyBase::Damage() {
	if (!damage_flag) {
		enemy_hp -= 1;
		damage_flag = true;
	}
}

void EnemyBase::IsDamage() {
	if (damage_flag) {
		if (damage_frame < max_damage) {
			damage_frame += delta;
		}
		else {
			damage_frame = 0.0f;
			damage_flag = false;
		}
	}
}

void EnemyBase::TemporaryDeath(float max_death) {
	if (enemy_hp <= 0) {
		temporary_death_flag = true;

		if (!DX12Effect.CheckAlive(star_handle))
			star_handle = DX12Effect.Play(star, position + SimpleMath::Vector3(0, 8, 0));
	}
	else {
		temporary_death_flag = false;
	}
	if (DXTK->KeyEvent->pressed.X) {
		//仮死状態解除するやつ
		DX12Effect.Stop(star_handle);
		enemy_hp = 1;
		death_frame = 0.0f;
		temporary_death_flag = false;
	}

	if (DXTK->KeyEvent->pressed.C) {
		DX12Effect.Stop(star_handle);
	}
}

bool EnemyBase::Stun() {
	if (enemy_hp == 1 && stun_frame < max_stun) {

	if (!DX12Effect.CheckAlive(star_handle))
		star_handle = DX12Effect.Play(star, position + SimpleMath::Vector3(0, 10, 0));

		stun_frame += delta;
		return true;
	}

	if(enemy_hp <= 0)
		DX12Effect.Stop(star_handle);

	return false;
}