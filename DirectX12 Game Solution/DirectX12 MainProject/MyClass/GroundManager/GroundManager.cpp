#include "GroundManager.h"

void GroundManager::LoadAsset() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model//Theatre\\background.x");	
	model->SetPosition(0, pos_y, pos_z);

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * box_size,
		box.Extents.y * box_size,
		box.Extents.z * box_size
	);

	box.Center = model->GetPosition();
	collision->SetPosition(0, -5.0f, 70.0f);
	collision->SetScale(90.0f, 5.0f, 30.0f);

}

void GroundManager::Render() {
	model->Draw();
	//collision->Draw();
}
