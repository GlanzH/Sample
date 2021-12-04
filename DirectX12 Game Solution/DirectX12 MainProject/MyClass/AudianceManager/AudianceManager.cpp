#include "AudianceManager.h"

void AudienceManager::LoadAssets() {
	audience = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Audience\\StandingMan\\audience_stand.X");
	audience->SetPosition(-2, -15.0f, 25);
}

int AudienceManager::Update() {
	return 0;
}

void AudienceManager::Render() {
	audience->Draw();
}