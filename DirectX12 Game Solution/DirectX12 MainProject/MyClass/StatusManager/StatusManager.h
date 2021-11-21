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

	void AddVoltage(int volt_size, const float deltaTime);
	float RenderVolt() { return voltage; }

private:
	float combo_time = 0.0f;
	const float combo_time_max =  1.5f;
	int combo = 0;
	const int combo_max = 3;

	int	  now_volt = 50;		//現在のボルテージ最大値
	float voltage  = now_volt;	//now_voltに追加していく値

	bool plus_flag = false;
	
};