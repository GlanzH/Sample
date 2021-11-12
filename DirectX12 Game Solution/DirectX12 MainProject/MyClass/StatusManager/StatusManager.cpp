#include"MyClass/StatusManager/StatusManager.h"
#include"MyClass/PlayerManager/PlayerManager.h"

int StatusManager::AddCombo(const float deltaTime) {
	
	
	if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent->x) {
		combo_flag = true;
	}

	if (combo_flag && combo_time < combo_time_max) {
		combo_time += deltaTime;
		if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent->x)
			combo++;
	}
	else
	{
		combo_flag = false;
		combo_time = 0.0f;
		combo = 0;
	}


	return 0;
}
