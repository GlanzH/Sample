#include"MyClass/StatusManager/StatusManager.h"
#include "MyClass/UIManager/UIManager.h"

void StatusManager::Initialize() {
	//敵撃破コンボ
	kill_combo = 0;
	kill_combo_time = 0.0f;
	kill_combo_flag	= false;

	//アニメーション
	anime_flag = false;

	//スコア
	score = SCORE_START_VALUE;
	now_score = score;
	add_score_size = 0.0f;
	enemy_num = 0.0f;
	plus_score_flag = false;
	good_flag = false;

	//ウェーブ
	wave = 0;
	wave_time = 0.0f;
	wave_change_flag = false;
}

void StatusManager::Update(const float deltaTime) {
	CalcScore(deltaTime);
	KillComboTime(deltaTime);
}

void StatusManager::SetAddScore(float score_size) {
	add_score_size = score_size;
	now_score += add_score_size;	//現在のスコア

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

void StatusManager::AddKillCombo() {
	kill_combo++;
	kill_combo_time = 5.0f;	//5秒追加
	kill_combo_flag = true;
	UIManager::Instance().ResetAnimeFrame();
	ResetaAnimeFlag();
	anime_flag = true;

	return;
}

void StatusManager::KillComboTime(const float deltaTime) {
	kill_combo_time = std::max(kill_combo_time - deltaTime, 0.0f);
	if (kill_combo_time <= 0.0f) {
		ResetKillCombo();
	}
	return;
}

void StatusManager::ResetKillCombo() {
	ComboScore();
	kill_combo = 0;
	kill_combo_flag = false;
	return;
}

void StatusManager::ComboScore() {
	switch (kill_combo) {
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
		if (kill_combo >= 5) {
			float BonusScore = (kill_combo * 50.0f) - 100.0f;
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
		wave_time = WAVE_TIME_LIMIT_ONE;
		break;

	case 2:
		wave_time = WAVE_TIME_LIMIT_ONE;
		break;

	case 3:
		wave_time = WAVE_TIME_LIMIT_ONE;
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