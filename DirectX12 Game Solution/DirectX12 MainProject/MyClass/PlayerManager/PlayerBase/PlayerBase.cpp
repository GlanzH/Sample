#include "PlayerBase.h"


#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerAttack/PlayerAttack.h"

PlayerBase::PlayerBase() {

	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	//�U���̎���
	attack_flag = false;
	attack_time = 0.0f;
	attack_zeit_max = 0.0f;

	direction_state_mode = Direction_State::RIGHT;
	under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;


	//���G����
	invincible_flag = false;
	invincible_time = 0.0f;
	invincible_time_max = 0.2f;

	//�W�����v���Ă邩�̃t���O
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;


	//�W�����v�^�C�~���O
	jump_start_flag = false;
	jump_start_time = 0.0f;
	jump_start_time_max = 0.0f;

	jump_end_flag = false;


	//�A�s�[��
	appeil_flag = false;
	appeil_time = 0.0f;
	appeil_cool_flag = false;
	//�K�E�Z
	deathbrow_flag = false;//�K�E�Z�����t���O



	//�U���̎��
	attack_type = 0;

	//���
	avoidance_flag = false;
	avoidance_start = 0.0f;
	avoidance_max = 0.0f;
	avoidance_move = 0.0f;


	//�m�b�N�o�b�N
	knock_back_flag = false;
	knock_back_start = 0.0f;
	knock_back_end = 0.0f;
	time_other = 0.0f;

	//�N���オ��
	rize_end = 0.0f;


	damage_mode_state = Damage_Mode::NOMAL_STATE;



	//��i(�ϐ��錾)
	upper_state_mode = Upper_State::NOT_UPPER;
	upper_start = 0.0f;
	upper_end = 0.383f;


	//���i(�ϐ��錾)
	lower_state_mode = Lower_State::NOT_LOWER;
	lower_start = 0.0f;
	lower_end = 0.333f;

	//�[��
	s_del_flag = false;
	s_del_start = 0.0f;
	s_del_end = 0.0f;



	//�G�̏���
	elimination_flag = false;
	elimination_end = 0.0f;


}

void PlayerBase::OnDeviceLost() {
	//DX12Effect.Reset();
}

bool PlayerBase::Initialize()
{
	//�W�����v���Ă邩�̃t���O
	jump_flag_ = false;
	jump_time_ = 0.0f;
	jump_start_v_ = 0.0f;

	//�W�����v�^�C�~���O
	jump_start_flag = false;
	jump_start_time = 0.0f;
	jump_start_time_max = 0.133f;
	jump_end_flag = false;


	//�U���̎���
	attack_flag = false;
	attack_time = 0.0f;
	attack_zeit_max = 0.05f;

	//���G����
	invincible_flag = false;
	invincible_time = 0.0f;
	invincible_time_max = 0.5f;

	invincible_type = Invincible_Type::NOT_INVICIBLE;

	//���
	avoidance_flag = false;
	avoidance_start = 0.0f;
	avoidance_max = 0.483f;
	avoidance_move = -50.0f;


	//�U���̎��
	attack_type = 0;



	//�A�s�[��
	appeil_flag = false;
	appeil_time = 0.0f;
	appeil_cool_flag = false;
	//�K�E�Z
	deathbrow_flag = false;//�K�E�Z�����t���O


	//�m�b�N�o�b�N
	knock_back_flag = false;
	knock_back_start = 0.0f;
	knock_back_end = 0.7f;
	time_other = 0.0f;

	//�N���オ��
	rize_end = 1.733f;


	damage_mode_state = Damage_Mode::NOMAL_STATE;

	//�m�b�N�o�b�N�������
	direction_knock_back == Direction_Knock_Back::RIGHT_BACK;




	//��i(�ϐ��錾)
	upper_state_mode = Upper_State::NOT_UPPER;
	upper_start = 0.0f;
	upper_end = 0.633f;

	//���i(�ϐ��錾)
	lower_state_mode = Lower_State::NOT_LOWER;
	lower_start = 0.0f;
	lower_end = 0.633f;

	//�[��
	s_del_flag = false;
	s_del_start = 0.0f;
	s_del_end = 2.0f;

	//�G�̏���
	elimination_flag = false;
	elimination_end  = 1.0f;

	frip_state_mode = Frip_State::NOT_FRIP;

	frip_flag = false;

	frip_start = 0.0f;
	frip_end = 0.783f;



	direction_state_mode = Direction_State::RIGHT;




	//�v���C���[��SE �t�@�C���ǂݍ���
	//�U��-SE
	first_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE\\Player\\first_attack_se.wav");
	second_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE\\Player\\second_attack_se.wav");
	third_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE\\Player\\third_attack_se.wav");
	return 0;
}

void PlayerBase::LoadAssets()
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Player\\chara_motion_v0125_.X");
	model->SetScale(model_scale);
	model->SetPosition(player_pos);
	model->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);

	//�v���C���[�̓����蔻��
	col.box = model->GetBoundingBox();
	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.box.Extents.x * player_box_size_x,
		col.box.Extents.y * player_box_size_y,
		col.box.Extents.z * player_box_size_z
	);
	collision->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);

	material.Diffuse  = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient  = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	collision->SetMaterial(material); 

	//�E�̓����蔻��
	right_col.right_box = model->GetBoundingBox();
	right_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		right_col.right_box.Extents.x * 2,
		right_col.right_box.Extents.y * 9,
		right_col.right_box.Extents.z * 2
	);
	right_collision->SetMaterial(material);

	//���̓����蔻��
	left_col.left_box = model->GetBoundingBox();
	left_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		left_col.left_box.Extents.x * 2,
		left_col.left_box.Extents.y * 9,
		left_col.left_box.Extents.z * 2
	);
	left_collision->SetMaterial(material);


	col.sword_box = model->GetBoundingBox();
	col.sword_box.Extents = SimpleMath::Vector3(col.sword_box.Extents) * 7.0f;
	sword_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.sword_box.Extents.x * 3,
		col.sword_box.Extents.y * 2,
		col.sword_box.Extents.z * 2
		//col.sword_box.Extents.x * box_size_x,
		//col.sword_box.Extents.y * box_size_y,
		//col.sword_box.Extents.z * box_size_z
	);
	sword_collision->SetMaterial(material);


	//�t�H���g
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);


	//�G�t�F�N�g�@�t�@�C���ǂݍ���
	DX12Effect.Create(L"Effect\\SwordEffect\\upper_attack\\upper_attack.efk","upper");
	DX12Effect.Create(L"Effect\\SwordEffect\\lower_attack\\lower_attack.efk","lower");



	//�G�t�F�N�g�@�~��
	DX12Effect.Create(L"Effect\\PlayerEffect\\stop\\stop.efk", "clincher");

	//�G�t�F�N�g�@�e�����
	DX12Effect.Create(L"Effect\\PlayerEffect\\be_played\\be_played.efk", "frip");

	//�K�E�Z�̃G�t�F�N�g
	DX12Effect.Create(L"Effect\\DeathBlow_Effect\\deathblow\\deathblow.efk", "deathblow_effect");

	//�p���B�̃G�t�F�N�g
	DX12Effect.Create(L"Effect\\Parry_Effect\\parry\\parry.efk", "parry_effect");
}

int PlayerBase::Update(const float deltaTime, bool temp)
{

	//���f���@�A�j���[�V����
	SetAnimation(model, STAND);

	//�v���C���[:�ړ�
	Player_move(deltaTime);

	//�v���C���[:�W�����v
	Player_jump(deltaTime);

	//�����o�[�W���b�N(�ړ�����)
	Player_limit();

	//�U���֌W
	Attack_Relation(deltaTime);


	//�~��
	Sword_Delivery(deltaTime, temp);

	//�e�����
	Frip();

	//���
	Avoidance(deltaTime);

	//���G����
	Invincible(deltaTime);

	//�m�b�N�o�b�N
	Knock_Back();


	//�U���̌���
	if (direction_state_mode == Direction_State::RIGHT) {
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(6.5, 5, 0));
		col.sword_box.Center = sword_collision->GetPosition() + SimpleMath::Vector3(0, -5.1, 0);
	}
	else if (direction_state_mode == Direction_State::LEFT) {
		
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-6.5, 5, 0));
		col.sword_box.Center = sword_collision->GetPosition() + SimpleMath::Vector3(0, -5.1, 0);
	}

	//�U������̎���
	if (attack_flag)
		attack_time += deltaTime;
	if (attack_time >= attack_zeit_max) {
		attack_flag = false;
		attack_time = 0.0f;
	}

	time_other = deltaTime;

	player_pos = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 1, 0));
	col.box.Center = collision->GetPosition();

	right_collision->SetPosition(player_pos.x + 1.1f, player_pos.y + 5.0f, player_pos.z);
	right_col.right_box.Center = right_collision->GetPosition() + SimpleMath::Vector3(0, -5.1, 0);

	left_collision->SetPosition(player_pos.x - 1.1f, player_pos.y + 5.0f, player_pos.z);
	left_col.left_box.Center  = left_collision->GetPosition() + SimpleMath::Vector3(0, -5.1, 0);


	model->AdvanceTime(deltaTime);
	return 0;
}

void PlayerBase::Render()
{
	//�v���C���[�̕`��
	model->Draw();
	//collision->Draw();
	//if (attack_flag) {
	//	sword_collision->Draw();
	//}
	////parry_collision->Draw();
	//right_collision->Draw();
	//left_collision->Draw();
}

void PlayerBase::OnCollisionEnter(std::string tag) {
	//�G�ɓ��������Ƃ��̏���
	if (!invincible_flag) {
		//���G
		invincible_flag = true;
		
		//�m�b�N�o�b�N
		knock_back_flag = true;

		if (tag == "SW")
			reduce_num = body_reduce_num;

		if (tag == "SH")
			reduce_num = body_reduce_num;

		if (tag == "MB")
			reduce_num = mb_reduce_num;

		if (tag == "AR")
			reduce_num = body_reduce_num;


		Knock_Back();

		StatusManager::Instance().SetAddScore(reduce_num);
	}
}

void PlayerBase::OnWeaponCollisionEnter(std::string tag) {

	//�G�ɓ��������Ƃ��̏���
	if (!invincible_flag) {

		//�m�b�N�o�b�N
		knock_back_flag = true;


		if (tag == "SW")
			reduce_num = weapon_reduce_num;

		if (tag == "SH")
			reduce_num = weapon_reduce_num;

		if (tag == "MB")
			reduce_num = mb_weapon_reduce_num;

		Knock_Back();


		StatusManager::Instance().SetAddScore(reduce_num);
	}
}

void PlayerBase::OnLeftCollisionEnter(std::string tag) {//��
	//�G�ɓ����������̏���(��)
	if (!invincible_flag) {

		//�m�b�N�o�b�N
		knock_back_flag = true;
		direction_knock_back = Direction_Knock_Back::LEFT_BACK;


		if (tag == "SW")
			reduce_num = weapon_reduce_num;

		if (tag == "SH")
			reduce_num = weapon_reduce_num;

		if (tag == "MB")
			reduce_num = mb_weapon_reduce_num;

		Knock_Back();


		StatusManager::Instance().SetAddScore(reduce_num);

	}
}

void PlayerBase::OnRightCollisionEnter(std::string tag) {//�E
	//�G�ɓ����������̏���(�E)
	if (!invincible_flag) {


		//�m�b�N�o�b�N
		knock_back_flag = true;
		direction_knock_back = Direction_Knock_Back::RIGHT_BACK;


		if (tag == "SW")
			reduce_num = weapon_reduce_num;

		if (tag == "SH")
			reduce_num = weapon_reduce_num;

		if (tag == "MB")
			reduce_num = mb_weapon_reduce_num;

		StatusManager::Instance().SetAddScore(reduce_num);

	}
}

void PlayerBase::Invincible(const float deltaTime)
{

	switch (invincible_type)
	{
	case Invincible_Type::NOT_INVICIBLE:
		//����̖��G
		if (avoidance_flag) {
			invincible_type = Invincible_Type::AVOIDANCE_INV;
		}

		//�m�b�N�o�b�N�̖��G
		if (knock_back_flag) {
			invincible_type = Invincible_Type::KNOCK_BACK_INV;
		}

		//�e���ꂽ�ۂ̖��G
		if (frip_flag) {
			invincible_type = Invincible_Type::FRIP_INV;
		}
		break;
	case Invincible_Type::AVOIDANCE_INV:
		//����̖��G����
		invincible_flag = true;
		invincible_time += deltaTime;

		if (invincible_time >= 0.7f) {
			invincible_time = 0.0f;
			invincible_flag = false;
			invincible_type = Invincible_Type::NOT_INVICIBLE;
		}

		break;
	case Invincible_Type::KNOCK_BACK_INV:
		//�m�b�N�o�b�N�̖��G����
		invincible_flag = true;
		invincible_time += deltaTime;

		if (invincible_time >= 2.5f) {
			invincible_time = 0.0f;
			invincible_flag = false;
			invincible_type = Invincible_Type::NOT_INVICIBLE;
		}
		break;
	case Invincible_Type::FRIP_INV:
		//�U����e���ꂽ�ۂ̖��G����
		invincible_flag = true;
		invincible_time += deltaTime;

		if (invincible_time >= 1.0f) {
			invincible_time = 0.0f;
			invincible_flag = false;
			invincible_type = Invincible_Type::NOT_INVICIBLE;
		}

		break;
	}
}


//�m�b�N�o�b�N
void PlayerBase::Knock_Back() {

	switch (damage_mode_state) {
	case Damage_Mode::NOMAL_STATE:
		if (knock_back_flag) {
			damage_mode_state = Damage_Mode::KNOCK_BACK;
		}
		break;
	case Damage_Mode::KNOCK_BACK:
		knock_back_start += time_other;
		SetAnimation(model, DAMAGE1);


		Knock_back_Move();
		
		Rize();
		break;
	}
}


void PlayerBase::Knock_back_Move() {

	if (knock_back_start < knock_back_end) {
		switch (direction_knock_back)
		{
		case Direction_Knock_Back::RIGHT_BACK:
			if (direction_state_mode == Direction_State::RIGHT) {
				model->Move(0, 0, 40.0f * time_other);
			}
			else if (direction_state_mode == Direction_State::LEFT) {
				model->SetRotation(0.0f, XMConvertToRadians(-90.0f), 0.0f);
				model->Move(0, 0, 40.0f * time_other);
			}
			break;
		case Direction_Knock_Back::LEFT_BACK:
			if (direction_state_mode == Direction_State::RIGHT) {
				model->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);
				model->Move(0, 0, 40.0f * time_other);
			}
			else if (direction_state_mode == Direction_State::LEFT) {				
				model->Move(0, 0, 40.0f * time_other);
			}
			break;
		}
	}

}

//�N���オ��
void PlayerBase::Rize() {
	if (knock_back_start >= rize_end) {
		knock_back_start = 0.0f;
		knock_back_flag = false;
		damage_mode_state = Damage_Mode::NOMAL_STATE;
	}
}

void PlayerBase::OnParryArea() {
	//�p���B�������̏���
	//�p���B�J�E���g�𑝂₷

}

//�w�肳�ꂽ���[�V������TRUE,����ȊO��FALSE
void PlayerBase::SetAnimation(DX9::SKINNEDMODEL& model, const int enableTrack)
{
	for (int i = 0; i < MOTION_MAX; ++i) {
		model->SetTrackEnable(i, FALSE);
	}
	model->SetTrackEnable(enableTrack, TRUE);
}

void PlayerBase::Player_move(const float deltaTime)
{
	if (upper_state_mode == Upper_State::NOT_UPPER && lower_state_mode == Lower_State::NOT_LOWER) {
		if ( !knock_back_flag && !s_del_flag && !avoidance_flag) {
			//�v���C���[:�ړ�(�L�[�{�[�h) & �Q�[���p�b�h�\���L�[
			if (DXTK->KeyState->Right || DXTK->GamePadState[0].dpad.right) {
				model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
				model->SetRotation(0.0f, DirectX::XMConvertToRadians(model_rotetion), 0.0f);
				col.sword_box.Center = model->GetRotation();
				direction_state_mode = Direction_State::RIGHT;
				SetAnimation(model, RUN);
			}
			if (DXTK->KeyState->Left || DXTK->GamePadState[0].dpad.left) {
				model->Move(0.0f, 0.0f, -player_speed_ * deltaTime);
				model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
				col.sword_box.Center = model->GetRotation();
				direction_state_mode = Direction_State::LEFT;
				SetAnimation(model, RUN);
			}
		}
	}
}


void PlayerBase::Player_limit()
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

void PlayerBase::Player_jump(const float deltaTime) {
	//�W�����v
	if (!s_del_flag && !avoidance_flag && lower_state_mode == Lower_State::NOT_LOWER && upper_state_mode == Upper_State::NOT_UPPER) {
		if (!jump_flag_) {
			if (DXTK->KeyEvent->pressed.Space || DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
				jump_start_flag = true;
				jump_flag_ = true;
				jump_time_ = 0;
				jump_start_v_ = model->Position.y;
			}
		}

	}

	if (jump_start_flag) {
		SetAnimation(model, JUMP);
		jump_start_time += deltaTime;
	}

	if (jump_flag_ && jump_start_time >= jump_start_time_max) {

		jump_time_ += deltaTime;
		auto pos = model->GetPosition();
		pos.y = jump_start_v_ + V0 * jump_time_ - 0.5f * gravity_ * jump_time_ * jump_time_;
		model->SetPosition(pos);

		if (model->GetPosition().y <= 0.65f) {
			jump_flag_ = false;
			jump_start_flag = false;
			jump_start_time = 0.0f;
			model->SetTrackPosition(JUMP, 0.0);
		}
	}
}

//�U��
void PlayerBase::Attack_Relation(const float deltaTime) {
	if (!jump_flag_) {
		//�U�艺�낵
		Swing_Down(deltaTime);

		//�؂�グ
		Reverse_Slash(deltaTime);
	}
}


//�~�艺�낵
void PlayerBase::Swing_Down(const float deltaTime) {
	switch (upper_state_mode)
	{
	case Upper_State::NOT_UPPER:
		if (lower_state_mode == Lower_State::NOT_LOWER && upper_state_mode == Upper_State::NOT_UPPER && !avoidance_flag) {
			if (!s_del_flag) {
				if (DXTK->KeyEvent->pressed.A || DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
					upper_state_mode = Upper_State::UPPER_ATTACK;
				}
			}
		}
		break;
	case Upper_State::UPPER_ATTACK:
		upper_start += deltaTime;
		SetAnimation(model, ACT1);

		//�����蔻��
		//�G�t�F�N�g
		attack_flag = true;
		attack_type = 1;

		if (!frip_flag && effect_count < 1) {
			if (direction_state_mode == Direction_State::RIGHT) {

				DX12Effect.PlayOneShot("upper", Vector3(player_pos.x + 4.0f, player_pos.y + 5.0f, player_pos.z));
			}
			else if (direction_state_mode == Direction_State::LEFT) {
				DX12Effect.Play("upper", Vector3(player_pos.x - 9.0f, player_pos.y + 4.0f, player_pos.z));
				DX12Effect.SetRotation("upper", Vector3(0.0f, 180.0f, 0.0f));
			}

			effect_count += 1;
		}

		if (upper_start >= upper_end) {
			upper_state_mode = Upper_State::NOT_UPPER;
			upper_start = 0.0f;
			model->SetTrackPosition(ACT1, 0.0);
			effect_count = 0;
			attack_type = 0;
		}

		break;
	}
}


//�؂�グ
void PlayerBase::Reverse_Slash(const float deltaTime) {
	switch (lower_state_mode)
	{
	case Lower_State::NOT_LOWER:
		if (lower_state_mode == Lower_State::NOT_LOWER && upper_state_mode == Upper_State::NOT_UPPER && !avoidance_flag) {
			if (!s_del_flag) {
				if (DXTK->KeyEvent->pressed.S || DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
					lower_state_mode = Lower_State::LOWER_ATTACK;
				}
			}
		}
		break;
	case Lower_State::LOWER_ATTACK:
		lower_start += deltaTime;
		SetAnimation(model, ACT2);

		attack_flag = true;
		attack_type = 2;

		if (!frip_flag && effect_count < 1) {
			if (direction_state_mode == Direction_State::RIGHT) {

				DX12Effect.PlayOneShot("lower", Vector3(player_pos.x + 4.0f, player_pos.y + 5.0f, player_pos.z));
				DX12Effect.SetRotation("lower", Vector3(0.0f, 0.0f, 0.0f));

			}
			else if (direction_state_mode == Direction_State::LEFT) {
				DX12Effect.PlayOneShot("lower", Vector3(player_pos.x - 9.0f, player_pos.y + 4.0f, player_pos.z));
				DX12Effect.SetRotation("lower", Vector3(0.0f, 180.0f, 0.0f));
			}
			effect_count += 1;
		}

		if (lower_start >= lower_end) {
			lower_state_mode = Lower_State::NOT_LOWER;
			lower_start = 0.0f;
			model->SetTrackPosition(ACT2, 0.0);

			effect_count = 0;
			attack_type = 0;
		}

		break;
	}
}

//�~��
void PlayerBase::Sword_Delivery(const float deltaTime, bool temp) {
	//������Ԃ̓G��1�̈ȏ�ŉ\
	if (!jump_flag_) {
		if (temp) {
			if (DXTK->KeyEvent->pressed.D || DXTK->GamePadEvent[0].rightShoulder == GamePad::ButtonStateTracker::PRESSED) {
				s_del_flag = true;
			}
		}
	}


	if (s_del_flag) {
		s_del_start += deltaTime;

		if (direction_state_mode == Direction_State::RIGHT) {
			SetAnimation(model, FINISH);
			
		}
		else if (direction_state_mode == Direction_State::LEFT) {
			SetAnimation(model, FINISH);
			model->SetRotation(0.0f, XMConvertToRadians(-90.0f), 0.0f);

		}

		DX12Effect.PlayOneShot("clincher", Vector3(player_pos.x, player_pos.y + 6.0f, player_pos.z));
		if (s_del_start >= elimination_end) {
			elimination_flag = true;
		}

	}

	if (s_del_start >= s_del_end) {
		s_del_flag = false;
		s_del_start = 0.0f;
		model->SetTrackPosition(FINISH, 0.0);

		elimination_flag = false;

		if (direction_state_mode == Direction_State::LEFT) {
			model->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);

		}
	}
}

//�e�����
void PlayerBase::Frip() {

	switch (frip_state_mode)
	{
	case Frip_State::NOT_FRIP:
		if (frip_flag && upper_state_mode == Upper_State::UPPER_ATTACK && upper_start >= 0.1f ||
			frip_flag && lower_state_mode == Lower_State::LOWER_ATTACK && lower_start >= 0.1f)
			frip_state_mode = Frip_State::FRIP;
		break;
	case Frip_State::FRIP:
		SetAnimation(model, REBOUND);
		DX12Effect.Play("frip", Vector3(player_pos.x, player_pos.y + 4.0f, player_pos.z));

		Frip_Knock_Back();

		break;
	}
}

void PlayerBase::Frip_Knock_Back() {
	frip_start += time_other;

	if (direction_state_mode == Direction_State::RIGHT) {
		model->Move(0, 0, 20.0f * time_other);
	}
	else if (direction_state_mode == Direction_State::LEFT) {
		model->Move(0, 0, 20.0f * time_other);
	}



	if (frip_start >= frip_end) {
		model->SetTrackPosition(REBOUND, 0.0);
		frip_flag = false;
		frip_start = 0.0f;
		frip_state_mode = Frip_State::NOT_FRIP;

		upper_state_mode = Upper_State::NOT_UPPER;
		upper_start = 0.0f;
		model->SetTrackPosition(ACT1, 0.0);


		lower_state_mode = Lower_State::NOT_LOWER;
		lower_start = 0.0f;
		model->SetTrackPosition(ACT2, 0.0);

		attack_type = 0;

	}
}

//���
void PlayerBase::Avoidance(const float deltaTime) {

	if (!jump_flag_ && !s_del_flag && upper_state_mode == Upper_State::NOT_UPPER && lower_state_mode == Lower_State::NOT_LOWER && !knock_back_flag) {
		if (!avoidance_flag) {
			if (DXTK->KeyEvent->pressed.Z || DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED) {
				avoidance_flag = true;
			}
		}
	}

	if (avoidance_flag) {
		avoidance_start += deltaTime;
		
		model->Move(0.0f, 0.0, avoidance_move * deltaTime);
		SetAnimation(model, ROLL);

		//����(�����Ɏg������)
		//avoidance_move += 70 * deltaTime;
		//if (avoidance_move >= 0.0f) {
		//	avoidance_move = 0;
		//}

	}

	if (avoidance_start >= avoidance_max) {
		avoidance_start = 0.0f;
		avoidance_flag = false;
		model->SetTrackPosition(ROLL, 0.0);

		avoidance_move = -50.0f;
	}
}

bool PlayerBase::IsAttack() {
	return attack_flag;
}

void PlayerBase::Debug() {
	//if (invincible_flag) {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1100.0f, 120.0f),
	//		DX9::Colors::BlueViolet,
	//		L"ON"
	//	);
	//}

}