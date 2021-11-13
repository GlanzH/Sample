#pragma ones
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};

	void AddCombo(const float deltaTime);
	int Update(const float deltaTime);

	int GetCombo() { return combo; }

	static StatusManager&Instance(){
		static StatusManager instance;
		return instance;
	}
private:
	float combo_time = 0.0f;
	const float combo_time_max = 0.7f;
	int combo = 0;
};