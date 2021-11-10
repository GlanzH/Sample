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

	//�v���C���[�̓����蔻��
	box = model->GetBoundingBox();

	//box.Extents = SimpleMath::Vector3(box.Extents);

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

	sword_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * 22,
		box.Extents.y * 4,
		box.Extents.z * 20
	);


	sword_box.Center = model->GetPosition() + SimpleMath::Vector3(6, 0, 0);


	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	DX12Effect.Initialize();
	Sword_Effect_ = DX12Effect.Create(L"Effect//Effect//Sword_Effect.efk");

}

int PlayerManager::Update(DX9::MODEL& ground,  const float deltaTime)
{
	//�n�`�̓����蔻��
	Player_collision_detection(ground);

	//���f���@�A�j���[�V����
	SetAnimation(model, Wait);

	//�v���C���[:�ړ�
	Player_move(deltaTime);

	//�v���C���[:�W�����v
	Player_jump(ground, deltaTime);


	//�v���C���[:�U��
	Player_attack();

	//�����o�[�W���b�N(�ړ�����)
	Player_limit();

	//�p���B
	Parry();

	sword_box.Center = model->GetPosition() + SimpleMath::Vector3(6, 0, 0);
	sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(5, 6, 0));


	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-0.5, 4, 0));
	model->AdvanceTime(deltaTime/1.0f);
	return 0;
}

void PlayerManager::Render() 
{
	//�v���C���[�̕`��
	model->Draw();

	collision->Draw();
	sword_collision->Draw();
}

void PlayerManager::OnCollisionEnter() {
	//�G�ɓ��������Ƃ��̏���
		
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
	//�p���B�������̏���
	SetAnimation(model, Parry_);

}

void PlayerManager::Parry() {
	if (DXTK->KeyEvent->pressed.P||DXTK->GamePadEvent->b) {
		if (parry_count < max_parry_count) {
			parry_count++;
			parry_flag = true;
		}
		else
			parry_flag = false;
	}
	else
		parry_count = 0;
}

//�w�肳�ꂽ���[�V������TRUE,����ȊO��FALSE
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
	//		L"��"
	//	);
	//}
	//else {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 0.0f),
	//		DX9::Colors::Black,
	//		L"��"
	//	);
	//}
}

void PlayerManager::Player_collision_detection(DX9::MODEL& ground)
{
	//�n�`�̓����蔻��
	float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() + SimpleMath::Vector3(0, collision_detection, 0), SimpleMath::Vector3::Down, &dist)) {
		model->Move(0.0f, collision_detection - dist, 0.0f);
	}

}

void PlayerManager::Player_move(const float deltaTime)
{
	//�v���C���[:�ړ�(�L�[�{�[�h)
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
	//�����o�[�W���b�N(�ړ�����)
	auto p_pos = model->GetPosition();
	p_pos = SimpleMath::Vector3(
		std::clamp(p_pos.x, -model_collision_detection_X,     model_collision_detection_X),
		std::clamp(p_pos.y,  model_collision_detection_Y_MIN, model_collision_detection_Y_MAX),
		std::clamp(p_pos.z, -model_collision_detection_Z,     model_collision_detection_Z)
	);
	model->SetPosition(p_pos);
}

void PlayerManager::Player_jump(DX9::MODEL& ground, const float deltaTime)
{
	//�W�����v
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


		//�W�����v�̏I������
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
	//�v���C���[:�U��
	if (IsAttack()) {
	

		//�����蔻���Interserts���g��
		//�����蔻��������������f���̃R���W����.Interserts(���胂�f���̃R���W����)

		//�a��
		SetAnimation(model, Attack_S);
		handle = DX12Effect.Play(Sword_Effect_);
		DX12Effect.SetPosition(handle, Vector3(6, -7, 0));
		//if (box.Intersects(->GetBox())) {
		//	//�U��������������P�_���[�W��^����
		//	//�G��HP��3�Ȃ̂Ő�������ΎO���œ|���
		//	EnemyBase���^�̕ϐ�->Damage();
		//}
	}

}

bool PlayerManager::IsAttack() {
	if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent->x)
		return true;

	return false;

}