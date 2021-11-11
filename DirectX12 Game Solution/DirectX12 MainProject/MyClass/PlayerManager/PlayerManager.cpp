#include "Base/pch.h"
#include "Base/dxtk.h"
#include "PlayerManager.h"

bool PlayerManager::Initialize()
{
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;


	return 0;
}

void PlayerManager::LoadAssets()
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"motion\\playler_motion.X");
	model->SetScale(model_scsle);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, XMConvertToRadians(model_rotetion), 0.0f);

	//プレイヤーの当たり判定
	box = model->GetBoundingBox();

	box.Extents = SimpleMath::Vector3(box.Extents) * 0.01f;

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * box_size,
		box.Extents.y * box_size,
		box.Extents.z * 1
	);
	collision->SetRotation(0.0f, XMConvertToRadians(model_rotetion), 0.0f);

	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	collision->SetMaterial(material);

	box.Center = player_pos;


	sword_box = model->GetBoundingBox();

	sword_box.Extents = SimpleMath::Vector3(sword_box.Extents) * 0.001f;

	sword_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		sword_box.Extents.x * box_size,
		sword_box.Extents.y * box_size,
		sword_box.Extents.z * box_size
	);


	sword_collision->SetScale(10, 10, 1);
	sword_box.Center = model->GetPosition() + SimpleMath::Vector3(15, 0, 0);


	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	DX12Effect.Initialize();
	Sword_Effect_ = DX12Effect.Create(L"Effect//Effect//Sword_Effect.efk");

}

int PlayerManager::Update(DX9::MODEL& ground, const float deltaTime)
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
	Player_attack();

	//ランバージャック(移動制限)
	Player_limit();

	//パリィ
	Parry();

	sword_box.Center = model->GetPosition();

	//if(DXTK->KeyState->Left)
	sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-8, 6, 0));
	//else if(DXTK->KeyState->Right)
	//	sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(8, 6, 0));

	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-0.5, 4, 0));
	model->AdvanceTime(deltaTime / 1.0f);
	return 0;
}

void PlayerManager::Render()
{
	//プレイヤーの描画
	model->Draw();

	//collision->Draw();
	//sword_collision->Draw();
}

void PlayerManager::OnCollisionEnter() {
	//敵に当たったときの処理

	box.Center = model->GetPosition();
	model->SetPosition(player_pos);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 4, 0));
	SetAnimation(model, Damage);
	//float dist = 0;
	//if (ground->IntersectRay(
	//	model->GetPosition() + SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
	//	SimpleMath::Vector3::Up,
	//	&dist
	//)) {
	//	model->Move(0.0f, dist, 0.0f);
	//}
	invincible_flag = true;
	invincible_count++;


	if (invincible_count >= invincible_count_max) {
		invincible_flag = false;
		invincible_count = 0;
	}
}

void PlayerManager::OnParryArea() {
	//パリィ成功時の処理


}

void PlayerManager::Parry() {
	if (DXTK->KeyEvent->pressed.P || DXTK->GamePadEvent->b) {
		if (parry_count < max_parry_count) {
			parry_count++;
			SetAnimation(model, Parry_);
			parry_flag = true;
		}
		else
			parry_flag = false;
	}
	else
		parry_count = 0;
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
	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(0.0f, 0.0f),
	//	DX9::Colors::DarkBlue,
	//	L"%f", model->Position.x
	//);

	//if (!parry_flag) {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 0.0f),
	//		DX9::Colors::Black,
	//		L"あ"
	//	);
	//}
	//else {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 0.0f),
	//		DX9::Colors::Black,
	//		L"い"
	//	);
	//}
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
	if (DXTK->KeyState->Right || DXTK->KeyState->D || DXTK->GamePadState[0].dpad.right) {
		model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
		model->SetRotation(0.0f, XMConvertToRadians(model_rotetion), 0.0f);
		SetAnimation(model, Run);

	}
	if (DXTK->KeyState->Left || DXTK->KeyState->A || DXTK->GamePadState[0].dpad.left) {
		model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
		model->SetRotation(0.0f, XMConvertToRadians(-model_rotetion), 0.0f);
		SetAnimation(model, Run);

	}

}

void PlayerManager::Player_limit()
{
	//ランバージャック(移動制限)
	auto p_pos = model->GetPosition();
	p_pos = SimpleMath::Vector3(
		std::clamp(p_pos.x, -model_collision_detection_X, model_collision_detection_X),
		std::clamp(p_pos.y, model_collision_detection_Y_MIN, model_collision_detection_Y_MAX),
		std::clamp(p_pos.z, -model_collision_detection_Z, model_collision_detection_Z)
	);
	model->SetPosition(p_pos);
}

void PlayerManager::Player_jump(DX9::MODEL& ground, const float deltaTime)
{
	//ジャンプ
	if (!jump_flag_) {
		if (DXTK->KeyEvent->pressed.Space || DXTK->GamePadEvent[0].a) {
			jump_flag_ = true;
			jump_time_ = 0;
			jump_start_v_ = model->Position.y;

		}
	}

	if (jump_flag_) {

		jump_time_ += deltaTime;
		auto pos = model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time_ - 0.5f * gravity_ * jump_time_ * jump_time_;
		model->SetPosition(pos);
		SetAnimation(model, Jump);


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

void PlayerManager::Player_attack() {
	//プレイヤー:攻撃
	if (IsAttack()) {


		//当たり判定はIntersertsを使う
		//当たり判定をさせたいモデルのコリジョン.Interserts(相手モデルのコリジョン)

		//斬撃
		SetAnimation(model, Attack_S);
		handle = DX12Effect.Play(Sword_Effect_);
		DX12Effect.SetPosition(handle, Vector3(6, -7, 0));
		//if (box.Intersects(->GetBox())) {
		//	//攻撃が当たったら１ダメージを与える
		//	//敵のHPは3なので成功すれば三発で倒れる
		//	EnemyBase＊型の変数->Damage();
		//}
	}

}

bool PlayerManager::IsAttack() {
	if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent->x)
		return true;

	return false;

}