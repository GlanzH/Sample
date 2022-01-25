#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

class C_Camera
{
public:
	C_Camera() {};
	~C_Camera() {};

	bool Initialize();
	void LoadAsset();
	int  Update(PlayerBase* base,int camera_pos_num, const float deltaTime);
	void Render();

	DX9::CAMERA* GetCamera() { return &camera; }

private:
	DX9::CAMERA  camera;

	SimpleMath::Vector3 position;
	
	enum CameraMode {
		IN_ZOOM,
		OUT_ZOOM
	};

	float camera_z = -10.0f;

	const float position_y = 30.0f;
	const float fixed_pos  = 13.0f;

	const float rotate_degrees = 40.0f;
	const float aspect = 16.0f / 9.0f;

	const float min_screen_range = 1.0f;
	const float max_screen_range = 10000.0f;
};
