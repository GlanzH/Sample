#include"MyClass/StatusManager/StatusManager.h"
#include"MyClass/PlayerManager/PlayerManager.h"

void Initialize() {

}

int StatusManager::Update(const float deltaTime) {
	combo_time += deltaTime;
	if (combo_time > combo_time_max || combo >= combo_max) {
		combo_time = 0.0f;
		combo = 0;
		
	}

	return 0;
}

void StatusManager::AddCombo(const float deltaTime) {

	combo++;
	combo_time = 0.0f;

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
	}

	return;
}

void StatusManager::HeartCount() {
	if (heart < 20.0f) {
		heart++;
	}
	return;
}

void StatusManager::HeartReset() {
	if (heart >= 20.0f) {
		heart = 0.0f;
	}
	return;
}