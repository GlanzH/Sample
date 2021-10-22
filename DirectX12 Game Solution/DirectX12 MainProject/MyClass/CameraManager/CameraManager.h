#pragma once

using namespace DirectX;
using namespace DX9;

typedef SimpleMath::Vector3 Vector3;

class CameraManager
{
public:
	bool Initialize();
	int  Update();
	void Render();

private:
	CAMERA  camera;
	Vector3 position;

	const Vector3 vector_up = Vector3(0.0f, 1.0f, 0.0f);
};
