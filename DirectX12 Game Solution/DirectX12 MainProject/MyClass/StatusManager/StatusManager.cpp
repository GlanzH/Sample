#include"MyClass/StatusManager/StatusManager.h"
#include"MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/GameSceneManager/SceneManager.h"

void StatusManager::Initialize() {
	//コンボ
	combo_time	= 0.0f;
	combo		= 0;
	combo_flag	= false;
	combo_count = 0;

	//オーディエンス
	audience	 = AUDIENCE_START_VALUE;
	now_audience = audience;

	//パリィ
	heart = 0.0f;
}

int StatusManager::Update(const float deltaTime) {
	if (combo_time > COMBO_TIME_MAX[combo_count] || combo >= COMBO_MAX) {
		combo_time  = 0.0f;
		combo_flag  = false;
		combo_count = 0;
		combo = 0;
		
	}

	if (combo_flag) {
		combo_time += deltaTime;
	}

	return 0;
}

void StatusManager::AddCombo(const float deltaTime) {
	combo++;
	combo_time = 0.0f;
	combo_flag = true;

	return;
}

void StatusManager::AddAudience(float add_size) {
	now_audience -= add_size;	//現在のオーディエンス
	return;
}


void StatusManager::DownAudience(const float deltaTime) {
	audience = std::max(audience - AUIDENCE_DN_SPEED * deltaTime, now_audience);
	if (audience < 0.0f) {
		audience = 0.0f;
		SceneManager::Instance().Update(deltaTime);
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