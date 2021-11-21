#include"MyClass/StatusManager/StatusManager.h"
#include"MyClass/PlayerManager/PlayerManager.h"

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

void StatusManager::AddVoltage(int volt_size, const float deltaTime) {
	now_volt = volt_size;
	//‘«‚µˆø‚«‚·‚é‘O‚Éƒtƒ‰ƒO‚ð—§‚Ä‚é
	if (voltage < now_volt) {
		plus_flag = true;
	}
	else {
		plus_flag = false;
	}

	if (plus_flag) {
		voltage = std::min((float)voltage + 100 * deltaTime, (float)now_volt);
	}
	else {
		if (voltage > 0.0f) {
			voltage = std::max((float)voltage - 100 * deltaTime, (float)now_volt);
		}
	}

	return;
}