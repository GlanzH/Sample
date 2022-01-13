#include"MyClass/StatusManager/StatusManager.h"
#include"MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/GameSceneManager/SceneManager.h"

void StatusManager::Initialize() {
	//プレイヤーのコンボ
	kill_combo = 0;
	kill_combo_time = 5.0f;
	kill_combo_flag	= false;

	//オーディエンス
	audience	 = AUDIENCE_START_VALUE;
	now_audience = audience;
	plus_audience_flag = false;

	//パリィ
	heart = 0.0f;

	//ウェーブ
	wave = 0;
	wave_time = 0.0f;
	wave_change_flag = false;
}

void StatusManager::AddAudience(float add_size) {
	now_audience += add_size;	//現在のオーディエンス

	now_audience = std::clamp(now_audience, 0.0f, AUDIENCE_MAX_VALUE);

	if (audience <= now_audience) {
		plus_audience_flag = true;
	}
	else
	{
		plus_audience_flag = false;
	}

	return;
}


void StatusManager::CalcAudience(const float deltaTime) {
	if (plus_audience_flag) {
		UpAudience(deltaTime);
	}
	else
	{
		DownAudience(deltaTime);
	}
	return;
}

void StatusManager::UpAudience(const float deltaTime) {
	audience = std::min(audience + AUIDENCE_DN_SPEED * deltaTime, now_audience);
	return;
}

void StatusManager::DownAudience(const float deltaTime) {
	audience = std::max(audience - AUIDENCE_DN_SPEED * deltaTime, now_audience);
	return;
}

void StatusManager::AddKillCombo() {
	kill_combo++;
	kill_combo_time = 5.0f;
	kill_combo_flag = true;
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
	kill_combo = 0;
	kill_combo_flag = false;
	return;
}


void StatusManager::BonusScore() {
	switch (kill_combo) {
	case 1:
		AddAudience(5.0f);
		break;
	case 2:
		AddAudience(10.0f);
		break;
	case 3:
		AddAudience(25.0f);
		break;
	case 4:
		AddAudience(50.0f);
		break;
	case 5:
		AddAudience(100.0f);
		break;
	case 6:
		AddAudience(150.0f);
	}
	return;
}

void StatusManager::HeartCount() {
	if (heart < HEART_MAX) {
		heart++;
	}
	return;
}

void StatusManager::HeartReset() {
	if (heart >= HEART_MAX) {
		heart = 0.0f;
	}
	return;
}

void StatusManager::SetWave(int wave_num) {
	wave = wave_num;

	switch (wave)
	{
	case 1:
		wave_time = 30.0f;
		break;
	}

	wave_change_flag = false;
	return;
}

void StatusManager::WaveTimeLimit(const float deltaTime) {
	wave_time = std::max(wave_time - deltaTime, 0.0f);

	if (wave_time <= 0.0f) {
		wave_change_flag = true;
	}
	return;
}