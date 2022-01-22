#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Timer {
public:
	bool Initialize();
	int Update(const float deltaTime);
	void Render();
private:
	DX9::SPRITEFONT font;
};