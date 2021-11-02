#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class PlayerManager;

using namespace DirectX;
using namespace DX9;

class CameraManager
{
public:
	CameraManager() {};
	~CameraManager() {};

	bool Initialize();
	void LoadAsset();
	int  Update(PlayerManager* player,DX9::MODEL& ground);
	void Render(SimpleMath::Vector3 player_position);

private:
	CAMERA  camera;

	SimpleMath::Vector3 position;
	
	const float fixed_pos = 10.0f;
	const float adjust_y  = 100.0f;
};
