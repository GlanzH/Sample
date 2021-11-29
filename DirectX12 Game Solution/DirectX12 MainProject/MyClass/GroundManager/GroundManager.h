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
	BoundingBox GetBox() { return box; }

private:
	DX9::MODEL model;
	DX9::MODEL collision;

	BoundingBox box;

	const float box_size =   2.0f;
	const float pos_y	 = -25.0f;
	const float pos_z	 =   0.0f;
};