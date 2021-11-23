#pragma once
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
	const float combo_time_max =  0.6f;
	int combo = 0;
	const int combo_max = 4;
};