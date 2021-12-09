#include "PlayerBase.h"


#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerAttack/PlayerAttack.h"


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

	//�K�E�Z
	special_attack_flag = false;



	//�U���̎���
	attack_flag = false;
	attack_zeit = 0.0f;
	attack_zeit_max = 0.03309f;

	//�U���̃N�[���^�C��
	cool_time_flag_zwei = false;
	cool_time_zwei = 0.0f;
	cool_time_max_zwei = 1.0f;
	count = 0;

	count_flag = false;
	count_time = 0.0f;
	count_time_max = 0.4f;

	//�U��-����
	first_attaack_flag = false;

	//�U��-�J�E���g-�t���O
	//���[�V����
	motion_time_start_flag = false;

	motion_attack_flag = false;
	motion_time = 0.0f;

	motion_count = 0;


	//�G�t�F�N�g�̔����^�C�~���O��
	effect_generation = false;
	effect_generation_time = 0.1f;


	effect_end_flag = false;


	first_attack_hit = false;
	first_attack_time = 0.0f;
	first_attack_time_max = 0.333f;


	//���G����
	invincible_flag = false;
	invincible_time = 0.0f;


	//�ύX*2
	motion_flag = 0;

	motion_flag_1 = false;
	motion_flag_2 = false;
	motion_flag_3 = false;

	motion_start_time_1 = false;
	motion_start_time_2 = false;
	motion_start_time_3 = false;


	motion_time_1 = 0.0f;
	motion_time_2 = 0.0f;
	motion_time_3 = 0.0f;

	motion_time_max_1 = 0.6f;
	motion_time_max_2 = 0.26f;
	motion_time_max_3 = 0.583f;

	//���͎�t���Ԃ܂ł̎��� & �G�t�F�N�g�\���܂ł̎���
	input_wait_flag = false;
	input_wait_time = 0.0f;
	input_wait_count = 0;

	//���͎�t����
	input_flag = false;
	input_time = 0.0f;
	input_count = 0;

	//�G�t�F�N�g�\��
	effect_flag = false;

	//�A�j���[�V�������o������
	animation_flag = false;
	animation_time = 0.0f;

	animation_count = 0;

	//�A�s�[��
	appeil_flag = false;

	appeil_time = 0.0f;
	appeil_time_max = 5.0f;

	appeil_cool_time = 0.0f;
	appeil_cool_time_max = 1.0f;

	appeil_cool_flag = false;

	//�K�E�Z
	deathbrow_flag = false;//�K�E�Z�����t���O

	deathbrow_attack = false;//�K�E�Z�̓����蔻��

	specialmove_time = 0.0f;
	specialmove_time_max = 4.0f;


	//�Ó]
	Transparency = 0;
	Blackout = 15;
	Blackout_max = 255;
	Blackout_flag = false;

	//���]
	bright_flag = false;
	Ming_Turn = 55;

	Deathblow_count = 20;

	direction_state_mode = Direction_State::RIGHT;

	under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;

	canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

	cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;

	////�v���C���[��SE �t�@�C���ǂݍ���
	////�U��-SE
	//first_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"");
	//second_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"");
	//third_attack_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"");
	////�W�����v
	//jump_se= XAudio::CreateSoundEffect(DXTK->AudioEngine, L"");
	////���n
	//landing_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"");
	////�_���[�W
	//damege_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"");
	////�A�s�[��
	//appeal_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"");


	return 0;
}

void PlayerBase::LoadAssets()
{
	model = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Model\\Player\\chara_motion_v1207_.X");
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


	col.sword_box = model->GetBoundingBox();

	col.sword_box.Extents = SimpleMath::Vector3(col.sword_box.Extents) * 7.0f;

	sword_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		col.sword_box.Extents.x * box_size_x,
		col.sword_box.Extents.y * box_size_y,
		col.sword_box.Extents.z * box_size_z
	);



	parry_box = model->GetBoundingBox();

	parry_collision = DX9::Model::CreateBox(
		DXTK->Device9,
		parry_box.Extents.x * parry_box_size_x,
		parry_box.Extents.y * parry_box_size_y,
		parry_box.Extents.z * parry_box_size_z
	);

	parry_box.Center = model->GetPosition();

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	deathbrow_sprite = DX9::Sprite::CreateFromFile(DXTK->Device9, L"DeathBrowBG\\deathbrow_bg.png");

	//�G�t�F�N�g�@�t�@�C���ǂݍ���
	DX12Effect.Initialize();
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


	////�v���C���[:�U��
	//Player_attack(deltaTime);

	//�����o�[�W���b�N(�ړ�����)
	Player_limit();

	////�p���B
	//Parry(deltaTime);

	//�A�s�[��
	Appeal(deltaTime);

	//�K�E�Z
	Player_Special_Move(deltaTime);

	//�v���C���[�̍U��(�C��)
	Player_Attack_two(deltaTime);

	//���G����
	Invincible(deltaTime);

	StatusManager::Instance().Update(deltaTime);



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
		attack_zeit += deltaTime;
	if (attack_zeit >= attack_zeit_max) {
		attack_flag = false;
		attack_zeit = 0.0f;

		//effect_generation = false;
		//effect_generation_time = 0.0f;

	}

	col.box.Center = model->GetPosition();
	player_pos = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, 6, 0));

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
}

void PlayerBase::OnCollisionEnter() {

	//�G�ɓ��������Ƃ��̏���
	if (!invincible_flag) {
		//���G
		invincible_flag = true;
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

	if (invincible_flag) {
		SetAnimation(model, DAMAGE);
		if (direction_state_mode == Direction_State::RIGHT) {
			model->Move(0, 0, 30.0f * deltaTime);
		}
		else if (direction_state_mode == Direction_State::LEFT) {
			model->Move(0, 0, 30.0f * deltaTime);
		}
	}

}

void PlayerBase::OnParryArea() {
	//�p���B�������̏���
	//�p���B�J�E���g�𑝂₷

}

void PlayerBase::Parry(const float deltaTime) {
	if (!parry_flag) {
		if (DXTK->KeyEvent->pressed.P || DXTK->GamePadEvent[0].leftShoulder) {
			parry_flag = true;
		}
	}

	else {
		parry_count += deltaTime;
		SetAnimation(model, PARRY);

	}
	if (parry_count >= max_parry_count) {
		parry_flag = false;
		parry_count = 0.0f;
	}
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
		if(!deathbrow_flag){
			if (!appeil_flag) {
				if (canot_move_state_mode == CANNOT_MOVE_STATE::MOVE) {
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
		if (!deathbrow_flag) {
			if (under_attack_state_mode == UNDER_ATTACK_STATE::NOMAL) {
				if (!appeil_flag) {
					if (!jump_flag_) {
						if (DXTK->KeyEvent->pressed.Space || DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
							jump_start_flag = true;
							jump_flag_ = true;
							jump_time_ = 0;
							jump_start_v_ = model->Position.y;
						}
					}
				}
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

void PlayerBase::Player_attack(const float deltaTime) {
	//�v���C���[:�U��
	if (!cool_time_flag_zwei) {
		if (!parry_flag) {
			if (!deathbrow_flag) {
				if (!appeil_flag) {
					if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
						//�ړ��s��
						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;

						//����U��
						if (!first_attaack_flag) {
							StatusManager::Instance().AddCombo(deltaTime);
							first_attaack_flag = true;
						}
						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;

						if (StatusManager::Instance().GetCombo() == 1);
						else if (StatusManager::Instance().GetCombo() == 2);
						else if (StatusManager::Instance().GetCombo() == 3);
					}
				}
			}
		}
	}
	if (StatusManager::Instance().GetCombo() == 1) {
		motion_time_start_flag = true;
		effect_generation      = true;
		SetAnimation(model, ACT1);
	}
	if (StatusManager::Instance().GetCombo() == 2) {
		motion_time_start_flag = true;
		effect_generation      = true;
		SetAnimation(model, ACT2);
	}
	if (StatusManager::Instance().GetCombo() == 3) {
		motion_time_start_flag = true;
		effect_generation      = true;
		SetAnimation(model, ACT3);
	}
	if (motion_time_start_flag == true) {
		motion_time += deltaTime;
	}
	if (!motion_attack_flag) {
		if (motion_time >= 0.1f && motion_time < motion_time_max[motion_count]) {
			if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent[0].x) {
				motion_attack_flag = true;
			}
		}
	} else {
		if (motion_time >= motion_time_max[motion_count]) {
			StatusManager::Instance().AddCombo(deltaTime);
			motion_time = 0.0f;
			motion_time_start_flag = false;
			motion_attack_flag = false;
			motion_count++;
			if (StatusManager::Instance().GetCombo() == 3) {
				cool_time_flag_zwei = true;
			}
		}
	}
	if (cool_time_flag_zwei == true) {
		cool_time_zwei += deltaTime;
	}
	if (cool_time_zwei >= cool_time_max_zwei) {
		first_attaack_flag = false;
		cool_time_flag_zwei = false;
		cool_time_zwei = 0.0f;
	}


	if (motion_count >= 3) {
		motion_count = 0;
		effect_generation_time = 0.0f;
		effect_generation = false;
		first_attaack_flag = false;
		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

	}
	if (motion_time >= motion_time_max[motion_count] || StatusManager::Instance().GetCombo() == 0) {
		motion_time = 0.0f;
		effect_generation_time = 0.0f;
		effect_generation = false;
		motion_count = 0;
		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
		first_attaack_flag = false;
	}

	//�G�t�F�N�g�\���֌W
	if (effect_generation == true) {
		effect_generation_time += deltaTime;
	}

	if (effect_generation_time >= effect_generation_time_max[motion_count]) {
		attack_flag = true;
		if (IsAttack()) {
			if (StatusManager::Instance().GetCombo() == 1 && motion_count == 0) {
				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("first");
					DX12Effect.SetPosition("first", Vector3(player_pos.x + 5.0f, player_pos.y + 2.0f, player_pos.z));
					
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("first");
					DX12Effect.SetPosition("first", Vector3(player_pos.x - 7.0f, player_pos.y + 2.0f, player_pos.z));
					DX12Effect.SetRotation("first", Vector3(0.0f, 180.0f, 0.0f));
				}
					damage = 2;
			}
			else if (StatusManager::Instance().GetCombo() == 2 && motion_count == 1) {

				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("second");
					DX12Effect.SetPosition("second", Vector3(player_pos.x + 4.0f, player_pos.y + 6.0f, player_pos.z));
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("second");
					DX12Effect.SetPosition("second", Vector3(player_pos.x - 4.0f, player_pos.y + 6.0f, player_pos.z));
					DX12Effect.SetRotation("second", Vector3(0.0f, 180.0f, 0.0f));

				}
					damage = 3;

			}
			else if (StatusManager::Instance().GetCombo() == 3 && motion_count == 2) {
				if (direction_state_mode == Direction_State::RIGHT) {
					DX12Effect.PlayOneShot("third");
					DX12Effect.SetPosition("third", Vector3(player_pos.x + 7.0f, player_pos.y + 5.0f, player_pos.z));
				}
				else if (direction_state_mode == Direction_State::LEFT) {
					DX12Effect.PlayOneShot("third");
					DX12Effect.SetPosition("third", Vector3(player_pos.x - 7.0f, player_pos.y + 5.0f, player_pos.z));
					DX12Effect.SetRotation("third", Vector3(0.0f, 180.0f, 0.0f));

				}
					damage = 5;

			}
		}
	}
}

//�v���C���[�̍U��(�{�^���z�u�ύXver)
void PlayerBase::Player_Attack_two(const float deltaTime) {
	if (!cool_time_flag_zwei) {
		if (!parry_flag) {
			if (!deathbrow_flag) {
				if (!appeil_flag) {

					//1����
					if (DXTK->KeyEvent->pressed.A || DXTK->GamePadEvent->x == GamePad::ButtonStateTracker::PRESSED) {
						motion_flag_1 = true;
						//�ړ��s��
						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;

						//�W�����v�s��
						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;

						//�U�����@���̍U���s��
						if (cannot_other == CANNOT_OTHER_ATTACK::NOMAL_STATE && cannot_other != CANNOT_OTHER_ATTACK::SECOND && cannot_other != CANNOT_OTHER_ATTACK::THIRD) {
							cannot_other = CANNOT_OTHER_ATTACK::FIRST;

							Attack(deltaTime);
							
						}
					}

					//2����
					if (DXTK->KeyEvent->pressed.S || DXTK->GamePadEvent->y == GamePad::ButtonStateTracker::PRESSED) {
						motion_flag_2 = true;
						//�ړ��s��
						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
						//�W�����v�s��
						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;

						//�U�����@���̍U���s��
						if (cannot_other == CANNOT_OTHER_ATTACK::NOMAL_STATE && cannot_other != CANNOT_OTHER_ATTACK::FIRST && cannot_other != CANNOT_OTHER_ATTACK::THIRD) {
							cannot_other = CANNOT_OTHER_ATTACK::SECOND;

							Attack(deltaTime);
							
						}

					}

					//3����
					if (DXTK->KeyEvent->pressed.D || DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED) {
						motion_flag_3 = true;
						//�ړ��s��
						canot_move_state_mode = CANNOT_MOVE_STATE::CANNOT_MOVE;
						//�W�����v�s��
						under_attack_state_mode = UNDER_ATTACK_STATE::ATTACK;

						if (cannot_other == CANNOT_OTHER_ATTACK::NOMAL_STATE && cannot_other != CANNOT_OTHER_ATTACK::FIRST && cannot_other != CANNOT_OTHER_ATTACK::SECOND) {
							cannot_other = CANNOT_OTHER_ATTACK::THIRD;


							Attack(deltaTime);
							
						}
					}

				}
			}
		}
	}

	//if (DXTK->KeyEvent->pressed.D || DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED ||
	//	DXTK->KeyEvent->pressed.A || DXTK->GamePadEvent->x == GamePad::ButtonStateTracker::PRESSED ||
	//	DXTK->KeyEvent->pressed.S || DXTK->GamePadEvent->y == GamePad::ButtonStateTracker::PRESSED)
	//{
	//	Attack(deltaTime);
	//	effect_first_time = 0.0f;
	//}

	if (motion_flag_1) {
		if (cannot_other == CANNOT_OTHER_ATTACK::FIRST) {
			effect_generation = true;
			motion_start_time_1 = true;
			motion_count = 0;
			SetAnimation(model, ACT1);
		}
	}

	if (motion_start_time_1) {
		motion_time_1 += deltaTime;
	}

	if (motion_time_1 >= motion_time_max_1) {
		

		motion_start_time_1 = false;
		motion_time_1 = 0.0f;
		motion_flag_1 = false;

		model->SetTrackPosition(ACT1, 0.0);

		//�ړ���
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;
		//�W�����v��
		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;
		//�U�����@���̍U���s��->����
		cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;
	}

	if (motion_flag_2) {
		if (cannot_other == CANNOT_OTHER_ATTACK::SECOND) {
			effect_generation = true;
			motion_start_time_2 = true;
			motion_count = 1;
			SetAnimation(model, ACT2);
		}
	}

	if (motion_start_time_2) {
		motion_time_2 += deltaTime;
	}

	if (motion_time_2 >= motion_time_max_2) {
	

		motion_start_time_2 = false;
		motion_time_2 = 0.0f;
		motion_flag_2 = false;
		model->SetTrackPosition(ACT2, 0.0);

		//�ړ��s��
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

		//�W�����v��
		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;

		//���̍U���s��_����
		cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;
	}


	if (motion_flag_3) {
		effect_generation = true;
		motion_start_time_3 = true;
		motion_count = 2;
		SetAnimation(model, ACT3);
	}

	if (motion_start_time_3) {
		motion_time_3 += deltaTime;
	}

	if (motion_time_3 >= motion_time_max_3) {
		motion_start_time_3 = false;
		motion_time_3 = 0.0f;
		motion_flag_3 = false;

		model->SetTrackPosition(ACT3, 0.0);

		//�ړ��s��
		canot_move_state_mode = CANNOT_MOVE_STATE::MOVE;

		//�W�����v��
		under_attack_state_mode = UNDER_ATTACK_STATE::NOMAL;

		//���̍U���s��_����
		cannot_other = CANNOT_OTHER_ATTACK::NOMAL_STATE;
	}

	//�G�t�F�N�g�\���֌W
	if (effect_generation) {
		effect_generation_time += deltaTime;
		//effect_generation = false;
	}

	if (effect_generation_time >= 1.0f) {
		effect_generation_time = 0.0f;
	}


	
	if (first_attack_hit) {
		first_attack_time += deltaTime;
		if (first_attack_time >= first_attack_time_max) {
			attack_flag = true;
			if (IsAttack()) {
				//�G�l�~�[�ɗ^����_���[�W
				damage = 2;
				first_attack_hit = false;
				first_attack_time = 0.0f;
			}
		}
	}

}

void PlayerBase::Attack(const float deltaTime)
{
	if (cannot_other == CANNOT_OTHER_ATTACK::FIRST) {
		if (effect_generation_time >= 0.0f) {
			if (motion_flag_1) {
				first_attack_hit = true;
				Attack_First(deltaTime);
			}
		}
	}

	if (cannot_other == CANNOT_OTHER_ATTACK::SECOND) {
		if (effect_generation_time >= 0.033f) {
			attack_flag = true;
			if (IsAttack()) {
				if (motion_flag_2) {
					//�G�l�~�[�ɗ^����_���[�W
					damage = 3;
					Attack_Secnod(deltaTime);
				}
			}
		}
	}

	if (cannot_other == CANNOT_OTHER_ATTACK::THIRD) {
		if (effect_generation_time >= 0.005f) {
			attack_flag = true;
			if (IsAttack()) {
				if (motion_flag_3) {
					//�G�l�~�[�ɗ^����_���[�W
					damage = 5;
					Attack_Third(deltaTime);
				}
			}
		}
	}
}

//�G�t�F�N�g1����
void PlayerBase::Attack_First(const float deltaTime) {
	if (direction_state_mode == Direction_State::RIGHT) {
		if (DX12Effect.CheckAlive("first")) {
			DX12Effect.Stop("first");
			DX12Effect.PlayOneShot("first", Vector3(player_pos.x + 2.0f, player_pos.y + 5.0f, player_pos.z));

		}
		else
		{
			DX12Effect.PlayOneShot("first", Vector3(player_pos.x + 2.0f, player_pos.y + 5.0f, player_pos.z));

		}
		DX12Effect.SetRotation("first", Vector3(0.0f, 0.0f, 0.0f));
	}
	else if (direction_state_mode == Direction_State::LEFT) {
		if (DX12Effect.CheckAlive("first")) {
			DX12Effect.Stop("first");
			DX12Effect.PlayOneShot("first", Vector3(player_pos.x - 7.0f, player_pos.y + 4.0f, player_pos.z));
		}
		else
		{
			DX12Effect.PlayOneShot("first", Vector3(player_pos.x - 7.0f, player_pos.y + 4.0f, player_pos.z));
		}
		DX12Effect.SetRotation("first", Vector3(0.0f, 180.0f, 0.0f));
	}


}
//�G�t�F�N�g2����
void PlayerBase::Attack_Secnod(const float deltaTime) {
	if (direction_state_mode == Direction_State::RIGHT) {
		if (DX12Effect.CheckAlive("second")) {
			DX12Effect.Stop("second");
			DX12Effect.PlayOneShot("second", Vector3(player_pos.x + 3.0f, player_pos.y + 6.0f, player_pos.z));
		}
		else
		{
			DX12Effect.PlayOneShot("second", Vector3(player_pos.x + 3.0f, player_pos.y + 6.0f, player_pos.z));
		}

		DX12Effect.SetScale("second", Vector3(1.5f, 1.5f, 1.5f));

	}
	else if (direction_state_mode == Direction_State::LEFT) {
		if (DX12Effect.CheckAlive("second")) {
			DX12Effect.Stop("second");
			DX12Effect.PlayOneShot("second", Vector3(player_pos.x - 3.0f, player_pos.y + 6.0f, player_pos.z));
		}
		else
		{
			DX12Effect.PlayOneShot("second", Vector3(player_pos.x - 3.0f, player_pos.y + 6.0f, player_pos.z));
		}
		DX12Effect.SetScale("second", Vector3(1.5f, 1.5f, 1.5f));
		DX12Effect.SetRotation("second", Vector3(0.0f, 180.0f, 0.0f));

	}

}
//�G�t�F�N�g3����
void PlayerBase::Attack_Third(const float deltaTime) {
	if (direction_state_mode == Direction_State::RIGHT) {
		if (DX12Effect.CheckAlive("third")) {
			DX12Effect.Stop("third");
			DX12Effect.PlayOneShot("third", Vector3(player_pos.x + 7.0f, player_pos.y + 5.0f, player_pos.z));
		}
		else
		{
			DX12Effect.PlayOneShot("third", Vector3(player_pos.x + 7.0f, player_pos.y + 5.0f, player_pos.z));
		}
	}
	else if (direction_state_mode == Direction_State::LEFT) {
		if (DX12Effect.CheckAlive("third")) {
			DX12Effect.Stop("third");
			DX12Effect.PlayOneShot("third", Vector3(player_pos.x - 7.0f, player_pos.y + 5.0f, player_pos.z));
		}
		else
		{
			DX12Effect.PlayOneShot("third", Vector3(player_pos.x - 7.0f, player_pos.y + 5.0f, player_pos.z));
		}
		DX12Effect.SetRotation("third", Vector3(0.0f, 180.0f, 0.0f));
	}

}




void PlayerBase::Player_Special_Move(const float deltaTime) {
	if (!jump_flag_) {
		if (StatusManager::Instance().ReturnHeart() >= 20) {
			if (DXTK->KeyEvent->pressed.L || DXTK->GamePadEvent->rightShoulder == GamePad::ButtonStateTracker::PRESSED) {
				deathbrow_flag = true;
			}
		}
	}

	if (deathbrow_flag) {
		specialmove_time += deltaTime;
		Blackout_flag = true;

	}

	//�Ó]
	if (Blackout_flag) {
		Transparency += Blackout;
		if (Transparency >= Blackout_max) {
			Transparency = Blackout_max;

		}
	}

	if (specialmove_time >= 0.1f) {
		deathbrow_attack = true;

		Blackout_flag = false;
		DX12Effect.PlayOneShot("deathblow_effect", Vector3(player_pos.x, 10, 0));


	}
	//���]
	if (specialmove_time >= 3.666f)
		bright_flag = true;

	if (bright_flag) {
		Transparency -= Ming_Turn;
		if (Transparency <= 0) {
			Transparency = 0;

			bright_flag = false;

		}
	}

	if (specialmove_time >= 3.9f && !special_attack_flag)
		special_attack_flag = true;

	//�K�E�Z�I��
	if (specialmove_time >= specialmove_time_max) {
		deathbrow_flag = false;
		special_attack_flag = false;
		specialmove_time = 0.0f;

		deathbrow_attack = false;

		//�K�E�Z�Q�[�W���Z�b�g�Ăяo��
		StatusManager::Instance().HeartReset();
	}

}

bool PlayerBase::IsAttack() {

	if (attack_flag) {


		return true;
	}
	return false;
}

	//�A�s�[��
void PlayerBase::Appeal(const float deltaTime)
{
	//�A�s�[��
	if (!jump_flag_) {
		if (!appeil_cool_flag) {
			if (DXTK->KeyState->W || DXTK->GamePadState->triggers.left) {
				appeil_flag = true;
			}
			else
			{
				appeil_flag = false;

				model->SetTrackPosition(APPEIL, 0.0);

				if (!appeil_flag) {
					appeil_cool_flag = true;
				}

				if (direction_state_mode == Direction_State::LEFT) {
					model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
				}

			}
		}
	}

	if (appeil_flag) {
		if (direction_state_mode == Direction_State::RIGHT) {
			SetAnimation(model, APPEIL);
		}
		else if (direction_state_mode == Direction_State::LEFT)
		{
			SetAnimation(model, APPEIL);
			model->SetRotation(Vector3(0.0f, XMConvertToRadians(-90.0f), 0.0f));
		}

		appeil_time += deltaTime;
	}

	if (appeil_time >= appeil_time_max) {//�{�^���b�����Ƃ���NOMAL�ɖ߂�
		appeil_flag = false;
		model->SetTrackPosition(APPEIL, 0.0);
		appeil_cool_flag = true;


		if (direction_state_mode == Direction_State::LEFT) {
			model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
		}
	}

	if (appeil_cool_flag) {
		appeil_cool_time += deltaTime;
	}

	if (appeil_cool_time >= appeil_cool_time_max) {
		appeil_cool_flag = false;
		appeil_cool_time = 0.0f;
		appeil_time = 0.0f;

		if (direction_state_mode == Direction_State::LEFT) {
			model->SetRotation(0.0f, DirectX::XMConvertToRadians(-model_rotetion), 0.0f);
		}
	}
}


void PlayerBase::BrackImage() {
	DX9::SpriteBatch->DrawSimple(deathbrow_sprite.Get(),
		SimpleMath::Vector3(0, 0, 0),
		nullptr,
		DX9::Colors::RGBA(0, 0, 0, Transparency)
	);

}

void PlayerBase::_2DRender()
{
	//if (invincible_flag) {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 0.0f),
	//		DX9::Colors::White,
	//		L"ON"
	//	);
	//} else {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 0.0f),
	//		DX9::Colors::White,
	//		L"OFF"
	//	);
	//}


	//if (cannot_other == CANNOT_OTHER_ATTACK::FIRST) {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 20.0f),
	//		DX9::Colors::White,
	//		L"ON"
	//	);
	//}
	//else {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 20.0f),
	//		DX9::Colors::White,
	//		L"OFF"
	//	);
	//}

	//if (cannot_other == CANNOT_OTHER_ATTACK::SECOND) {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 40.0f),
	//		DX9::Colors::White,
	//		L"ON"
	//	);
	//}
	//else {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 40.0f),
	//		DX9::Colors::White,
	//		L"OFF"
	//	);
	//}

	//if (cannot_other == CANNOT_OTHER_ATTACK::THIRD) {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 60.0f),
	//		DX9::Colors::White,
	//		L"ON"
	//	);
	//}
	//else {
	//	DX9::SpriteBatch->DrawString(font.Get(),
	//		SimpleMath::Vector2(1000.0f, 60.0f),
	//		DX9::Colors::White,
	//		L"OFF"
	//	);
	//}

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 80.0f),
	//	DX9::Colors::White,
	//	L"%d", StatusManager::Instance().ReturnHeart()
	//);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 40.0f),
	//	DX9::Colors::White,
	//	L"%f", appeil_time
	//);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 80.0f),
	//	DX9::Colors::White,
	//	L"%f", effect_generation_time
	//);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 100.0f),
	//	DX9::Colors::Black,
	//	L"%f %f %f", sword_box.Center.x, sword_box.Center.y, sword_box.Center.z
	//);

	//DX9::SpriteBatch->DrawString(font.Get(),
	//	SimpleMath::Vector2(1000.0f, 120.0f),
	//	DX9::Colors::BlueViolet,
	//	L"%d", Transparency
	//);
}