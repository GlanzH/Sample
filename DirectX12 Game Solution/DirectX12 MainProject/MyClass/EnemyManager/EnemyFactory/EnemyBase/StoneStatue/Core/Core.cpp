#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Core.h"



Core::Core()
{
}

bool Core::Initialize(std::string tag,SimpleMath::Vector3 speed, int hp)
{
	EnemyBase::Initialize(tag,speed, hp);
	DX12Effect.Create(L"Effect//shoot//shoot.efk", "shoot");
	DX12Effect.Create(L"Effect//charge//charge.efk", "charge");
	DX12Effect.Create(L"Effect//landing//landing.efk", "landing");
	

	wait_count = 0;

	return true;
}

int Core::Update(SimpleMath::Vector3 player, const float deltaTime) {
	
	EnemyBase::Update(player, deltaTime);

	 Attack(deltaTime);

	if (enemy_hp < 0)
		return DEAD;

	collision->SetPosition(model->GetPosition());

	return LIVE;
}

void Core::Attack(const float deltaTime)
{


}

void Core::Shot()
{
	SimpleMath::Vector3 bullet_pos;
	bullet_pos.x -= 3.0f;
	bullet_pos.y -= 2.0f;
}

void Core::Render() {
	EnemyBase::Render();
}