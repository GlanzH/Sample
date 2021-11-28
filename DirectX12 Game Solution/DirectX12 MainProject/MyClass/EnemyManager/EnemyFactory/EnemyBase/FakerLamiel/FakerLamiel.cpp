#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

bool FakerLamiel::Initialize(std::string tag, SimpleMath::Vector3 speed, int hp) {
	EnemyBase::Initialize(tag,speed,hp);
	DX12Effect.Create(L"Effect/LamielEffect/omen/omen.efk", "sigh");
	DX12Effect.Create(L"Effect/LamielEffect/fire/fire.efk", "fire");

	appear_collision_flag = false;
	action = DOWN;


	obstacle_collision = DX9::Model::CreateBox(DXTK->Device9,1,1,1);

	col.fire = obstacle_collision->GetBoundingBox();

	obstacle_collision->SetMaterial(material);
	obstacle_collision->SetScale(11,4,4);

	fire_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

	col.fire.Center = position;
	return true;
}

int FakerLamiel::Update(SimpleMath::Vector3 player, const float deltaTime) {
	EnemyBase::Update(player, deltaTime);

	delta = deltaTime;
	
	Move(player);
	MoveFireCollision();

	if (enemy_hp < 0)
		return DEAD;


	return LIVE;
}

void FakerLamiel::Move(SimpleMath::Vector3 player)
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
		if(omen_effect_frame < MAX_OMEN_FRAME) {
			DX12Effect.SetPosition("sigh", SimpleMath::Vector3(position.x,position.y - 10.0f, position.z));
			DX12Effect.PlayOneShot("sigh");
			omen_effect_frame += delta;
		}
		else
			action = ATTACK;

		break;

	case ATTACK:
		if (fire_effect_frame < MAX_FIRE_FRAME) {
			DX12Effect.SetPosition("fire", SimpleMath::Vector3(position.x, position.y - 20.0f, position.z + 30.0f));
			DX12Effect.PlayOneShot("fire");

			if (!appear_collision_flag) {
				fire_pos = SimpleMath::Vector3(position.x + 13.0f, position.y - 15.0f, position.z);
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
	if (fire_effect_frame < MAX_FIRE_FRAME -1)
		fire_pos.x -= 6.3f * delta;
	else
		fire_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX,FLT_MAX);

	col.fire.Center = obstacle_collision->GetPosition();
	obstacle_collision->SetPosition(fire_pos);
}

void FakerLamiel::Render() {
	EnemyBase::Render();
	int a = 0;
	obstacle_collision->Draw();
}