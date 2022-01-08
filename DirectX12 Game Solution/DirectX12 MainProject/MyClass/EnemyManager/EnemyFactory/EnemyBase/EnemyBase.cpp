#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

bool EnemyBase::EffectInit() {
	DX12Effect.Initialize();
	hit  = DX12Effect.Create(L"Effect/EnemyEffect/hit/hit.efk");
	die  = DX12Effect.Create(L"Effect/EnemyEffect/die/die.efk");
	star = DX12Effect.Create(L"Effect/EnemyEffect/star/star.efk");
	love = DX12Effect.Create(L"Effect/AudienceEffect/heart/heart.efk");
	death_effect_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
	hit_effect_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
	return true;
}

bool EnemyBase::Initialize(std::string tag, bool time_stop_flag, int hp)
{
	enemy_tag   = tag;
	enemy_hp    = hp;

	enemy_stop_flag = time_stop_flag;
	retreat_flag    = false;
	
	return true;
}

void EnemyBase::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	position = initial_position;

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.0f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	//!�A�j���[�V�������f���̍쐬
	anim_model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, model_name);
	anim_model->SetPosition(position);

	//������鏀��
	col.box = anim_model->GetBoundingBox();
	col.box.Extents = SimpleMath::Vector3(col.box.Extents) * anim_adjust_extents_col;

	//�R���W�������f���̍쐬
	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.box.Extents.x * anim_box_size,
		col.box.Extents.y * anim_box_size,
		col.box.Extents.z * anim_box_size
	);

	collision->SetMaterial(material);

	//anim_collision->SetScale(anim_adjust_extents_col);
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

	//!�A�j���[�V�������f���̍쐬
	model = DX9::Model::CreateFromFile(DXTK->Device9, model_name);
	model->SetPosition(position);

	//������鏀��
	col.box = model->GetBoundingBox();

	//�R���W�������f���̍쐬
	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.box.Extents.x * anim_box_size,
		col.box.Extents.y * anim_box_size,
		col.box.Extents.z * anim_box_size
	);

	collision->SetMaterial(material);

	col.box.Center = position;
}

int EnemyBase::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime)
{
	delta      = deltaTime;
	player_pos = player;
	
	
	IsRetreat();

	if (position.z < 15.0f) {
		explode.Update(position, delta);

		//if (!reduce_audience_flag) {
		//	if(enemy_tag == "S")
		//		StatusManager::Instance().AddAudience(6);
	 //  else if (enemy_tag == "H")
		//		StatusManager::Instance().AddAudience(8);
		//	reduce_audience_flag = true;
		//}
	}

	StatusManager::Instance().CalcAudience(delta);

	return 0;
}

void EnemyBase::OnDeviceLost() {
	DX12Effect.Reset();
}

void EnemyBase::AnimModelRender() {
	anim_model->Draw();

	if (position.z < 15.0f)
		explode.Render();
	//anim_collision->Draw();
}

void EnemyBase::ModelRender() {
	model->Draw();
	collision->Draw();
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

void EnemyBase::EnemyAnimation() {
	//if (!IsDamage())
	//	SetAnimation(anim_model, WAIT);
	//else
	//	SetAnimation(anim_model, DAMAGE);

	//anim_model->AdvanceTime(delta / 1.0f);
}

void EnemyBase::HitEffect() {
	//if (enemy_hp > 0) {
		hit_effect_pos = position;

	//	DX12Effect.PlayOneShot("hit_eff", hit_effect_pos);
	//}
}

void EnemyBase::DeathEffect() {
	death_effect_pos = position;

	//if (death_effect_pos.z > 40)
	//	DX12Effect.PlayOneShot("die", death_effect_pos);
}

void EnemyBase::TimeStopDecision() {
	if (enemy_stop_flag)
		do_time_stop_flag = true;
}

void EnemyBase::Retreat() {
	retreat_flag = true;
}

void EnemyBase::IsRetreat() {
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
	enemy_hp -= 1;
}

bool EnemyBase::Stun() {
	if (enemy_hp == 1 && stun_frame < max_stun) {
		if (!DX12Effect.CheckAlive(star_handle))
			star_handle = DX12Effect.Play(star, position + SimpleMath::Vector3(0,10,0));
		stun_frame += delta;
		return true;
	}

	return false;
}