#include "C_Camera.h"

bool C_Camera::Initialize() {
	//�J�����̈ʒu
	camera->SetView(SimpleMath::Vector3(0.0f, fixed_pos, 20.0f), SimpleMath::Vector3::Zero);

	//�J�����̌����E�f������
	camera->SetPerspectiveFieldOfView(
		XMConvertToRadians(rotate_degrees), aspect, min_screen_range, max_screen_range
	);
	
	return true;
}

void C_Camera::LoadAsset() {

}

int C_Camera::Update(PlayerBase* base,int camera_pos_num,const float deltaTime) {
	if (base->GetAppielTime() > 0 || camera_pos_num == IN_ZOOM)
		camera_z -= 15.f * deltaTime;
	else if (base->GetAppealCoolFlag())
		camera_z += 40.f * deltaTime;

	camera_z = std::clamp(camera_z, -10.0f, 40.0f);


	camera->SetPosition(base->GetModel()->GetPosition().x, fixed_pos, -camera_z);
	return 0;
}

void C_Camera::Render() {
	DXTK->Direct3D9->SetCamera(camera);
}