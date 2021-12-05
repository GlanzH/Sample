#include "AudianceManager.h"

void AudienceManager::LoadAssets() {
	audience = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Audience\\StandingMan\\audience_stand.X");
	throw_things_lv2 = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Audience\\ThrowThings\\throw_lv2b.X");

	//audience->SetTexture(0,L"audience.png");

	//material.Diffuse = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 0.0f);
	//material.Ambient = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 0.0f);
	//material.Specular = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 0.0f);


	throw_things_lv2->SetPosition(0, -12.0f, 25);

	audience->SetPosition(-2, -15.0f, 25);
}

int AudienceManager::Update(float appeal_time,const float deltaTime) {

	//if(DXTK->KeyState->W)
	//time = appeal_time;

	//if (time >= 3.0f) {
	//	SetAnimation(throw_things_lv2, FIRST);
	//	throw_things_lv2->AdvanceTime(deltaTime / 1.0f);
	//	throw_things_flag = true;
	//}

	if (DXTK->KeyState->Z)
		throw_things_flag = true;
	else
		throw_things_flag = false;

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

void AudienceManager::Render() {
	audience->Draw();

	if (time > 3.0f) {
		
	}

	//throw_things_lv2->Draw();
}