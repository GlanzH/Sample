#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class CameraManager
{
public:
	CameraManager() {};
	~CameraManager() {};

	bool Initialize();
	void LoadAsset();
	int  Update(SimpleMath::Vector3 pos);
	void Render();

	DX9::CAMERA GetCamera() { return camera; }

private:
	DX9::CAMERA  camera;

	SimpleMath::Vector3 position;
	
	const float position_y = 30.0f;
	const float fixed_pos  = 10.0f;

	const float rotate_degrees = 40.0f;
	const float aspect = 16.0f / 9.0f;

	const float min_screen_range = 1.0f;
	const float max_screen_range = 10000.0f;
};
