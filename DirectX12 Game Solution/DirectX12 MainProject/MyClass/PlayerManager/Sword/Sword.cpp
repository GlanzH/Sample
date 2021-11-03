#include "Sword.h"

#include "MyClass/PlayerManager/PlayerManager.h"

bool Sword::Initialize() {
	sword_pos = SimpleMath::Vector3(0.0f, fixed_pos, 100.0f);

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
}

int Sword::Update(PlayerManager* player, const float deltaTime)
{
	auto pos = player->GetModel()->GetPosition();
	sword_model_->SetPosition(pos.x + 3.0f, pos.y, pos.z + 5.0f);

	if (DXTK->KeyEvent->pressed.J || DXTK->KeyEvent->pressed.F || DXTK->GamePadEvent->b) {
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

	return 0;
}

void Sword::Render()
{
	sword_model_->Draw();
}