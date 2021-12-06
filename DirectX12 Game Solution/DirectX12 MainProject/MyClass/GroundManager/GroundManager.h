#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class GroundManager {
public:
	GroundManager() {};
	~GroundManager() {};

	void LoadAsset();
	void Render();

	DX9::MODEL& GetModel() { return model; }

private:
	DX9::MODEL model;

	const float box_size =   2.0f;
	const float pos_y	 = -25.0f;
};