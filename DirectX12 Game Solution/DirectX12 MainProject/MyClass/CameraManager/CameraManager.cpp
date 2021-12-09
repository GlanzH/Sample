#include "CameraManager.h"

bool CameraManager::Initialize() {
	//カメラの位置
	camera->SetView(SimpleMath::Vector3(0.0f, fixed_pos, 0.0f), SimpleMath::Vector3::Zero);

	//カメラの向き・映す距離
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(rotate_degrees), aspect, min_screen_range, max_screen_range
	);
	

	return true;
}

void CameraManager::LoadAsset() {

}

int CameraManager::Update(PlayerBase* base,const float deltaTime) {
	if (base->GetAppielTime() > 0)
		camera_z -= 15.f * deltaTime;
	else if (base->GetAppealCoolFlag())
		camera_z += 40.f * deltaTime;

	camera_z = std::clamp(camera_z, -10.0f, 20.0f);


	camera->SetPosition(base->GetModel()->GetPosition().x, fixed_pos, -camera_z);
	return 0;
}

void CameraManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);
}