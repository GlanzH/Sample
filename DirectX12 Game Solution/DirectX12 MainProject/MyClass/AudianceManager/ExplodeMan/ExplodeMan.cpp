#include "ExplodeMan.h"

void ExplodeMan::LoadAssets(float x) {
	man = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Audience\\ExplodingMan\\audience_damege_bone.X");
	man->SetPosition(x, 0, 25);
}

int ExplodeMan::Update(SimpleMath::Vector3 position,const float deltaTime) {
	man->SetPosition(position.x,position.y,25.0f);

	SetAnimation(man, EXPLODE_MAN);
	man->AdvanceTime(deltaTime / 1.0f);
	return 0;
}

void ExplodeMan::Render() {
	man->Draw();
}

void ExplodeMan::SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack) {
	for (int i = 0; i < MAX_MOTION; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}