#include "Sword.h"

#include "MyClass/PlayerManager/PlayerManager.h"

bool Sword::Initialize() {
	sword_pos = SimpleMath::Vector3(0.0f, 0, fixed_pos);

	sword_flag = false;

	return 0;
}

void Sword::LoadAssets()
{
	sword_model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"negi\\negi.X");
	sword_model_->SetTexture(L"negi\\negiii.png");
	sword_model_->SetPosition(sword_pos);
	sword_model_->SetScale(3.0f);
	sword_model_->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);

	box = sword_model_->GetBoundingBox();

	collision = DX9::Model::CreateBox(
		DXTK->Device9,
		box.Extents.x * 14,
		box.Extents.y * 4,
		box.Extents.z * 14
	);

	box.Center = sword_model_->GetPosition();
}

int Sword::Update(PlayerManager* player, const float deltaTime)
{
	sword_model_->SetPosition(player->GetModel()->GetPosition() + SimpleMath::Vector3(3,0,0));

	if (IsAttack()) {
		sword_flag = true;
		sword_attack_time = 0.0f;
	}


	if (sword_flag) {
		sword_model_->Rotate(XMConvertToRadians(180.0f) * deltaTime, 0, 0);
		sword_attack_time += deltaTime;
		if (sword_attack_time >= 0.5f) {
			sword_model_->SetRotation(0.0f, XMConvertToRadians(90.0f), 0.0f);
			sword_flag = false;
			sword_attack_time = 0.0f;

		}
	}

	box.Center  = sword_model_->GetPosition() + SimpleMath::Vector3(3, 0, 0);
	collision->SetPosition(sword_model_->GetPosition() + SimpleMath::Vector3(3, 7, 0));
	
	return 0;
}

bool Sword::IsAttack() {
	if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent->b)
		return true;

	return false;
}

void Sword::Render()
{
	sword_model_->Draw();
//	collision->Draw();
}