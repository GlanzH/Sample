#pragma once
#include "MyClass/PlayerManager/PlayerManager.h"

using namespace DirectX;
using namespace DX9;

class CameraManager
{
public:
	bool Initialize();
	int  Update();
	void Render(SimpleMath::Vector3 player_position);

private:
	CAMERA  camera;
	SimpleMath::Vector3 position;
	
	const float view_y = 10.0f;
};
