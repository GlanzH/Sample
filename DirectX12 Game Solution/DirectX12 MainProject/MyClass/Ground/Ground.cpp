#include "Ground.h"

void Ground::LoadAsset() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\BackGround\\stage.X");
	a = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\Theater\\Forest\\bg_forest.X");
	model->SetPosition(0.0f, -23.0, 0.0f);
	a->SetPosition(0, -25, 0);
	//a->SetScale(0.4f);
	a->SetPosition(0, -pos_y, 20.0f);
	pos = SimpleMath::Vector3::Zero;
}

/**
 * @fn 条件によってモーションを切り替える
 * @return なし
 * @detail 変数にdeltaTimeを代入して、条件によってモーションを切り替える
 *         (例)30フレーム　= 変数の値が0.3
 */
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
	//if (ウェーブ数＞ = 0 && ウェーブ数 ＜ = 3)
	//	街の背景モーションを再生する関数

	//	if (ウェーブ数＞ = 4 && ウェーブ数 ＜ = 6)
	//		森の背景モーションを再生する関数

	//		if (ウェーブ数＞ = 7 && ウェーブ数 ＜ = 9)
	//			遺跡の背景モーションを再生する関数

	//SetAnimation(a, (int)Forest::PLAY, (int)Forest::MAX_MOTION);
	//a->AdvanceTime(deltaTime / 1.0f);
	//a->SetPosition(pos);
	auto a = model->GetPosition();
	return 0;
}

void Ground::Render() {
	//model->Draw();
	//a->Draw();
}

/**
 * @fn モデルを渡す関数
 * @return 背景モデル
 * @detail シーンによって対応したモデルを返すようにする
 */

//DX9::SKINNEDMODEL& Ground::GetModel() {
//	
//	return town;
//	//return forest;
//	//return ruins;
//}

void Ground::SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack, int max_motion)
{
	for (int i = 0; i < max_motion; i++)
	{
		model->SetTrackEnable(i, FALSE);
		model->SetTrackEnable(enabletack, TRUE);
	}
}

