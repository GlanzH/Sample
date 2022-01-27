#include"MyClass/StatusManager/StatusManager.h"
#include "MyClass/UIManager/UIManager.h"

void StatusManager::Initialize() {
	//�G���j�R���{
	combo = 0;
	combo_time = 0.0f;
	combo_flag	= false;
	combo_miss_flag = false;

	//�A�j���[�V����
	anime_flag = false;

	//�X�R�A
	score = SCORE_START_VALUE;
	now_score = score;
	add_score_size = 0.0f;
	enemy_num = 0.0f;
	plus_score_flag = false;
	good_flag = false;

	//�E�F�[�u
	wave = 0;
	wave_time = 0.0f;
	once_exec_time = 0.0f;
	wave_change_flag = false;
}

void StatusManager::Update(const float deltaTime) {
	CalcScore(deltaTime);
	ComboTime(deltaTime);
}

void StatusManager::SetAddScore(float score_size) {
	add_score_size = score_size;
	now_score += add_score_size;	//���݂̃X�R�A

	now_score = std::clamp(now_score, 0.0f, SCORE_MAX_VALUE);

	if (score < now_score) {
		plus_score_flag = true;
	}
	else
	{
		plus_score_flag = false;
	}

	if (add_score_size < 0) {
		good_flag = false;
	}
	else {
		good_flag = true;
	}

	UIManager::Instance().PlayUIEffect();

	return;
}


void StatusManager::CalcScore(const float deltaTime) {
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
	score = std::min(score + SCORE_UPDN_SPEED * deltaTime, now_score);
	return;
}

void StatusManager::ScoreDown(const float deltaTime) {
	score = std::max(score - SCORE_UPDN_SPEED * deltaTime, now_score);
	return;
}

void StatusManager::AddHitCombo() {
	combo++;
}

void StatusManager::AddHitComboTime() {
	combo_time = COMBO_TIME_NUM;
	combo_flag = true;
	UIManager::Instance().ResetAnimeFrame();
	ResetaAnimeFlag();
	anime_flag = true;

	return;
}

void StatusManager::ComboTime(const float deltaTime) {
	combo_time = std::max(combo_time - deltaTime, 0.0f);
	if (combo_time <= 0.0f) {
		combo_miss_flag = true;
		ResetHitCombo();
	}
	return;
}

void StatusManager::ResetHitCombo() {
	if (!combo_miss_flag) {
		ComboScore();
	}
	combo = 0;
	combo_miss_flag = false;
	combo_flag = false;
	return;
}

void StatusManager::ComboScore() {
	switch (combo) {
	case 1:
		SetAddScore(10.0f);
		break;
	case 2:
		SetAddScore(30.0f);
		break;
	case 3:
		SetAddScore(60.0f);
		break;
	case 4:
		SetAddScore(100.0f);
		break;
	default:
		if (combo >= 5) {
			float BonusScore = (combo * 50.0f) - 100.0f;
			SetAddScore(BonusScore);
		}
		break;
	}
	
	return;
}

void StatusManager::SetWave(int wave_num) {
	wave = wave_num;

	switch (wave)
	{
	case 1:
		wave_time = TUTORIAL_TIME;
		once_exec_time = wave_time - 0.01;
		break;

	case 2:
		wave_time = TUTORIAL_TIME;
		once_exec_time = wave_time - 0.01;
		break;

	case 3:
		wave_time = TUTORIAL_TIME;
		once_exec_time = wave_time - 0.01;
		break;

	default:
		if (wave >= 4) {
			wave_time = WAVE_TIME_LIMIT_TWO;
			once_exec_time = wave_time - 0.01;
		}
		break;
	}

	wave_change_flag = false;
	return;
}

void StatusManager::WaveTimeLimit(const float deltaTime) {
	wave_time = std::max(wave_time - deltaTime, 0.0f);

	if (wave_time <= 0.0f) {
		ResetWaveTime();
	}
	return;
}

void StatusManager::ResetWaveTime() {
	if (!wave_change_flag) {
		float TimeBonus = wave_time * 5.0f;
		float LostEnemy = enemy_num * -30.0f;
		SetAddScore(TimeBonus + LostEnemy);
		wave_time = 0.0f;
		wave_change_flag = true;
	}
}