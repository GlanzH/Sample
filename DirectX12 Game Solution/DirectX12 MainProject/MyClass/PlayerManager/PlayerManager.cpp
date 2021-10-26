#include "Base/pch.h"
#include "Base/dxtk.h"
#include "PlayerManager.h"

void PlayerManager::Initialize() 
{

	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;

	//落下時
	V1 = gravity_ * jump_time_ * jump_time_;

}

void PlayerManager::LoadAssets() 
{

	DXTK->Direct3D9->SetRenderState(NormalizeNormals_Enable);
	DXTK->Direct3D9->SetRenderState(Specular_Enable);


	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Mikoto//mikoto.x");
	model->SetScale(0.04f);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, XMConvertToRadians(-90.0f), 0.0f);

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

}

int PlayerManager::Update(DX9::MODEL& ground, const float deltaTime)
{
	//地形の当たり判定
	float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() + SimpleMath::Vector3(0, 100, 0), SimpleMath::Vector3::Down, &dist)) {
		model->Move(0.0f, 100.0f - dist, 0.0f);
	}

	//モデル　アニメーション

	SetAnimation(model, Wait);


	//プレイヤー:移動
	if (DXTK->KeyState->Right||DXTK->KeyState->D) {
		model->Move(0.0f, 0.0f, -30.0f * deltaTime);
		SetAnimation(model, Walk);

	}
	if (DXTK->KeyState->Left||DXTK->KeyState->A) {
		model->Move(0.0f, 0.0f, 30.0f * deltaTime);
		SetAnimation(model, Walk);
	}

	//プレイヤー:ジャンプ
	//ジャンプ
	if (!jump_flag_) {
		if (DXTK->KeyEvent->pressed.Space) {
			jump_flag_ = true;
			jump_time_ = 0;
			jump_start_v_ = model->Position.y;
			SetAnimation(model, Jump);
		}

	}

	if (jump_flag_) {
		jump_time_ += deltaTime;
		auto pos = model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time_ - 0.5f * gravity_ * jump_time_ * jump_time_;
		model->SetPosition(pos);

		//ジャンプの終了判定
		if (V0 * jump_time_ < gravity_ * jump_time_ * jump_time_) {
			float dist = 0;
			if (ground->IntersectRay(
				model->GetPosition(),
				SimpleMath::Vector3::Up,
				&dist
			)) {
				model->Move(0.0f, dist, 0.0f);
				jump_flag_ = false;
			}

		}
	}

	//プレイヤー:攻撃
	if (DXTK->KeyEvent->pressed.J||DXTK->KeyEvent->pressed.F) {

	}

	//ランバージャック(移動制限)
	auto p_pos = model->GetPosition();
	model->SetPosition(p_pos);
	//p_pos = SimpleMath::Vector3(std::clamp(p_pos.x,  -100.0f,  100.0f),
	//	                        std::clamp(p_pos.y,     0.0f, 1000.0f),
	//	                        std::clamp(p_pos.z, -1000.0f, 1000.0f)
	//);

	return 0;
}

void PlayerManager::Render() 
{
	//プレイヤーの描画
	model->Draw();
}

void PlayerManager::_2DRender()
{

	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(0.0f, 0.0f),
		DX9::Colors::DarkBlue,
		L"%f %f" ,model->Position.x ,model->Position.y
	);
}

//指定されたモーションはTRUE,それ以外はFALSE
void PlayerManager::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}
