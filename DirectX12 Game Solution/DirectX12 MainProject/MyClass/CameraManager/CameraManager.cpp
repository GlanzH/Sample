#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CameraManager.h"

bool CameraManager::Initialize() {
	//カメラの位置
	camera->SetView(Vector3(0.0f, 0.0f, -10.0f),Vector3(0.0f, 0.0f, 0.0f));

	//カメラの向き・映す距離
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(90.0f), 16.0f / 9.0f, 1.0f, 10000.0f
	);

	return true;
}

int CameraManager::Update() {
	return 0;
}

void CameraManager::Render() {
	//camera->SetViewLookAt(mikoto->GetPosition() + SimpleMath::Vector3(0.0f, 0.0f, -1.0f) * 30
	//	+ SimpleMath::Vector3(0.0f, 6.0f, 2.0f), mikoto->GetPosition(), vector_up);

	DXTK->Direct3D9->SetCamera(camera);
}