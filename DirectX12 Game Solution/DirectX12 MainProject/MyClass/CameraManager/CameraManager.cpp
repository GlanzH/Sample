#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CameraManager.h"

bool CameraManager::Initialize() {
	//カメラの位置
	camera->SetView(Vector3(0.0f, view_y, 0.0f),Vector3(0.0f, 0.0f, 0.0f));

	//カメラの向き・映す距離
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(40.0f), 16.0f / 9.0f, 1.0f, 10000.0f
	);


	return true;
}

void CameraManager::Render(Vector3 player_position) {
	camera->SetViewLookAt(player_position + Vector3::Forward * 40
		+ SimpleMath::Vector3(0.0f, 10.0f, 0.0f), player_position, Vector3::Up);

	DXTK->Direct3D9->SetCamera(camera);
}