#include "CameraManager.h"

#include "MyClass/PlayerManager/PlayerManager.h"

bool CameraManager::Initialize() {
	//�J�����̈ʒu
	camera->SetView(SimpleMath::Vector3(0.0f, fixed_pos, 0.0f), SimpleMath::Vector3::Zero);

	//�J�����̌����E�f������
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(40.0f), 16.0f / 9.0f, 1.0f, 10000.0f
	);
	

	return true;
}

void CameraManager::LoadAsset() {

}

int CameraManager::Update(PlayerManager* player) {
	auto pos = player->GetModel()->GetPosition();
	camera->SetPosition(pos.x,fixed_pos, - fixed_pos);
	return 0;
}

void CameraManager::Render(SimpleMath::Vector3 player_position) {
	DXTK->Direct3D9->SetCamera(camera);
}