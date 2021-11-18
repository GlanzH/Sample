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
