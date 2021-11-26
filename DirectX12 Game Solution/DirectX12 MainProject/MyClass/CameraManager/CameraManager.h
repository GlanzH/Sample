#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class PlayerBase;

using namespace DirectX;
using namespace DX9;

class CameraManager
{
public:
	CameraManager() {};
	~CameraManager() {};

	bool Initialize();
	void LoadAsset();
	int  Update(SimpleMath::Vector3 pos);
	void Render();

private:
	CAMERA  camera;

	SimpleMath::Vector3 position;
	
	const float position_y = 30.0f;
	const float fixed_pos  = 10.0f;
};
