#include "AudianceManager.h"

void AudienceManager::LoadAssets() {

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	audience = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Audience\\StandingMan\\audience_stand.X");
	throw_things_lv2 = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Audience\\ThrowThings\\throw_lv2b.X");

	audience->SetPosition(-2, -15.0f, 25);
	throw_things_lv2->SetPosition(0, -12.0f, 25);

	col.lv2_box = throw_things_lv2->GetBoundingBox();
	col.lv2_box.Extents.x = col.lv2_box.Extents.x * 150;
	col.lv2_box.Extents.y = col.lv2_box.Extents.y * 150;
	col.lv2_box.Extents.z = col.lv2_box.Extents.z * 15;

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.lv2_box.Extents.x * 2,
		col.lv2_box.Extents.y * 2,
		col.lv2_box.Extents.z * 2
	);

	col.lv2_box.Center = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
	collision->SetPosition(INT_MAX, INT_MAX, INT_MAX);
	collision->SetScale(SimpleMath::Vector3::One);
	collision->SetMaterial(material);
}

int AudienceManager::Update(float appeal_time, bool cool_flag,bool special_flag, const float deltaTime) {

	delta = deltaTime;

	if (cool_flag && appeal_time >= 3.0f) {
			time = appeal_time;
	}

	if (special_flag) {
		SpecialAttackCollision(0.01f);
	}
	else {
		col.lv2_box.Center = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
		collision->SetPosition(INT_MAX, INT_MAX, INT_MAX);
		collision->SetScale(SimpleMath::Vector3::One);
	}


	if (time >= 3.0f) {
		if (throw_frame < max_throw) {
			SetAnimation(throw_things_lv2, FIRST);
			throw_things_lv2->AdvanceTime(deltaTime / 1.0f);
			throw_frame += deltaTime;
			throw_things_flag = true;
		}
		else {
			SpecialAttackCollision(0.1f);
		}
	}


	return 0;
}

void AudienceManager::SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack)
{
	for (int i = 0; i < MAX_MOTION; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}

void AudienceManager::SpecialAttackCollision(float max_col_time) {
	if (col_frame < max_col_time) {
		collision->SetPosition(fill_theater_pos);
		collision->SetScale(fill_theater_col);
		col_frame += delta;
		col.lv2_box.Center = fill_theater_pos;
	}
	else {
		col.lv2_box.Center = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
		collision->SetPosition(INT_MAX, INT_MAX, INT_MAX);
		collision->SetScale(SimpleMath::Vector3::One);
		col_frame = 0.0f;
		throw_frame = 0.0f;
		time = 0;
		throw_things_flag = false;
	}
}

void AudienceManager::Render() {
	DXTK->Direct3D9->AlphaBendEnable(true);
	audience->Draw();
	DXTK->Direct3D9->AlphaBendEnable(false);

	if (time >= 3.0f) {
		throw_things_lv2->Draw();
	}

//	collision->Draw();
}