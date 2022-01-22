#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Timer {
public:
	Timer();
	~Timer();
	bool Initialize();
	int Update(const float deltaTime);
	void Render();
private:
	DX9::SPRITEFONT font;

	float stop_frame = 0.0f;
	const float max_stop = 2.f;

	const int init_stage_num = 1;
	int stage_num = init_stage_num;
};