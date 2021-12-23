#include "LandingAttackClass.h"


void LandingAttackClass::Initialize()
{
}

void LandingAttackClass::LoadAseets()
{
	tarai = DX9::Model::CreateFromFile(DXTK->Device9, L"Model/tarai/tarai.X");
	tarai->SetPosition(tarai_pos);
}

void LandingAttackClass::Update()
{
	tarai_pos.y = tarai_pos.y - deltaTime;
	tarai_attack(tarai_pos);

}

void LandingAttackClass::Render()
{ 
	tarai->Draw();
}

void LandingAttackClass::tarai_attack(Vector3 enemy)
{
	std::random_device random_fall;
	random_landing = std::mt19937(random_fall());
	distribute = std::uniform_int_distribution<int>(MIN, MAX);
	tarai_pos.y = enemy_pos.y + distribute(random_landing);
	tarai_pos.x = enemy_pos.x;
}

