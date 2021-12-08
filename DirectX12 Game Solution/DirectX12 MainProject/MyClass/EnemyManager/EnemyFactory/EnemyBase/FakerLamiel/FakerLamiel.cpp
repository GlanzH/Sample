#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

bool FakerLamiel::Initialize(std::string tag, bool time_stop_flag, int hp)
{
	EnemyBase::Initialize(tag,time_stop_flag,hp);
	DX12Effect.Create(L"Effect/EnemyEffect/LamielEffect/omen/omen.efk", "sigh");
	DX12Effect.Create(L"Effect/EnemyEffect/LamielEffect/fire/fire.efk", "fire");
	teleport_frame    = 0;
	omen_effect_frame = 0;
	fire_effect_frame = 0;

	appear_collision_flag = false;
	action = DOWN;

	obstacle_collision = DX9::Model::CreateBox(DXTK->Device9,1,1,1);

	col.fire = obstacle_collision->GetBoundingBox();
	col.fire.Extents.x = col.fire.Extents.x * 20;

	if (collision != nullptr)
		collision->SetScale(2.0f);

	obstacle_collision->SetMaterial(material);
	obstacle_collision->SetScale(collision_scale);

	fire_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	col.fire.Center = position;
	return true;
}

int FakerLamiel::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player,special_attack_flag,thorow_things_flag, deltaTime);

	delta = deltaTime;
	player_pos = player;
	
	if (!special_attack_flag && !thorow_things_flag) {
		Move();
		MoveFireCollision();
	}
	else if (special_flag || throw_flag) {
		StopEffect();
	}

	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
	col.box.Center = model->GetPosition();

	col.fire.Center = obstacle_collision->GetPosition();
	obstacle_collision->SetPosition(fire_pos);

	return 0;
}

void FakerLamiel::Move()
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
					position.z + 20)
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
				SimpleMath::Vector3(3, -fire_effect_y,fire_effect_z));
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
		fire_accelerate   = 1.0f;

		appear_collision_flag = false;

		action = ATTACK_SIGH;
		break;

	default:
		action = DOWN;
		break;
	}
}

void FakerLamiel::MoveFireCollision() {
	if (fire_effect_frame < MAX_FIRE_FRAME + 0.01f) {
		fire_pos.x -= move_fire * fire_accelerate * delta;

		if(player_pos.x + 4.0f < fire_pos.x)
			fire_accelerate = 2.45f;
		else if (player_pos.x - 1.0f <= fire_pos.x && player_pos.x + 4.0f >= fire_pos.x)
			fire_accelerate = 1.f;
		//else if(player_pos.x + 10.0f > fire_pos.x)
		//	fire_accelerate = 2.45f;
	}
	else {
		fire_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
		fire_accelerate = 1.0f;
	}
}

void FakerLamiel::StopEffect() {
	switch (action) {
	case ATTACK_SIGH:
		DX12Effect.Stop("sigh");
		break;
	case ATTACK:
		DX12Effect.Stop("fire");
		break;
	default:
		break;
	}
}

void FakerLamiel::Render() {
	EnemyBase::Render();
	obstacle_collision->Draw();
}