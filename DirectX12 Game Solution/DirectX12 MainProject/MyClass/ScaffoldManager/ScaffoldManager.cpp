#include "ScaffoldManager.h"

void ScaffoldManager::LoadAssets() {
	model = DX9::Model::CreateFromFile(DXTK->Device9, L"Model\\asiba.X");
	model->SetPosition(10, 5, 50);

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	
	box.Extents.x = box.Extents.x * 7;
	box.Extents.z = box.Extents.z * 4;

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * 2,
		box.Extents.y * 2,
		box.Extents.z * 2
	);

	box.Center = model->GetPosition();
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0,1,0));
	collision->SetMaterial(material);
}

int ScaffoldManager::Update() {
	//scaffold_flag = false;
	
	return 0;
}

void ScaffoldManager::Render() {
	model->Draw();
	collision->Draw();
}

void ScaffoldManager::OnCollisionEnter() {
	scaffold_flag = true;
}

void ScaffoldManager::NotCollisionEnter() {
	scaffold_flag = false;
}