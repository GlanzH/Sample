#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

bool FakerLamiel::Initialize(std::string tag, SimpleMath::Vector3 speed, int hp) 
{
	EnemyBase::Initialize(tag,speed,hp);
	DX12Effect.Create(L"Effect/EnemyEffect/LamielEffect/omen/omen.efk", "sigh");
	DX12Effect.Create(L"Effect/EnemyEffect/LamielEffect/fire/fire.efk", "fire");
	teleport_frame    = 0;
	omen_effect_frame = 0;
	fire_effect_frame = 0;

	appear_collision_flag = false;
	action = DOWN;

	obstacle_collision = DX9::Model::CreateBox(DXTK->Device9,1,1,1);

	col.fire = obstacle_collision->GetBoundingBox();

	obstacle_collision->SetMaterial(material);
	obstacle_collision->SetScale(collision_scale);

	fire_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	col.fire.Center = position;
	return true;
}

int FakerLamiel::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player,special_attack_flag,thorow_things_flag, deltaTime);

	delta = deltaTime;
	
	if (!special_attack_flag && !thorow_things_flag) {
		Move(player);
		MoveFireCollision();
	}

	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));

	return 0;
}

void FakerLamiel::Move(SimpleMath::Vector3 player)
{
	switch (action)
	{
	case DOWN:
		if (position.y > min_down_pos)
			position.y -= move_speed * delta;
		else
			action = ATTACK_SIGH;
		break;

	case ATTACK_SIGH:
		if(omen_effect_frame < max_omen_frame) {
			DX12Effect.SetPosition("sigh",
				SimpleMath::Vector3(
					position.x,
					position.y - adjust_sigh_y,
					position.z)
			);

			DX12Effect.PlayOneShot("sigh");
			omen_effect_frame += delta;
		}
		else
			action = ATTACK;

		break;

	case ATTACK:
		if (fire_effect_frame < MAX_FIRE_FRAME) {
			DX12Effect.SetPosition("fire",
				SimpleMath::Vector3(6, -fire_effect_y,fire_effect_z));
			DX12Effect.SetScale("fire",SimpleMath::Vector3(0.8, 1.3, 1));
			DX12Effect.SetSpeed("fire", 1.4f);
			DX12Effect.PlayOneShot("fire");

			if (!appear_collision_flag) {
				fire_pos = SimpleMath::Vector3(80,0,position.z);
				appear_collision_flag = true;
			}

			fire_effect_frame += delta;
		}
		else
			action = TELEPORT;
		break;

	case TELEPORT:
		if (teleport_frame > MAX_TELEPORT_FRAME) {
			std::random_device teleport_seed;
			random_device = std::mt19937(teleport_seed());
			distribute = std::uniform_int_distribution<int>(MIN_RANGE, NAX_RANGE);
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

		appear_collision_flag = false;

		action = ATTACK_SIGH;
		break;

	default:
		action = DOWN;
		break;
	}
}

void FakerLamiel::MoveFireCollision() {
	if (fire_effect_frame < MAX_FIRE_FRAME)
		fire_pos.x -= move_fire * delta;
	else
		fire_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX,FLT_MAX);

	col.fire.Center = obstacle_collision->GetPosition();
	obstacle_collision->SetPosition(fire_pos);
}

void FakerLamiel::Render() {
	EnemyBase::Render();
	//obstacle_collision->Draw();
}