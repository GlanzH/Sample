#include"MyClass/StatusManager/StatusManager.h"
#include"MyClass/PlayerManager/PlayerManager.h"

int StatusManager::Update(const float deltaTime) {
	combo_time += deltaTime;
	if (combo_time > combo_time_max || combo >= combo_max) {
		combo_time = 0.0f;
		combo = 0;
		
	}

	if (volt_add_flag == plus) {
		UpVoltage(deltaTime);
	}
	else
	{
		DownVoltage(deltaTime);
	}

	return 0;
}

void StatusManager::AddCombo(const float deltaTime) {

	combo++;
	combo_time = 0.0f;

	return;
}

void StatusManager::AddVoltage(float volt_size) {
	now_volt += volt_size;	//���݂̃{���e�[�W

	JudgeVolt();

	return;
}

void StatusManager::JudgeVolt() {
	if (voltage < now_volt) {
		volt_add_flag = plus;
	}
	else
	{
		volt_add_flag = minus;
	}

	return;
}

void StatusManager::UpVoltage(const float deltaTime) {
	voltage = std::min((float)voltage + VOL_UPDN_SPEED * deltaTime, (float)now_volt);
	
	return;
}

void StatusManager::DownVoltage(const float deltaTime) {
	voltage = std::max((float)voltage - VOL_UPDN_SPEED * deltaTime, (float)now_volt);
	if (voltage < 0.0f) {
		voltage = 0.0f;
	}

	return;
}

void StatusManager::ParryCount() {
	parry++;
	return;
}

void StatusManager::ParryReset() {
	parry = 0.0f;
	return;
}