#include "CameraManager.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

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

int CameraManager::Update(SimpleMath::Vector3 pos) {
	camera->SetPosition(pos.x,fixed_pos, - 20);
	return 0;
}

void CameraManager::Render() {
	DXTK->Direct3D9->SetCamera(camera);
}