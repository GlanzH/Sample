#include "CameraManager.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

bool CameraManager::Initialize() {
	//カメラの位置
	camera->SetView(SimpleMath::Vector3(0.0f, fixed_pos, 0.0f), SimpleMath::Vector3::Zero);

	//カメラの向き・映す距離
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(40.0f), 16.0f / 9.0f, 1.0f, 10000.0f
	);
	

	return true;
}

void CameraManager::LoadAsset() {

}

int CameraManager::Update(PlayerBase* player) {
	auto pos = player->GetModel()->GetPosition();
	camera->SetPosition(pos.x,fixed_pos, - fixed_pos);
	return 0;
}

void CameraManager::Render(SimpleMath::Vector3 player_position) {
	DXTK->Direct3D9->SetCamera(camera);
}