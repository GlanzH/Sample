#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/EnemyManager/EnemyManager.h"

using namespace DirectX;

class Timer {
public:
	Timer();
	~Timer();
	bool Initialize();
	int Update(EnemyManager* enemy, const float deltaTime);
	void Render();
private:
	DX9::SPRITEFONT font;

	DX9::SPRITE time;
	DX9::SPRITE time_number;

	float time_one_digit;
	int time_two_digit;

	const int TIME_NUM_WIDTH = 56;
	const int TIME_NUM_HIGHT = 70;

	const float TIME_POS_X = 1160.0f;
	const float TIME_POS_Y = 20.0f;

	const float ONE_DIGIT_POS_X = TIME_POS_X + 40;
	const float TWO_DIGIT_POS_X = TIME_POS_X - 10;

	const float TIME_NUM_POS_Y = TIME_POS_Y + 40.0f;


	float stop_frame = 0.0f;
	const float max_stop = 2.f;

	int stage_num = 0;
};