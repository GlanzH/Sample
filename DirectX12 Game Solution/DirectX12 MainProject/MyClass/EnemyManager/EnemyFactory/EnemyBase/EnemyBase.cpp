#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/ResourceManager/ResourceManager.h"
#include "EnemyBase.h"

bool EnemyBase::Initialize(
	std::string tag, double init_wait, double stop_pos,
	double speed, std::string direct, std::string posture, int enemy_hp)
{
	enemy_tag = tag;
	init_hp = enemy_hp;
	enemy_stop = stop_pos;
	enemy_direct = direct;
	enemy_posture = posture;
	move_speed = speed;
	max_init_wait = init_wait;

	retreat_flag = false;
	damage_flag  = false;
	die_flag     = false;
	attack_flag  = false;
	dest_flag    = false;

	temporary_death_flag = false;
	confetti_effect_flag = false;
	death_effect_flag    = false;

	retreat_count = 0;
	effect_count  = 0;

	dead_frame         = 0.0f;
	is_damage          = 0.0f;
	init_wait_frame    = 0.0f;
	death_frame        = 0.0f;
	auto_destroy_frame = 0.0f;
	damage_frame       = 0.0f;

	return true;
}

void EnemyBase::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	position = initial_position;

	//!�A�j���[�V�������f���̍쐬(���������̌����H)(���񏈗����ꂽ�肷��Ȃ�)
	anim_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
	anim_model->SetPosition(position);

	//������鏀��
	col.box = anim_model->GetBoundingBox();
	col.box.Extents = SimpleMath::Vector3(col.box.Extents) * anim_adjust_extents_col;

	//�R���W�������f���̍쐬
	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.box.Extents.x * box_size,
		col.box.Extents.y * 10,
		col.box.Extents.z * box_size
	);

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.0f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	collision->SetMaterial(material);
	col.box.Center = position;
	hit        = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/hit/hit.efk");
	star       = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/star/star.efk");
	del        = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/delete/delete.efk");
	confetti   = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/confetti/confetti.efk");
	normal_die = ResourceManager::Instance().LoadEffect(L"Effect/EnemyEffect/die/die.efk");
}

void EnemyBase::LoadModel(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	position = initial_position;
	init_pos = initial_position;

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.0f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	//!���f���̍쐬
	model = DX9::Model::CreateFromFile(DXTK->Device9, model_name);
	model->SetPosition(position);

	//������鏀��
	col.box = model->GetBoundingBox();

	//�R���W�������f���̍쐬
	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.box.Extents.x * box_size,
		col.box.Extents.y * box_size,
		col.box.Extents.z
	);

	collision->SetMaterial(material);

	col.box.Center = position;
}

int EnemyBase::Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime)
{
	delta = deltaTime;
	player_pos = player;
	dest_flag = destroy_flag;

	IsDamage();
	IsRetreat();

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
}

void EnemyBase::HitEffect() {
	//if (enemy_hp > 0) {
	if (enemy_hp >= 0) {
		if (!DX12Effect.CheckAlive(hit_handle))
			hit_handle = DX12Effect.Play(hit, SimpleMath::Vector3(position.x, position.y, 200));
	}
	//}
}

void EnemyBase::NormalDeathEffect(float max_death, bool confetti_effect, bool death_effect, int effect_count) {
	if (die_flag) {
		if (dead_frame < max_death) {
			if (!DX12Effect.CheckAlive(confetti_handle) && confetti_effect && effect_count == CONFINETTI)
				confetti_handle = DX12Effect.Play(confetti, position);

			if (!DX12Effect.CheckAlive(die_handle) && death_effect && effect_count == DEATH)
				die_handle = DX12Effect.Play(normal_die, position);

			dead_frame += delta;
		}
	}
}

void EnemyBase::AutoDestoryEffect() {
	if (!DX12Effect.CheckAlive(del_handle))
		del_handle = DX12Effect.Play(del, position);
}

void EnemyBase::Retreat() {
	retreat_flag = true;
}

void EnemyBase::DieFlag() {
	if (enemy_hp <= 0)
		die_flag = true;
}

void EnemyBase::IsRetreat() {
	if (enemy_hp <= 0)
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
		enemy_hp--;
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

void EnemyBase::TemporaryDeath() {
	if (!temporary_death_flag && enemy_hp <= 0) {
		StatusManager::Instance().AddHitCombo();
		StatusManager::Instance().AddHitComboTime();
	}

	if (enemy_hp <= 0 && !die_flag) {
		temporary_death_flag = true;

		if (!DX12Effect.CheckAlive(star_handle))
			star_handle = DX12Effect.Play(star, position + SimpleMath::Vector3(0, 8, 0));
	}

	if (temporary_death_flag && StatusManager::Instance().GetHitComboTime() == 0.0f) {
		//������ԉ���������
		DX12Effect.Stop(star_handle);
		enemy_hp = init_hp;
		death_frame = 0.0f;
		temporary_death_flag = false;
	}
}

bool EnemyBase::FrontFlag() {
	if (position.x > player_pos.x && direct == RIGHT ||
		position.x < player_pos.x && direct == LEFT)
		return true;

	return false;
}