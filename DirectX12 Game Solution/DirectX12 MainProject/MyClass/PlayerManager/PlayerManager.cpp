#include "Base/pch.h"
#include "Base/dxtk.h"
#include "PlayerManager.h"

bool PlayerManager::Initialize() 
{
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;

	hit_flag = false;

	return 0;
}

void PlayerManager::LoadAssets() 
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Mikoto//mikoto.x");
	model->SetScale(model_scsle);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, XMConvertToRadians(model_rotetion), 0.0f);

	//プレイヤーの当たり判定
	box = model->GetBoundingBox();

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * box_size,
		box.Extents.y * box_size,
		box.Extents.z * box_size
	);
	collision->SetRotation(0.0f, XMConvertToRadians(model_rotetion), 0.0f);



	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	collision->SetMaterial(material);

	box.Center = player_pos;

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	DX12Effect.Initialize();
	Sword_Effect_ = DX12Effect.Create(L"Effect//Sword_Effect.efk");

}

int PlayerManager::Update(DX9::MODEL& ground,  const float deltaTime)
{
	//地形の当たり判定
	Player_collision_detection(ground);

	//モデル　アニメーション
	SetAnimation(model, Wait);

	//プレイヤー:移動
	Player_move(deltaTime);

	//プレイヤー:ジャンプ
	Player_jump(ground, deltaTime);


	//プレイヤー:攻撃
	if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F) {
		//当たり判定はIntersertsを使う
		//当たり判定をさせたいモデルのコリジョン.Interserts(相手モデルのコリジョン)
		
		//斬撃
		handle = DX12Effect.Play(Sword_Effect_);
		////今回の場合
		//if (box.Intersects(enemy->GetBox())) {
		//	//プレイヤーが的にあたったときのの処理
		//	//今回は、hit_flagをtrueにする
		//	hit_flag = true;
		//	enemy ->Damage();
		//}
	}


	//ランバージャック(移動制限)
	Player_limit();
	return 0;
}

void PlayerManager::Render() 
{
	//プレイヤーの描画
	model->Draw();

	//collision->Draw();
}

void PlayerManager::OnCollisionEnter(PlayerManager* player) {

}


//指定されたモーションはTRUE,それ以外はFALSE
void PlayerManager::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}

void PlayerManager::_2DRender()
{
	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(0.0f, 0.0f),
		DX9::Colors::DarkBlue,
		L"%f", model->Position.x
	);
}

void PlayerManager::Player_collision_detection(DX9::MODEL& ground)
{
	//地形の当たり判定
	float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() + SimpleMath::Vector3(0, collision_detection, 0), SimpleMath::Vector3::Down, &dist)) {
		model->Move(0.0f, collision_detection - dist, 0.0f);
	}

}

void PlayerManager::Player_move(const float deltaTime)
{
	//プレイヤー:移動(キーボード)
	if (DXTK->KeyState->Right || DXTK->KeyState->D||DXTK->GamePadState[0].dpad.right) {
		model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
		SetAnimation(model, Walk);

	}
	if (DXTK->KeyState->Left || DXTK->KeyState->A || DXTK->GamePadState[0].dpad.left) {
		model->Move(0.0f, 0.0f, player_speed_ * deltaTime);
		SetAnimation(model, Walk);
	}

	////プレイヤー(ゲームパッド)
	//SimpleMath::Vector3 movement = SimpleMath::Vector3(
	//	 DXTK->GamePadState[0].thumbSticks.leftX,
	//	-DXTK->GamePadState[0].thumbSticks.leftY,
	//	0.0f
	//);
	//const float SQUARE_X =  DXTK->GamePadState[0].thumbSticks.leftX;
	//const float SQUARE_Y = -DXTK->GamePadState[0].thumbSticks.leftY;

	//movement.x = SQUARE_X * sqrt(5.0f - 0.5 * SQUARE_Y * SQUARE_Y);
	//movement.y = SQUARE_Y * sqrt(5.0f - 0.5 * SQUARE_X * SQUARE_X);



}

void PlayerManager::Player_limit()
{
	//ランバージャック(移動制限)
	auto p_pos = model->GetPosition();
	p_pos = SimpleMath::Vector3(
		std::clamp(p_pos.x, -model_collision_detection_X,     model_collision_detection_X),
		std::clamp(p_pos.y,  model_collision_detection_Y_MIN, model_collision_detection_Y_MAX),
		std::clamp(p_pos.z, -model_collision_detection_Z,     model_collision_detection_Z)
	);
	model->SetPosition(p_pos);

	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));

}

void PlayerManager::Player_jump(DX9::MODEL& ground,const float deltaTime)
{
	//ジャンプ
	if (!jump_flag_) {
		if (DXTK->KeyEvent->pressed.Space||DXTK->GamePadEvent[0].a) {
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

		float dist = 0;
		if (ground->IntersectRay(
			model->GetPosition() + SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
			SimpleMath::Vector3::Up,
			&dist
		)) {
			model->Move(0.0f, dist, 0.0f);
			jump_flag_ = false;
		}


		//ジャンプの終了判定
		if (V0 * jump_time_ < gravity_ * jump_time_ * jump_time_) {
			float dist = 0;
			if (ground->IntersectRay(
				model->GetPosition() + SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
				SimpleMath::Vector3::Up,
				&dist
			)) {
				model->Move(0.0f, dist, 0.0f);
				jump_flag_ = false;
			}
		}
	}

}