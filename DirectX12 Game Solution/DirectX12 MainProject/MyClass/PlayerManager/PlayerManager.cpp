#include "Base/pch.h"
#include "Base/dxtk.h"
#include "PlayerManager.h"

#include "MyClass/StatusManager/StatusManager.h"


bool PlayerManager::Initialize() 
{
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;

	appeal_state_mode = Appeal_state::NORMAL;

	direction_state_mode = Direction_State::RIGHT;



	return 0;
}

void PlayerManager::LoadAssets() 
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Player\\playler_motion.X");
	model->SetScale(model_scsle);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, XMConvertToRadians(model_rotetion), 0.0f);

	//�v���C���[�̓����蔻��
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

	//�U���G�t�F�N�g
	DX12Effect.Initialize();
	//1
	Sword_Effect_1 = DX12Effect.Create(L"Effect\\SwordEffect_AOZORA\\first_attack\\first_attack.efk");
	//2
	Sword_Effect_2 = DX12Effect.Create(L"Effect\\SwordEffect_AOZORA\\second_attack\\second_attack.efk");
	//3
	Sword_Effect_3 = DX12Effect.Create(L"Effect\\SwordEffect_AOZORA\\third_attack\\third_attack.efk");


}

int PlayerManager::Update(DX9::MODEL& ground, const float deltaTime)
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
	Player_attack(deltaTime);

	////�v���C���[:�U���G�t�F�N�g
	//Player_Attack_Effect(deltaTime);


	//�����o�[�W���b�N(�ړ�����)
	Player_limit();

	//�p���B
	Parry();

	//�A�s�[��
	//Appeal(deltaTime);


	//���G����
	Invincible(deltaTime);

	StatusManager::Instance().Update(deltaTime);



	//�U���̌���
	if (direction_state_mode == Direction_State::RIGHT) {
		sword_box.Center = model->GetPosition() + SimpleMath::Vector3(7, 0, 0);
	}
	else if (direction_state_mode == Direction_State::LEFT) {
		sword_box.Center = model->GetPosition() + SimpleMath::Vector3(-5, 0, 0);
	}

	//�U������̎���
	if (attack_flag)
		attack_zeit += deltaTime;
	if (attack_zeit > attack_zeit_max) {
		attack_flag = false;
		attack_zeit = 0.0f;
	}
	//if(DXTK->KeyState->Left)
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-8, 6, 0));
	//else if(DXTK->KeyState->Right)

	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-0.5, 4, 0));
	model->AdvanceTime(deltaTime / 1.5f);
	return 0;
}

void PlayerManager::Render() 
{
	//�v���C���[�̕`��
	model->Draw();

	//collision->Draw();
	//sword_collision->Draw();
}

void PlayerManager::OnCollisionEnter() {

	//�G�ɓ��������Ƃ��̏���
	if (!invincible_flag) {
		model->SetPosition(player_pos.x -= 2.0f, player_pos.y, player_pos.z);
		
		//���G
		invincible_flag = true;

		sword_box.Center = model->GetPosition() + SimpleMath::Vector3(6, 0, 0);
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(8, 6, 0));

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
	}
}

void PlayerManager::Invincible(const float deltaTime)
{
	if (invincible_flag)
		invincible_time += deltaTime;

	if (invincible_time >= invincible_time_max) {
		invincible_flag = false;
		invincible_time = 0.0f;
	}
}


void PlayerManager::OnParryArea() {
	//�p���B�������̏���
	SetAnimation(model, Parry_);

}

void PlayerManager::Parry() {
	if (DXTK->KeyState->P||DXTK->GamePadState->buttons.b) {
		if (parry_count < max_parry_count) {
			parry_count++;
			parry_flag = true;
		}
	}
	else {
		parry_flag  = false;
		parry_count = 0;
	}
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
	//�R���{�m�F�p
	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 0.0f),
		DX9::Colors::Black,
		L"%d",StatusManager::Instance().GetCombo()
	);

	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 40.0f),
		DX9::Colors::Red,
		L"%f", cool_time_zwei
	);

	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 60.0f),
		DX9::Colors::Brown,
		L"%d", count
	);

	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 80.0f),
		DX9::Colors::DarkGreen,
		L"%f", StatusManager::Instance().Gettime()
	);

	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1000.0f, 100.0f),
		DX9::Colors::DarkGreen,
		L"%f", count_time
	);


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
	if (!parry_flag) {
		//�v���C���[:�ړ�(�L�[�{�[�h)
		if (DXTK->KeyState->Right || DXTK->KeyState->D || DXTK->GamePadState[0].dpad.right) {
			model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
			model->SetRotation(0.0f, XMConvertToRadians(model_rotetion), 0.0f);
			sword_box.Center = model->GetRotation();
			direction_state_mode = Direction_State::RIGHT;
			SetAnimation(model, Run);

		}
		if (DXTK->KeyState->Left || DXTK->KeyState->A || DXTK->GamePadState[0].dpad.left) {
			model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
			model->SetRotation(0.0f, XMConvertToRadians(-model_rotetion), 0.0f);
			sword_box.Center = model->GetRotation();
			direction_state_mode = Direction_State::LEFT;
			SetAnimation(model, Run);

		}
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
	if (!parry_flag) {
		if (!jump_flag_) {
			if (DXTK->KeyEvent->pressed.Space || DXTK->GamePadEvent[0].a) {
				jump_flag_ = true;
				jump_time_ = 0;
				jump_start_v_ = model->Position.y;

			}
		}
	}

	if (jump_flag_) {

		jump_time_ += deltaTime;
		auto pos = model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time_ - 0.5f * gravity_ * jump_time_ * jump_time_;
		model->SetPosition(pos);
		//SetAnimation(model, Jump);

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

void PlayerManager::Player_attack(const float deltaTime) {
	//�v���C���[:�U��

	if (!cool_time_flag_zwei) {
		if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
			StatusManager::Instance().AddCombo(deltaTime);
			count_time = 0.0f;
			attack_flag = true;
			if (IsAttack()) {
				if (StatusManager::Instance().GetCombo() == 1) {
					//�a���A�j���[�V����
					SetAnimation(model, Attack_S);
					cool_time_flag_zwei = true;
					damege = 2;

					if (direction_state_mode == Direction_State::RIGHT) {
						handle_1 = DX12Effect.Play(Sword_Effect_1);
						DX12Effect.SetPosition(handle_1, Vector3(6, -5, 0));
						DX12Effect.SetSpeed(handle_1, 1.0f);
						DX12Effect.SetScale(handle_1, Vector3(2, 2, 2));
						DX12Effect.SetRotation(handle_1, Vector3(XMConvertToRadians(-10.0f), 0, XMConvertToRadians(15.0f)));
					}

					if (direction_state_mode == Direction_State::LEFT) {
						handle_1 = DX12Effect.Play(Sword_Effect_1);
						DX12Effect.SetPosition(handle_1, Vector3(-7, -9, -2));
						DX12Effect.SetSpeed(handle_1, 1.5f);
						DX12Effect.SetRotation(handle_1, Vector3(0, XMConvertToRadians(180), 0));
						DX12Effect.SetScale(handle_1, Vector3(1.5, 1.5, 1.5));

					}
				}
				else if (StatusManager::Instance().GetCombo() == 2) {
					SetAnimation(model, Attack_S);
					cool_time_flag_zwei = true;
					damege = 3;

					if (direction_state_mode == Direction_State::RIGHT) {
						handle_2 = DX12Effect.Play(Sword_Effect_2);
						DX12Effect.SetPosition(handle_2, Vector3(6, -7, 0));
						DX12Effect.SetSpeed(handle_2, 1.0f);
					}

					if (direction_state_mode == Direction_State::LEFT) {
						handle_2 = DX12Effect.Play(Sword_Effect_2);
						DX12Effect.SetPosition(handle_2, Vector3(-7, -9, -2));
						DX12Effect.SetSpeed(handle_2, 1.0f);
						DX12Effect.SetRotation(handle_2, Vector3(0, XMConvertToRadians(180), 0));
						DX12Effect.SetScale(handle_2, Vector3(1.5, 1.5, 1.5));

					}

				}
				else if (StatusManager::Instance().GetCombo() == 3) {
					SetAnimation(model, Attack_L);
					cool_time_flag_zwei = true;
					damege = 5;

					if (direction_state_mode == Direction_State::RIGHT) {
						handle_3 = DX12Effect.Play(Sword_Effect_3);
						DX12Effect.SetPosition(handle_3, Vector3(6, -7, 0));
						DX12Effect.SetSpeed(handle_3, 1.5f);
					}

					if (direction_state_mode == Direction_State::LEFT) {
						handle_3 = DX12Effect.Play(Sword_Effect_3);
						DX12Effect.SetPosition(handle_3, Vector3(-7, -9, -2));
						DX12Effect.SetSpeed(handle_3, 1.5f);
						DX12Effect.SetRotation(handle_3, Vector3(0, XMConvertToRadians(180), 0));
						DX12Effect.SetScale(handle_3, Vector3(1.5, 1.5, 1.5));

					}

				}
			}
		}
	}
	if (cool_time_flag_zwei) {
		cool_time_zwei += deltaTime;
		if (cool_time_zwei >= cool_time_max_zwei[count]) {
			cool_time_zwei = 0.0f;
			count++;
			cool_time_flag_zwei = false;
		}
	}

	count_time += deltaTime;
	if (count >= 3 || count_time > count_time_max) {
		count = 0;
		count_time = 0.0f;
	}


	//if (cool_time_flag && !cool_time_flag_zwei)
	//{
	//	cool_time += deltaTime;
	//}
	//if (!cool_time_flag && cool_time_flag_zwei)
	//{
	//	cool_time_zwei += deltaTime;
	//}

	//if (cool_time >= cool_time_max) {
	//	cool_time = 0.0f;
	//	cool_time_flag = false;
	//}




}

void PlayerManager::Player_Attack_Effect(const float deltaTime)
{
	if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {

	}

}

bool PlayerManager::IsAttack() {

	if (attack_flag) {
		return true;
	}
	return false;
}

void PlayerManager::Appeal(const float deltaTime)
{
	////�A�s�[��
	//if (DXTK->KeyEvent->pressed.W)
	//	appeal_state_mode = Appeal_state::APPEAL;

	//if (appeal_state_mode = Appeal_state::APPEAL) {
	//	SetAnimation(model, Appeil);
	//	appeal_time += deltaTime;
	//	if (appeal_time >= appeal_time_max) {
	//		appeal_state_mode = Appeal_state::NORMAL;
	//	}
	//}
}