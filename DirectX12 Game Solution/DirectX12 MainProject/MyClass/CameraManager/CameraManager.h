#pragma once

using namespace DirectX;

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	bool Initialize();
	int  Update();
	void Render();

private:
	
};
