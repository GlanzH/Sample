#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

int FakerLamiel::Update(SimpleMath::Vector3 player, const float deltaTime) {
	delta = deltaTime;

	Attack(player);

	if (enemy_hp < 0)
		return DEAD;
	return LIVE;
}

void FakerLamiel::Attack(SimpleMath::Vector3 player)
{
	switch (action)
	{
	case DOWN:
		if (player.y + 15.0f < position.y)
			position.y -= move_speed * delta;
		else
			action = ATTACK_SIGH;
		break;

	case ATTACK_SIGH:
		if (!omen_load_flag) {
			DX12Effect.Create(L"Effect/LamielEffect/omen/omen.efk", "sigh");
			omen_load_flag = true;
		}
		else if(omen_effect_frame < 3.0f) {
			DX12Effect.SetRotation("sigh", SimpleMath::Vector3(0, 170, 0));
			DX12Effect.SetPosition("sigh", SimpleMath::Vector3(0,0,0));
			DX12Effect.PlayOneShot("sigh");
			omen_effect_frame += delta;
		}
		else
			action = ATTACK;

		break;

	case ATTACK:
		if (!fire_load_flag) {
			DX12Effect.Create(L"Effect/LamielEffect/fire/fire.efk", "fire");
			fire_load_flag = true;
		}
		else if (fire_effect_frame < 7.0f) {
			DX12Effect.SetRotation("sigh", SimpleMath::Vector3(0, 0, 0));
			DX12Effect.SetPosition("sigh", SimpleMath::Vector3(0, 0, 0));
			DX12Effect.PlayOneShot("fire");
			fire_effect_frame += delta;
		}
		else
			action = TELEPORT;
		break;

	case TELEPORT:
		if (teleport_frame > 60.0f) {
			std::random_device teleport_seed;
			random_device = std::mt19937(teleport_seed());
			distribute = std::uniform_int_distribution<int>(-30, 40);
			position.x = distribute(random_device);
			
			action = INIT_DATA;
		}
		else
			teleport_frame += delta;

		break;

	case INIT_DATA:
		teleport_frame    = 0;
		omen_effect_frame = 0;
		fire_effect_frame = 0;

		action = ATTACK_SIGH;
		break;

	default:
		action = DOWN;
		break;
	}

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}


