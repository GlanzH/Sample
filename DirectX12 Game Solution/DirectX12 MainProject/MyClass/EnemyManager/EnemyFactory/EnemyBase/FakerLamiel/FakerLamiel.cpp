#include "Base/pch.h"
#include "Base/dxtk.h"
#include "FakerLamiel.h"

bool FakerLamiel::Initialize(std::string tag, SimpleMath::Vector3 speed, int hp) {
	EnemyBase::Initialize(tag,speed,hp);
	DX12Effect.Create(L"Effect/LamielEffect/omen/omen.efk", "sigh");
	DX12Effect.Create(L"Effect/LamielEffect/fire/fire.efk", "fire");
	action = DOWN;
	return true;
}

int FakerLamiel::Update(SimpleMath::Vector3 player, const float deltaTime) {
	EnemyBase::Update(player, deltaTime);

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

		action = ATTACK_SIGH;
		break;

	default:
		action = DOWN;
		break;
	}
}

void FakerLamiel::Render() {
	EnemyBase::Render();
}