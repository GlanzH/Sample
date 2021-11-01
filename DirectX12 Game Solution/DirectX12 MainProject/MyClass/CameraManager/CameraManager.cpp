#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CameraManager.h"

bool CameraManager::Initialize() {
	//�J�����̈ʒu
	camera->SetView(SimpleMath::Vector3(0.0f, 15.0f, 0.0f), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));

	//�J�����̌����E�f������
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(40.0f), 16.0f / 9.0f, 1.0f, 10000.0f
	);

	camera->SetPosition(0, 30.0f, 0);

	return true;
}

int CameraManager::Update(PlayerManager* player) {
	auto pos = player->GetModel()->GetPosition();
	camera->SetPosition(pos.x,10.0f,-10.0f);
	return 0;
}

void CameraManager::Render(SimpleMath::Vector3 player_position) {
	DXTK->Direct3D9->SetCamera(camera);
}