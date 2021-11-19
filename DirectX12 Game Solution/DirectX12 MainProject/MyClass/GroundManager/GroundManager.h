#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class GroundManager {
public:
	GroundManager() {};
	~GroundManager() {};

	void LoadAsset();
	void Render();

private:
	DX9::MODEL model;

	const float pos_z = 50.0f;
};