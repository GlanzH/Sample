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
	rize_start = 0.0f;
	rize_end   = 0.0f;


	damage_mode_state = Damage_Mode::NOMAL_STATE;



	//��i(�ϐ��錾)
	upper_state_mode = Upper_State::NOT_UPPER;
	upper_start = 0.0f;
	upper_end = 0.383f;

	//���i(�ϐ��錾)
	lower_sate_mode = Lower_State::NOT_LOWER;
	lower_start = 0.0f;
	lower_end = 0.333f;
}

void PlayerBase::OnDeviceLost() {
	DX12Effect.Reset();
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
	attack_zeit_max = 0.03309f;

	//���G����
	invincible_flag = false;
	invincible_time = 0.0f;
	invincible_time_max = 0.5f;

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
	knock_back_flag  = false;
	knock_back_start = 0.0f;
	knock_back_end   = 0.2f;
	time_other       = 0.0f;

	//�N���オ��
	rize_start = 0.0f;
	rize_end   = 0.2f;


	damage_mode_state = Damage_Mode::NOMAL_STATE;



	//��i(�ϐ��錾)
	upper_state_mode = Upper_State::NOT_UPPER;
	upper_start      = 0.0f;
	upper_end        = 0.383f;

	//���i(�ϐ��錾)
	lower_sate_mode = Lower_State::NOT_LOWER;
	lower_start     = 0.0f;
	lower_end       = 0.333f;




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
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Player\\chara_motion_v0116_.X");
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
	right_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.right_box.Extents.x * sidebox_size_x,
		col.right_box.Extents.y * sidebox_size_y,
		col.right_box.Extents.z * sidebox_size_z
	);
	right_collision->SetMaterial(material);

	//���̓����蔻��
	left_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		left_box.Extents.x * sidebox_size_x,
		left_box.Extents.y * sidebox_size_y,
		left_box.Extents.z * sidebox_size_z
	);
	left_collision->SetMaterial(material);


	col.sword_box = model->GetBoundingBox();
	col.sword_box.Extents = SimpleMath::Vector3(col.sword_box.Extents) * 7.0f;
	sword_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.sword_box.Extents.x * box_size_x,
		col.sword_box.Extents.y * box_size_y,
		col.sword_box.Extents.z * box_size_z
	);
	sword_collision->SetMaterial(material);


	//�t�H���g
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);


	//�G�t�F�N�g�@�t�@�C���ǂݍ���
	DX12Effect.Create(L"Effect\\SwordEffect\\one\\first_attack.efk","first");
	DX12Effect.Create(L"Effect\\SwordEffect\\two\\second_attack.efk","second");
	DX12Effect.Create(L"Effect\\SwordEffect\\three\\third_attack.efk","third");

	//�K�E�Z�̃G�t�F�N�g
	DX12Effect.Create(L"Effect\\DeathBlow_Effect\\deathblow\\deathblow.efk", "deathblow_effect");

	//�p���B�̃G�t�F�N�g
	DX12Effect.Create(L"Effect\\Parry_Effect\\parry\\parry.efk", "parry_effect");

}

int PlayerBase::Update(const float deltaTime)
{

	//���f���@�A�j���[�V����
	SetAnimation(model, STAND);

	//�v���C���[:�ړ�
	Player_move(deltaTime);

	//�v���C���[:�W�����v
	Player_jump(deltaTime);

	//�����o�[�W���b�N(�ړ�����)
	Player_limit();

	//�U�艺�낵
	Swing_Down(deltaTime);

	//�؂�グ
	Reverse_Slash(deltaTime);

	//�[��
	Sword_Delivery();


	//���
	Avoidance(deltaTime);

	//���G����
	Invincible(deltaTime);

	//�m�b�N�o�b�N
	Knock_Back();

	//StatusManager::Instance().Update(deltaTime);



	//�U���̌���
	if (direction_state_mode == Direction_State::RIGHT) {
		col.sword_box.Center = model->GetPosition() + SimpleMath::Vector3(9.5, 3, 0);
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(6.5, 5, 0));

	}
	else if (direction_state_mode == Direction_State::LEFT) {
		col.sword_box.Center = model->GetPosition() + SimpleMath::Vector3(-9.5, 3, 0);
		sword_collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(-6.5, 5, 0));

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
	left_collision ->SetPosition(player_pos.x - 1.1f, player_pos.y + 5.0f, player_pos.z);


	model->AdvanceTime(deltaTime);
	return 0;
}

void PlayerBase::Render()
{
	//�v���C���[�̕`��
	model->Draw();
	//collision->Draw();
	//sword_collision->Draw();
	//parry_collision->Draw();
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

		StatusManager::Instance().AddAudience(reduce_num);
	}
}

void PlayerBase::OnWeaponCollisionEnter(std::string tag) {

	//�G�ɓ��������Ƃ��̏���
	if (!invincible_flag) {
		//���G
		invincible_flag = true;

		if (tag == "SW")
			reduce_num = weapon_reduce_num;

		if (tag == "SH")
			reduce_num = weapon_reduce_num;

		if (tag == "MB")
			reduce_num = mb_weapon_reduce_num;

		StatusManager::Instance().AddAudience(reduce_num);
	}
}

void PlayerBase::Invincible(const float deltaTime)
{
	if (invincible_flag)
		invincible_time += deltaTime;

	if (invincible_time >= invincible_time_max) {
		invincible_flag = false;
		invincible_time = 0.0f;
	}
}

void PlayerBase::Knock_Back() {

	switch (damage_mode_state) {
	case Damage_Mode::NOMAL_STATE:
		if (knock_back_flag) {
			damage_mode_state = Damage_Mode::KNOCK_BACK;
		}
		break;
	case Damage_Mode::KNOCK_BACK:
		knock_back_start += time_other;
		SetAnimation(model, DAMAGE);
		if (direction_state_mode == Direction_State::RIGHT) {
			model->Move(0, 0, 80.0f * time_other);
		}
		else if (direction_state_mode == Direction_State::LEFT) {
			model->Move(0, 0, 80.0f * time_other);
		}


		if (knock_back_start >= knock_back_end) {
			knock_back_flag = false;
			knock_back_start = 0.0f;
			damage_mode_state = Damage_Mode::RISE;
		}
		break;
	case Damage_Mode::RISE:
		SetAnimation(model, PARRY);
		rize_start += time_other;

		if (rize_start >= rize_end) {
			rize_start = 0.0f;
			damage_mode_state = Damage_Mode::NOMAL_STATE;
		}

		break;
	}


	if (knock_back_flag) {
		knock_back_start += time_other;
		if (knock_back_start < knock_back_end) {
			SetAnimation(model, DAMAGE);
			if (direction_state_mode == Direction_State::RIGHT) {
				model->Move(0, 0, 80.0f * time_other);
			}
			else if (direction_state_mode == Direction_State::LEFT) {
				model->Move(0, 0, 80.0f * time_other);
			}
		}
	}

	if (knock_back_start >= knock_back_end) {
		knock_back_flag = false;
		knock_back_start = 0.0f;
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
	if (!invincible_flag) {
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
	if (!invincible_flag) {
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


//�~�艺�낵
void PlayerBase::Swing_Down(const float deltaTime) {
	switch (upper_state_mode)
	{
	case Upper_State::NOT_UPPER:
		if (lower_sate_mode == Lower_State::NOT_LOWER || upper_state_mode == Upper_State::NOT_UPPER) {
			if (DXTK->KeyEvent->pressed.A || DXTK->GamePadEvent[0].y == GamePad::ButtonStateTracker::PRESSED) {
				upper_state_mode = Upper_State::UPPER_ATTACK;
			}
		}
		break;
	case Upper_State::UPPER_ATTACK:
		upper_start += deltaTime;
		SetAnimation(model, ACT1);

		attack_flag = true;
		if (IsAttack()) {

		}

		if (upper_start >= upper_end) {
			upper_state_mode = Upper_State::NOT_UPPER;
			upper_start = 0.0f;
			model->SetTrackPosition(ACT1, 0.0);
		}

		break;
	}
}


//�؂�グ
void PlayerBase::Reverse_Slash(const float deltaTime) {
	switch (lower_sate_mode)
	{
	case Lower_State::NOT_LOWER:
		if (lower_sate_mode == Lower_State::NOT_LOWER || upper_state_mode == Upper_State::NOT_UPPER) {
			if (DXTK->KeyEvent->pressed.S || DXTK->GamePadEvent[0].x == GamePad::ButtonStateTracker::PRESSED) {
				lower_sate_mode = Lower_State::LOWER_ATTACK;
			}
		}
		break;
	case Lower_State::LOWER_ATTACK:
		lower_start += deltaTime;
		SetAnimation(model, ACT2);

		attack_flag = true;
		if (IsAttack()) {

		}

		if (lower_start >= lower_end) {
			lower_sate_mode = Lower_State::NOT_LOWER;
			lower_start = 0.0f;
			model->SetTrackPosition(ACT2, 0.0);
		}

		break;
	}

}

//�[��
void PlayerBase::Sword_Delivery() {

}


//���
void PlayerBase::Avoidance(const float deltaTime) {

	if (!jump_flag_){
		if(!avoidance_flag) {
			if (DXTK->KeyEvent->pressed.Z || DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED) {
				avoidance_flag = true;
			}
		}
	}

	if (avoidance_flag) {
		avoidance_start += deltaTime;
		
		model->Move(0.0f, 0.0, avoidance_move * deltaTime);
		SetAnimation(model, ROLL);
		invincible_flag = true;

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

	if (attack_flag ) {


		return true;
	}
	return false;
}


void PlayerBase::Debug() {



	if (invincible_flag) {
		DX9::SpriteBatch->DrawString(font.Get(),
			SimpleMath::Vector2(1100.0f, 120.0f),
			DX9::Colors::BlueViolet,
			L"ON"
		);
	}
	else {
		DX9::SpriteBatch->DrawString(font.Get(),
			SimpleMath::Vector2(1100.0f, 120.0f),
			DX9::Colors::BlueViolet,
			L"OFF"
		);
	}

}