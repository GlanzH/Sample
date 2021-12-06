#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Core.h"



Core::Core()
{
}

bool Core::Initialize(std::string tag,SimpleMath::Vector3 speed, int hp)
{
	EnemyBase::Initialize(tag,speed, hp);
	DX12Effect.Create(L"Effect/EnemyEffect/StatueEffect/shoot/shoot.efk",      "shoot");
	DX12Effect.Create(L"Effect/EnemyEffect/StatueEffect/charge/charge.efk",   "charge");
	DX12Effect.Create(L"Effect/EnemyEffect/StatueEffect/landing/landing.efk","landing");

	obstacle_collision = DX9::Model::CreateSphere(DXTK->Device9, 4, 8, 2);

	obstacle_collision->SetMaterial(material);
	obstacle_collision->SetScale(collision_scale);

	bull_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	col.bullet.Center = position;
	launch_count_count = 0;
	landing_count = 0;





	return true;
}

int Core::Update(SimpleMath::Vector3 player, const float deltaTime) {

	delta = deltaTime;

	EnemyBase::Update(player, deltaTime);
	Move(player);


	if (enemy_hp < 0)
	{
		DX12Effect.Stop("chage");
		return DEAD;
	}
		

	collision->SetPosition(model->GetPosition());
	col.bullet.Center = obstacle_collision->GetPosition();
	obstacle_collision->SetPosition(bull_pos);

	return LIVE;
}

void Core::Move(SimpleMath::Vector3 player){
	switch (action)
	{
	case MOVE:
		if (position.z > max_move)
			position.z -= move_core * delta;
		else
			action = CHARGE;
		break;

	case CHARGE:
		if (wait_charge_frame < max_wait_charge)
		{
			wait_charge_frame += delta;
		}
		else if (charge_effect_frame < max_charge) 
		{
			DX12Effect.SetPosition("charge", position);
			DX12Effect.PlayOneShot("charge");
			charge_effect_frame += delta;
		}
		else
			action = ATTACK;
		break;

	case ATTACK:
			if (!shot_flag)
			{
				player_pos = player;
				bull_pos = position;
				shot_flag = true;
			}
			else if (wait_shot_frame < max_wait_shot)
			{
				wait_shot_frame += delta;
			}
			else
			{	
				Shot(player_pos);
				if (launch_count_count == 3)
				{
					action = WAIT;
				}
			}
		break;

	case WAIT:
		bull_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

		if (wait_frame < max_wait)
			wait_frame += delta;
		else
		action = BACK;
		break;

	case BACK:
		if (position.z < max_back)
			position.z += move_core * delta;
		else
		action = STOP;
		break;

	case STOP:
		if (stop_frame < max_stop)
			stop_frame += delta;
		else
			action = INIT;
		break;

	case INIT:
		charge_effect_frame  = 0;
		landing_effect_frame = 0;
		wait_charge_frame    = 0;
		wait_shot_frame      = 0;

		wait_frame = 0;
		stop_frame = 0;
		shot_flag = false;
		action = MOVE;
		break;

	default:
		break;
	}

}

void Core::Shot(SimpleMath::Vector3 init_bull_pos)
{
	auto distance_x = SimpleMath::Vector3::Distance(bull_pos, player_pos);
	auto distance_y = SimpleMath::Vector3::Distance(bull_pos,SimpleMath::Vector3(0.0,-10.0f,50.0f)) /3;
	Vector3 a =SimpleMath::Vector3(distance_x, distance_y,50);
	a.Normalize();
	oblique_shooting = sqrt(distance_y * distance_y + distance_x * distance_x);
	
	
	//bull_pos.x = distance_x * delta;
	bull_pos.y -= distance_y  * delta;

	if (bull_pos.x > init_bull_pos.x)
		bull_pos.x -= distance_x * delta;
	else
		bull_pos.x += distance_x * delta;
	//if (bull_pos.y > init_bull_pos.y)
	//{
	//	//bull_pos.y = oblique_shooting;
	//	bull_pos.y -= move_bull_y * delta;

	//	DX12Effect.SetPosition("shoot", bull_pos);	
	//	DX12Effect.Play("shoot");
	//}
	if (bull_pos.y > init_bull_pos.y)
	{

		DX12Effect.SetPosition("shoot", bull_pos);
		DX12Effect.Play("shoot");
	}
	else
	{
		if (landing_effect_frame < max_landing)
		{
			DX12Effect.SetPosition("landing", bull_pos);
			DX12Effect.PlayOneShot("landing");
			
			landing_effect_frame += delta;
		}
		else
		{
			landing_effect_frame = 0;
			wait_shot_frame = 0;
			launch_count_count++;
			shot_flag = false;
		}
	}
}

void Core::Render() {
	EnemyBase::Render();
	//obstacle_collision->Draw();
}