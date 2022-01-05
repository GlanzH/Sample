#include"MyClass/StatusManager/StatusManager.h"
#include"MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/GameSceneManager/SceneManager.h"

void StatusManager::Initialize() {
	//プレイヤーのコンボ
	atk_combo		= 0;
	atk_combo_count = 0;
	atk_combo_time	= 0.0f;
	kill_combo_time = 0.0f;
	atk_combo_flag	= false;

	//オーディエンス
	audience	 = AUDIENCE_START_VALUE;
	now_audience = audience;
	plus_audience_flag = false;

	//パリィ
	heart = 0.0f;
}

int StatusManager::Update(const float deltaTime) {
	if (atk_combo_time > ATK_COMBO_TIME_MAX[atk_combo_count] || atk_combo >= ATK_COMBO_MAX) {
		atk_combo_time  = 0.0f;
		atk_combo_flag  = false;
		atk_combo_count = 0;
		atk_combo = 0;
		
	}

	if (atk_combo_flag) {
		atk_combo_time += deltaTime;
	}

	return 0;
}

void StatusManager::AddCombo(const float deltaTime) {

	atk_combo++;
	atk_combo_time = 0.0f;
	atk_combo_flag = true;

	return;
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

float StatusManager::GetKillComboTime(const float deltaTime) {
	kill_combo_time = std::min(kill_combo_time + deltaTime, KILL_COMBO_TIME_MAX);
	return kill_combo_time;
}

void StatusManager::BonusScore(int kill_combo) {
	switch (kill_combo) {
	case 1:
		AddAudience(20.0f);
		kill_combo_time -= KILL_COMBO_TIME_MAX;
		break;
	case 2:
		AddAudience(40.0f);
		kill_combo_time -= KILL_COMBO_TIME_MAX;
		break;
	case 3:
		AddAudience(80.0f);
		kill_combo_time -= KILL_COMBO_TIME_MAX;
		break;
	case 4:
		AddAudience(160.0f);
		kill_combo_time -= KILL_COMBO_TIME_MAX;
		break;
	case 5:
		AddAudience(320.0f);
		kill_combo_time -= KILL_COMBO_TIME_MAX;
		break;
	default:
		break;
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