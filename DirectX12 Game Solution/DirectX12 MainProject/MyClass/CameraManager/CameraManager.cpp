#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CameraManager.h"

#include "MyClass/PlayerManager/PlayerManager.h"

bool CameraManager::Initialize() {
	//カメラの位置
	camera->SetView(SimpleMath::Vector3(0.0f, fixed_pos, 0.0f), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));

	//カメラの向き・映す距離
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(40.0f), 16.0f / 9.0f, 1.0f, 10000.0f
	);
	
	camera->SetPosition(0, 30.0f, 0);

	return true;
}

void CameraManager::LoadAsset() {

}

int CameraManager::Update(PlayerManager* player,DX9::MODEL& ground) {
	//地形の当たり判定
	float dist = FLT_MAX;
	if (ground->IntersectRay(camera->GetPosition() + SimpleMath::Vector3(0, adjust_y, 0), SimpleMath::Vector3::Down, &dist)) {
		camera->Move(0.0f, adjust_y - dist, 0.0f);
	}

	auto pos = player->GetModel()->GetPosition();
	camera->SetPosition(pos.x,camera->GetPosition().y + fixed_pos, - fixed_pos);
	return 0;
}

void CameraManager::Render(SimpleMath::Vector3 player_position) {
	DXTK->Direct3D9->SetCamera(camera);
}