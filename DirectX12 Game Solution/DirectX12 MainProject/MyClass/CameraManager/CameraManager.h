#pragma once

using namespace DirectX;
using namespace DX9;

typedef SimpleMath::Vector3 Vector3;

class CameraManager
{
public:
	bool Initialize();
	void Render(Vector3 player_position);

private:
	CAMERA  camera;
	Vector3 position;
	
	const float view_y = 10.0f;
};
