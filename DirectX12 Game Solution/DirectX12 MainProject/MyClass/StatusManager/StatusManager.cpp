#include"MyClass/StatusManager/StatusManager.h"
#include "MyClass/UIManager/UIManager.h"



void StatusManager::Initialize() {
	//敵撃破コンボ
	combo = 0;
	combo_time = 0.0f;
	combo_flag	= false;
	combo_miss_flag = false;

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
	once_exec_time = 0.0f;
	wave_change_flag = false;
}

void StatusManager::Update(const float deltaTime, int remain_enemy) {
	CalcScore(deltaTime);
	ComboTime(deltaTime);
	enemy_num = remain_enemy;
}

void StatusManager::SetAddScore(float score_size) {
	//スコアを設定する
	add_score_size = score_size;
	now_score += add_score_size;

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

	if (add_score_size != 0.0f) {
		UIManager::Instance().PlayUIEffect();
	}
	return;
}


void StatusManager::CalcScore(const float deltaTime) {
	//スコア増減判定
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
	//スコアを増やす
	score = std::min(score + SCORE_UPDN_SPEED * deltaTime, now_score);
	return;
}

void StatusManager::ScoreDown(const float deltaTime) {
	//スコアを減らす
	score = std::max(score - SCORE_UPDN_SPEED * deltaTime, now_score);
	return;
}

void StatusManager::AddHitCombo() {
	//コンボを増やす
	combo++;
}

void StatusManager::AddHitComboTime() {
	//コンボ継続時間を増やす
	combo_time = COMBO_TIME_NUM;
	combo_flag = true;
	UIManager::Instance().ResetAnimeFrame();
	ResetaAnimeFlag();
	anime_flag = true;

	return;
}

void StatusManager::ComboTime(const float deltaTime) {
	//コンボ継続時間を減らす
	combo_time = std::max(combo_time - deltaTime, 0.0f);
	if (combo_time <= 0.0f) {
		combo_miss_flag = true;
		ResetHitCombo();
	}
	return;
}

void StatusManager::ResetHitCombo() {
	//コンボ数をリセットする
	if (!combo_miss_flag) {
		ComboScore();
	}
	combo = 0;
	combo_miss_flag = false;
	combo_flag = false;
	return;
}

void StatusManager::ComboScore() {
	//コンボ数に応じた観客のリアクション変化
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
	//ウェーブごとの時間設定
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
	//ウェーブの時間を減らす
	wave_time = std::max(wave_time - deltaTime, 0.0f);
	return;
}

void StatusManager::ResetWaveTime() {
	//ウェーブの時間をリセットしてスコアを増減させる
	if (!wave_change_flag) {
		float TimeBonus = wave_time * 5.0f;
		float LostEnemy = enemy_num * -30.0f;
		SetAddScore(TimeBonus + LostEnemy);
		wave_time = 0.0f;
		wave_change_flag = true;
	}
}