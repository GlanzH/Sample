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
	model->SetScale(0.04f);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, XMConvertToRadians(-90.0f), 0.0f);

	//�v���C���[�̓����蔻��
	box = model->GetBoundingBox();

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * 2,
		box.Extents.y * 2,
		box.Extents.z * 2
	);
	collision->SetRotation(0.0f, XMConvertToRadians(-90.0f), 0.0f);



	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	collision->SetMaterial(material);

	box.Center = player_pos;

}

int PlayerManager::Update(DX9::MODEL& ground, BoundingBox enemy, const float deltaTime)
{
	//�n�`�̓����蔻��
	float dist = FLT_MAX;
	if (ground->IntersectRay(model->GetPosition() + SimpleMath::Vector3(0, 100, 0), SimpleMath::Vector3::Down, &dist)) {
		model->Move(0.0f, 100.0f - dist, 0.0f);
	}

	//���f���@�A�j���[�V����

	SetAnimation(model, Wait);



	//�v���C���[:�ړ�
	if (DXTK->KeyState->Right||DXTK->KeyState->D) {
		model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
		SetAnimation(model, Walk);
		
	}
	if (DXTK->KeyState->Left||DXTK->KeyState->A) {
		model->Move(0.0f, 0.0f, player_speed_ * deltaTime);
		SetAnimation(model, Walk);
	}





	//�v���C���[:�W�����v
	//�W�����v
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

	//�v���C���[:�U��
	if (DXTK->KeyEvent->pressed.J||DXTK->KeyEvent->pressed.F) {
		//�����蔻���Interserts���g��
		//�����蔻��������������f���̃R���W����.Interserts(���胂�f���̃R���W����)
		//����̏ꍇ
		if (box.Intersects(enemy)) {
			//�v���C���[���I�ɂ��������Ƃ��̂̏���
			//����́Ahit_flag��true�ɂ���
			hit_flag = true;
		}
	}


	//�����o�[�W���b�N(�ړ�����)
	auto p_pos = model->GetPosition();
	p_pos = SimpleMath::Vector3(
		std::clamp(p_pos.x,  -99.0f,  99.0f),
		std::clamp(p_pos.y,   -5.0f, 1000.0f),
		std::clamp(p_pos.z, -100.0f, 100.0f)
	);
	model->SetPosition(p_pos);

	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0,4,0));

	return 0;
}

void PlayerManager::Render() 
{
	//�v���C���[�̕`��
	model->Draw();

	//collision->Draw();
}


//�w�肳�ꂽ���[�V������TRUE,����ȊO��FALSE
void PlayerManager::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}
