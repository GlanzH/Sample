#include"MyClass/StatusManager/StatusManager.h"
#include "MyClass/UIManager/UIManager.h"



void StatusManager::Initialize() {
	//�G���j�R���{
	combo = 0;
	combo_time = 0.0f;
	combo_time_num = 0.0f;
	combo_flag = false;
	combo_miss_flag = false;
	combo_time_flag = true;

	//�A�j���[�V����
	anime_flag = false;

	//�X�R�A
	coin_num = 0;
	score = SCORE_START_VALUE;
	now_score = score;
	enemy_num = 0.0f;
	plus_score_flag = false;
	coin_get_flag = false;

	//�E�F�[�u
	wave = 0;
	wave_time = 0.0f;
	once_exec_time = 0.0f;
	wave_change_flag = false;
}

void StatusManager::Update(const float deltaTime, int remain_enemy) {
	CalcScore(deltaTime);
	ComboTime(deltaTime);
}

void StatusManager::SetAddScore(float score_size) {
	//�X�R�A��ݒ肷��
	now_score += score_size;

	now_score = std::clamp(now_score, 0.0f, SCORE_MAX_VALUE);

	if (30 == score_size) {
		coin_num++;
		coin_get_flag = true;
	}

	if (score < now_score) {
		plus_score_flag = true;
	}
	else
	{
		plus_score_flag = false;
	}

	return;
}

void StatusManager::CalcScore(const float deltaTime) {
	//�X�R�A��������
	if (plus_score_flag) {
		ScoreUp(deltaTime);
	}
	else
	{
		ScoreDown(deltaTime);
	}
	return;
}

void StatusManager::ScoreUp(const float deltaTime) {
	//�X�R�A�𑝂₷
	score = std::min(score + SCORE_UPDN_SPEED * deltaTime, now_score);
	return;
}

void StatusManager::ScoreDown(const float deltaTime) {
	//�X�R�A�����炷
	score = std::max(score - SCORE_UPDN_SPEED * deltaTime, now_score);
	return;
}

void StatusManager::AddHitCombo() {
	//�R���{�𑝂₷
	combo++;
	if (combo >= 10) {
		combo = 10;
	}
}

void StatusManager::AddHitComboTime() {
	//�R���{�p�����Ԃ𑝂₷
	//�R���{���ɂ���Čp�����Ԃ�ϓ�����
	float minus_combo_time = -0.6f * (combo - 1);
	if (combo < 6) {
		combo_time_num = 6.0f + minus_combo_time;
	}
	else {
		combo_time_num = 3.0f;
	}
	combo_time = combo_time_num;
	combo_flag = true;
	UIManager::Instance().ResetAnimeFrame();
	ResetaAnimeFlag();
	anime_flag = true;

	return;
}

void StatusManager::ComboTime(const float deltaTime) {
	//�t���O�������Ă�����R���{�p�����Ԃ����炷
	if (combo_time_flag) {
		combo_time = std::max(combo_time - deltaTime, 0.0f);
	}

	if (combo_time <= 0.0f) {
		combo_miss_flag = true;
		ResetHitCombo();
	}
	return;
}

void StatusManager::ResetHitCombo() {
	//�R���{�������Z�b�g����
	if (!combo_miss_flag) {
		ComboScore();
	}
	combo = 0;
	combo_miss_flag = false;
	combo_flag = false;
	combo_time = 0.0f;
	combo_time_flag = true;
	return;
}

void StatusManager::ComboScore() {
	//�R���{���ɉ������ϋq�̃��A�N�V�����ω�
	switch (combo) {
	case 1:
	case 2:
	case 3:
		UIManager::Instance().SetAudienceState(1);
		break;

	default:
		if (combo >= 4) {
			UIManager::Instance().PlayCracker();
			UIManager::Instance().SetAudienceState(2);
		}
		break;
	}

	return;
}

void StatusManager::SetWave(int wave_num) {
	//�E�F�[�u���Ƃ̎��Ԑݒ�
	wave = wave_num;

	switch (wave)
	{
	case 1:
	case 2:
	case 3:
		wave_time = STAGE_ONE_TIME;
		once_exec_time = wave_time - 0.01f;
		break;

	default:
		if (wave >= 4) {
			wave_time = STAGE_TWO_TIME;
			once_exec_time = wave_time - 0.01f;
		}
		break;
	}

	wave_change_flag = false;
	return;
}

void StatusManager::WaveTimeLimit(const float deltaTime) {
	//�E�F�[�u�̎��Ԃ����炷
	wave_time = std::max(wave_time - deltaTime, 0.0f);
	return;
}

void StatusManager::ResetWaveTime() {
	//�E�F�[�u�̎��Ԃ����Z�b�g���ăX�R�A�𑝌�������
	if (!wave_change_flag) {
		float LostEnemy = enemy_num * -30.0f;
		SetAddScore(LostEnemy);
		wave_time = 0.0f;
		wave_change_flag = true;
	}
}