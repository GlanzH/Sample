#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CameraManager.h"

bool CameraManager::Initialize() {
	//�J�����̈ʒu
	camera->SetView(Vector3(0.0f, view_y, 0.0f),Vector3(0.0f, 0.0f, 0.0f));

	//�J�����̌����E�f������
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(40.0f), 16.0f / 9.0f, 1.0f, 10000.0f
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