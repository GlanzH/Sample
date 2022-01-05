#pragma once
#include "Base/pch.h"
#include <DirectXTK9.h>
#include <Base/dxtk.h>

using namespace DirectX;

class UIManager {
public:
	UIManager() {};
	~UIManager() {};

	void LoadAsset();
	void Render(float audience ,float heart);

private:
	DX9::SPRITE audience_empty;
	DX9::SPRITE audience_max;
	
	DX9::SPRITE heart_empty;
	DX9::SPRITE heart_max;

	
	//äœãq
	const float AUDIENCE_UI_POS_X		= 79.0f;
	const float AUDIENCE_UI_POS_Y		= 58.0f;
	const float AUDIENCE_EMPTY_UI_POS_Z = -99.0f;
	const float AUDIENCE_MAX_UI_POS_Z	= -100.0f;

	const int AUDIENCE_MAX_HIGH = 64;

	//ÉnÅ[Ég
	const float HEART_UI_POS_X = 84.0f;
	const float HEART_UI_POS_Y = 137.0f;

	const int HEART_MAX_WIDTH = 89;
	const int HEART_MAX_HIGH  = 89;
};