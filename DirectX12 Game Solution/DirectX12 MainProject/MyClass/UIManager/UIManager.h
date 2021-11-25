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
	void Render(float voltage, float parry);

private:
	DX9::SPRITE volt_empty;
	DX9::SPRITE volt_max;
	DX9::SPRITE sword_empty;
	DX9::SPRITE sword_max;
};