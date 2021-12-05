#include "AudianceManager.h"

void AudienceManager::LoadAssets() {
	audience = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Audience\\StandingMan\\audience_stand.X");
	//audience->SetTexture(L"audience.png", DX9::Colors::Alpha(0.0f));
	//model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Audience\\ThrowThings\\throw_lv1.X");

	//model->SetScale(0.005f);
	//model->SetPosition(0, 15.0f, 50);
	//audience->SetTexture(L"Model\\Audience\\StandingMan\\audience.png");
	audience->SetPosition(-2, -15.0f, 25);
}

int AudienceManager::Update(const float deltaTime) {
	//	SetAnimation(throw_things_lv1, FIRST);

	//throw_things_lv1->AdvanceTime(deltaTime / 1.0f);
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
	//model->Draw();
}