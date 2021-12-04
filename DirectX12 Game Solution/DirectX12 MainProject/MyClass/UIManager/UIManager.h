#pragma once
#include "Base/pch.h"
#include <DirectXTK9.h>
#include <Base/dxtk.h>

using namespace DirectX;

class UIManager {
public:
	UIManager() {};
	~UIManager() {};

	bool Initialize();
	void LoadAsset();
	int Update(const float deltaTime);
	int GetTensionCount(int count) { return 0; }
	void Render(float distance ,float heart);

private:
	DX9::SPRITE audience_empty;
	DX9::SPRITE audience_max;
	DX9::SPRITE heart_empty;
	DX9::SPRITE heart_max;

	const float AUDIENCE_UI_POS_X = 40.0f;
	const float AUDIENCE_UI_POS_y = 600.0f;

	const float HEART_UI_POS_X = 104.0f;
	const float HEART_UI_POS_Y = 91.0f;
	const int HEART_MAX_WIDTH = 104;
	const int HEART_MAX_HIGH  = 91;

	float AUDIeNCE_MAX_WIDTH = 1183;
	const int AUDIENCE_MAX_HIGH = 61;

	float audience;

};