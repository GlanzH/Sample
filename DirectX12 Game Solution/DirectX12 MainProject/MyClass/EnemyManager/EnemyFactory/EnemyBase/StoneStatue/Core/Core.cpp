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
	DX12Effect.Create(L"Effect/EnemyEffect/StatueEffect/landing3/landing.efk","landing");

	obstacle_collision = DX9::Model::CreateSphere(DXTK->Device9, 4, 8, 2);

	obstacle_collision->SetMaterial(material);
	obstacle_collision->SetScale(collision_scale);

	bull_pos = SimpleMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
	col.bullet.Center = position;
	launch_count_count = 0;
	landing_count = 0;
	SHOT_SPEED = 1.1;
	return true;
}

int Core::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	
	bull_pos -= laser_coordinate * SHOT_SPEED;
	special_flag = special_attack_flag;
	throw_flag   = thorow_things_flag;
	delta = deltaTime;
	
	EnemyBase::Update(player, special_flag, throw_flag, deltaTime);

	if (!special_flag && !throw_flag) {
		Move(player);
	}
	//else if(special_flag || throw_flag) {
	//	StopEffect();
	//}


	if (enemy_hp < 0)
		DX12Effect.Stop("charge");
		return DEAD;



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
		launch_count_count   = 0;
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
	laser_coordinate = position - player_pos;
	laser_coordinate.Normalize();
	laser_coordinate.z = 0.0f;
	if (bull_pos.y > init_bull_pos.y)
	{

		DX12Effect.PlayOneShot("shoot", bull_pos);
		DX12Effect.SetPosition("shoot", bull_pos);
	}
	else
	{
		if (landing_effect_frame < max_landing)
		{
			DX12Effect.PlayOneShot("landing", bull_pos);
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

void Core::StopEffect() {
	switch (action) {
		case CHARGE:
			DX12Effect.Stop("charge");
			break;
		case ATTACK:
			DX12Effect.Stop("shoot");
			DX12Effect.Stop("landing");
			break;
		default:
			break;
	}
}

void Core::Render() {
	EnemyBase::Render();
	//obstacle_collision->Draw();
}