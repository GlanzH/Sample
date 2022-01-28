#include "AudianceManager.h"

void AudienceManager::LoadAssets() {
	audience = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Audience\\StandingMan\\audience_stand.X");
	audience->SetPosition(-2, -15.0f, 25);
}

int AudienceManager::Update(const float deltaTime)
{
	delta = deltaTime;

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
	DXTK->Direct3D9->AlphaBendEnable(true);
	audience->Draw();
	DXTK->Direct3D9->AlphaBendEnable(false);
}