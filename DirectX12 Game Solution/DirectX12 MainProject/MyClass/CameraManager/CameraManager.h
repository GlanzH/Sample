#pragma once

using namespace DirectX;
using namespace DX9;

typedef SimpleMath::Vector3 Vector3;

class CameraManager
{
public:
	bool Initialize();
	int  Update();
	void SetCamera() { DXTK->Direct3D9->SetCamera(camera); }

private:
	CAMERA  camera;
	Vector3 position;

};
