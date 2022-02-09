#include "MyClass/UIManager/UIManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/ResourceManager/ResourceManager.h"

void UIManager::Initialize() {
	score_width = 0.0;
	combo_anime = 0.0f;
	combo_gauge_width = 0.0f;
	combo_num = 0;
	combo_one_digit = 0;
	combo_two_digit = 0;
	combo_digit_up_flag = false;
	cracker_se = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/Directing/cracker.wav");

	effect_handle = 0;

	enemy_max_num = 0;
	enemy_dead_width = 0;
	enemy_pos_x = 0.0f;
	enemy_pos_y = 0.0f;

	audience_pos = SimpleMath::Vector3(600.0f, 500.0f, 0.0f);
	rev_audience_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	audience_anim = 0;
	state_reset_time = 0.0f;

	applause = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/Audience/applause.wav");
	excitement = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/Audience/excitement.wav");

	DX12Effect2D.Initialize();

	camera.SetView(SimpleMath::Vector3(0.0f, 13.0f, -20.0f), SimpleMath::Vector3::Zero);
	camera.SetPerspectiveFieldOfView(XMConvertToRadians(40.0f), 16.0f / 9.0f, 1.0f, 10000.0f);

	DX12Effect2D.SetCamera(&camera);
}

void UIManager::LoadAsset() {
	score_gauge_empty = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Score/scoreui_coin_bottom.png");
	score_gauge_max = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Score/scoreui_coin_top.png");

	combo_base = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Combo/Combo_Anim.png");
	combo_gauge = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Combo/combo_gauge.png");
	combo = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Combo/COMBO.png");
	combo_number = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Combo/numbers_combo_h.png");

	cracker_effect = DX12Effect2D.Create(L"Effect\\UIEffect\\cracker\\cracker.efk", "cracker");

	enemy = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Enemy/Enemy.png");
	enemy_alive = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Enemy/Enemy_h.png");
	enemy_dead = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Enemy/Enemy_dead_h.png");

	audience_normal = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Audience/hyouka1.png");
	audience_hard = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Audience/hyouka2.png");
	audience_very_hard = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Audience/hyouka3.png");
	rev_audience_normal = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Audience/hyouka1_rev.png");
	rev_audience_hard = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Audience/hyouka2_rev.png");
	rev_audience_very_hard = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Audience/hyouka3_rev.png");
}

void UIManager::Update(const float deltaTime, int enemy_num, int enemy_death) {
	Animation(deltaTime);
	DX12Effect2D.Update(deltaTime);
	combo_num = StatusManager::Instance().GetHitCombo();
	score_width = SCORE_MIN_WIDTH + (int)StatusManager::Instance().GetScoreGauge();
	combo_anime = COMBO_BASE_HIGHT * (int)combo_anime_frame;
	combo_gauge_width = COMBO_GAUGE_DIVIDE * StatusManager::Instance().GetHitComboTime();

	enemy_max_num = enemy_num;
	enemy_dead_num = enemy_death;

	//�R���{��2���\���m�F
	if (combo_num <= 9.0f) {
		combo_digit_up_flag = false;
	}
	else {
		combo_digit_up_flag = true;
	}

	//�R���{��2���\��������
	if (!combo_digit_up_flag) {
		combo_one_digit = COMBO_NUM_WIDTH * combo_num;
	}
	else {
		combo_one_digit = COMBO_NUM_WIDTH * (combo_num % 10);
		combo_two_digit = COMBO_NUM_WIDTH * (combo_num / 10);
	}


	//�ϋq�̃A�j���[�V����
	audience_anim += 60 * deltaTime;
	if (audience_anim > 11)
		audience_anim = 0;

	if (audience_state != NORMAL) {
		state_reset_time += deltaTime;
	}
	if (state_reset_time > 5.0f) {
		audience_state = NORMAL;
		state_reset_time = 0.0f;
	}

}

void UIManager::Render() {
	//�R�C���Q�[�W
	DX9::SpriteBatch->DrawSimple(
		score_gauge_empty.Get(),
		SimpleMath::Vector3(SCORE_POS_X, SCORE_POS_Y, SCORE_EMPTY_POS_Z)
	);
	DX9::SpriteBatch->DrawSimple(
		score_gauge_max.Get(),
		SimpleMath::Vector3(SCORE_POS_X, SCORE_POS_Y, SCORE_MAX_POS_Z),
		RectWH(0, 0, score_width, SCORE_MAX_HIGHT)
	);

	if (StatusManager::Instance().GetComboFlag()) {
		//�R���{�����o��
		DX9::SpriteBatch->DrawSimple(
			combo_base.Get(),
			SimpleMath::Vector3(COMBO_BASE_POS_X, COMBO_BASE_POS_Y, 0.0f),
			RectWH(0, combo_anime, COMBO_BASE_WIDTH, COMBO_BASE_HIGHT)
		);

		//�R���{�Q�[�W
		DX9::SpriteBatch->DrawSimple(
			combo_gauge.Get(),
			SimpleMath::Vector3(COMBO_GAUGE_POS_X, COMBO_GAUGE_POS_Y, 0.0f),
			RectWH(0, 0, combo_gauge_width, COMBO_GAUGE_HIGHT)
		);

		//�R���{����
		DX9::SpriteBatch->DrawSimple(
			combo.Get(),
			SimpleMath::Vector3(COMBO_POS_X, COMBO_POS_Y, 0.0f)
		);


		//�R���{��(1��)
		DX9::SpriteBatch->DrawSimple(
			combo_number.Get(),
			SimpleMath::Vector3(COMBO_ONE_DIGIT_X, COMBO_ONE_DIGIT_Y, 0.0f),
			RectWH(combo_one_digit, 0, COMBO_NUM_WIDTH, COMBO_NUM_HIGHT)
		);

		if (combo_digit_up_flag) {
			//�R���{��(2��)
			DX9::SpriteBatch->DrawSimple(
				combo_number.Get(),
				SimpleMath::Vector3(COMBO_TWO_DIGIT_X, COMBO_TWO_DIGIT_Y, 0.0f),
				RectWH(combo_two_digit, 0, COMBO_NUM_WIDTH, COMBO_NUM_HIGHT)
			);
		}
	}

	//�G�l�~�[(����)
	DX9::SpriteBatch->DrawSimple(
		enemy.Get(),
		SimpleMath::Vector3(1000.0f, 30.0f, 0.0f)
	);

	// �����Ă�G
	int enemy_icon_count = 0;
	for (int i = enemy_icon_count; i < enemy_max_num - enemy_dead_num; ++i) {
		enemy_pos_x = 42 * (i % 10);
		enemy_pos_y = 42 * (i / 10);
		DX9::SpriteBatch->DrawSimple(
			enemy_alive.Get(),
			SimpleMath::Vector3(ENEMY_MIN_POS_X + enemy_pos_x, 50.0f + enemy_pos_y, 0.0f)
		);
		++enemy_icon_count;
	}
	// �|�����G
	for (int i = enemy_icon_count; i < enemy_max_num; ++i) {
		enemy_pos_x = 42 * (i % 10);
		enemy_pos_y = 42 * (i / 10);
		DX9::SpriteBatch->DrawSimple(
			enemy_dead.Get(),
			SimpleMath::Vector3(ENEMY_MIN_POS_X + enemy_pos_x, 50.0f + enemy_pos_y, 0.0f)
		);
		++enemy_icon_count;
	}

	//3D�̃J�������W��2D�ɕϊ����ĕ`�悷��
	audience_pos = DXTK->Direct3D9->WorldToScreenPoint(XMFLOAT3(0.0f, 3.0f, 30.0f), *ui_camaera);
	rev_audience_pos = DXTK->Direct3D9->WorldToScreenPoint(XMFLOAT3(0.0f, 2.0f, 30.0f), *ui_camaera);
	audience_pos.z = 10.0f;
	rev_audience_pos.z = 10.0f;
	float add_pos = 0.0f;
	for (int i = 0; i < 2; ++i) {
		//�ϋq�����W�����炵�����`��
		add_pos = 1388 * i;
		switch (audience_state)
		{
		case NORMAL:
			DX9::SpriteBatch->DrawSimple(
				audience_normal.Get(),
				SimpleMath::Vector3(audience_pos.x - add_pos, audience_pos.y, audience_pos.z),
				RectWH(0, 180 * audience_anim, 1388, 180)
			);

			DX9::SpriteBatch->DrawSimple(
				rev_audience_normal.Get(),
				SimpleMath::Vector3(rev_audience_pos.x - add_pos, rev_audience_pos.y, rev_audience_pos.z),
				RectWH(0, 180 * audience_anim, 1388, 180)
			);
			break;

		case HARD:
			DX9::SpriteBatch->DrawSimple(
				audience_hard.Get(),
				SimpleMath::Vector3(audience_pos.x - add_pos, audience_pos.y, audience_pos.z),
				RectWH(0, 180 * audience_anim, 1388, 180)
			);

			DX9::SpriteBatch->DrawSimple(
				rev_audience_hard.Get(),
				SimpleMath::Vector3(rev_audience_pos.x - add_pos, rev_audience_pos.y, rev_audience_pos.z),
				RectWH(0, 180 * audience_anim, 1388, 180)
			);
			break;

		case VERY_HARD:
			DX9::SpriteBatch->DrawSimple(
				audience_very_hard.Get(),
				SimpleMath::Vector3(audience_pos.x - add_pos, audience_pos.y, audience_pos.z),
				RectWH(0, 180 * audience_anim, 1388, 180)
			);

			DX9::SpriteBatch->DrawSimple(
				rev_audience_very_hard.Get(),
				SimpleMath::Vector3(rev_audience_pos.x - add_pos, rev_audience_pos.y, rev_audience_pos.z),
				RectWH(0, 180 * audience_anim, 1388, 180)
			);
			break;
		}
	}

}

void UIManager::Animation(const float deltaTime) {
	if (StatusManager::Instance().GetAnimeFlag()) {
		combo_anime_frame += 30.0f * deltaTime;
	}
	else {
		ResetAnimeFrame();
	}

	if (combo_anime_frame > 9.0f) {
		StatusManager::Instance().ResetaAnimeFlag();
		ResetAnimeFrame();
	}
	return;
}

void UIManager::ResetAnimeFrame() {
	combo_anime_frame = 0.0f;
	return;
}

void UIManager::PlayCracker() {
	//�N���b�J�[�G�t�F�N�g�̍Đ�
	effect_handle = DX12Effect2D.Play(cracker_effect, Vector3(0.0f, 0.0f, 0.0f));
	DX12Effect2D.SetPosition(effect_handle, Vector3(0.0f, 12.0f, 7.0f));
	cracker_se->Play();
}

void UIManager::EfkRender()
{
	DX12Effect2D.SetCameraPosition(&camera);
	DX12Effect2D.Renderer();
}

void UIManager::SetAudienceState(int state) {
	//�ϋq�̏�Ԑݒ�ASE�̍Đ�
	switch (state) {
	case HARD:
		audience_state = HARD;
		applause->Play();
		break;

	case VERY_HARD:
		audience_state = VERY_HARD;
		excitement->Play();
		break;

	default:
		break;
	}
	state_reset_time = 0.0f;
}
