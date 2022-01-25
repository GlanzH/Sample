#include "Ground.h"

void Ground::LoadAsset() {
<<<<<<< HEAD
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\Forest\\bg_remains.X");	
	model->SetPosition(0.0f, pos_y, 10.0f);
=======
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\BackGround\\stage.X");
	a = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\Forest\\bg_forest.X");
	model->SetPosition(0.0f, -23.0, 0.0f);
	//a->SetPosition(0, -25, 0);
	a->SetScale(0.4f);
	a->SetPosition(0, -pos_y, 20.0f);
	pos = SimpleMath::Vector3::Zero;
}

int Ground::Update(const float deltaTime) {
	if (DXTK->KeyState->J)
		pos.x -= 0.1f;

	if (DXTK->KeyState->U)
		pos.x += 0.1f;

	if (DXTK->KeyState->K)
		pos.y -= 0.1f;

	if (DXTK->KeyState->I)
		pos.y += 0.1f;

	if (DXTK->KeyState->L)
		pos.z -= 0.1f;

	if (DXTK->KeyState->O)
		pos.z += 0.1f;

	//SetAnimation(a, (int)Forest::PLAY, (int)Forest::MAX_MOTION);
	//a->AdvanceTime(deltaTime / 1.0f);
	//a->SetPosition(pos);
	auto a = model->GetPosition();
	return 0;
>>>>>>> 617062441bd5256eaf6981462a94e6c64b904a2f
}

void Ground::Render() {
	//model->Draw();
	//a->Draw();
}

void Ground::SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack, int max_motion)
{
	for (int i = 0; i < max_motion; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}

