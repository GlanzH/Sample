#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MidBoss.h"

void MidBoss::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	EnemyBase::LoadAsset(model_name, initial_position);

	col.weapon = col.box;

	//コリジョンモデルの作成
	sword_col = DX9::Model::CreateBox(
		DXTK->Device9,
		col.weapon.Extents.x * 3,
		col.weapon.Extents.y * 5,
		col.weapon.Extents.z * 5
	);

	sword_col->SetMaterial(material);

	sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);

	col.weapon.Center = sword_pos;
}

int MidBoss::Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime) {
	EnemyBase::Update(player, destroy_flag, deltaTime);
	EnemyBase::Update(player, destroy_flag, deltaTime);
	EnemyBase::NormalDeathEffect(max_dead, confetti_effect_flag, death_effect_flag, effect_count);
	EnemyBase::AdjustAnimCollision();
	EnemyBase::TemporaryDeath();
	//Freeze();
	IsDeath();

	if (!temporary_death_flag && !die_flag)
		Action();

	sword_col->SetPosition(sword_pos);
	anim_model->AdvanceTime(delta / 1.0f);
	col.weapon.Center = SimpleMath::Vector3(sword_pos.x, 0, sword_pos.z);
	return 0;
}

void MidBoss::Render() {
	anim_model->Draw();
	//collision->Draw();
	//sword_col->Draw();
}

void MidBoss::Action() {

	switch (action)
	{
	case (int)ActionNum::FIRST_WAIT:
		InitDirect();

		if (init_wait_frame < max_init_wait) {
			init_wait_frame += delta;
			Rotate();
			SetAnimation(anim_model, (int)Motion::WAIT, (int)Motion::MAX_MOTION);
		}
		else {
			action = (int)ActionNum::INIT;
		}
		break;

	case (int)ActionNum::INIT:
		wait_frame = 0.0f;
		attack_frame = 0.0f;
		move_pos_x = player_pos.x;
		SetAnimation(anim_model, (int)Motion::WALK, (int)Motion::MAX_MOTION);
		action = (int)ActionNum::MOVE;
		break;

	case (int)ActionNum::MOVE:

		//!移動終了条件(プレイヤーがいた座標に到着したら)
		end_move = position.x > player_pos.x && position.x - 0.5f < move_pos_x ||
			position.x < player_pos.x&& position.x + 0.5f > move_pos_x;

		if (end_move)
			action = (int)ActionNum::ATTACK;
		else {
			Move();
			Rotate();
		}
		break;

	case (int)ActionNum::ATTACK:
		Rotate();
		Attack();

		if (attack_frame < max_attack) {
			SetAnimation(anim_model, (int)Motion::ATTACK, (int)Motion::MAX_MOTION);
			attack_frame += delta;
			attack_flag = true;
		}
		else {
			attack_flag = false;
			action = (int)ActionNum::INIT;
		}
		break;
	}
}

void MidBoss::InitDirect() {
	if (enemy_direct == "L") {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LEFT;
	}
	else {
		anim_model->SetRotation(0, rotate, 0);
		direct = RIGHT;
	}
}

void MidBoss::Move() {
	if (direct == LEFT)
		position.x += move_speed * delta;

	else if (direct == RIGHT)
		position.x -= move_speed * delta;
}

void MidBoss::Rotate() {
	if (direct == LEFT && position.x >= max_range) {
		anim_model->SetRotation(0, rotate, 0);
		direct = RIGHT;
	}

	if (direct == RIGHT && position.x <= -max_range) {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LEFT;
	}
}

void MidBoss::IsRetreat() {
	EnemyBase::IsRetreat();

	if (enemy_hp > 0 && retreat_flag)
		SetAnimation(anim_model, (int)Motion::DAMAGE, (int)Motion::MAX_MOTION);
}

void MidBoss::Attack() {
	if (direct == LEFT) {
		if ( attack_frame >= 2.0f)
			sword_pos = SimpleMath::Vector3(position.x + 5.0f, fit_collision_y, position.z);
	}
	else {
		if (attack_frame >= 2.0f)
			sword_pos = SimpleMath::Vector3(position.x - 5.0f, fit_collision_y, position.z);
	}

	if (attack_frame >= max_attack)
		sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
}

void MidBoss::Damage() {
	EnemyBase::Damage();
	damage_flag = true;
}

bool MidBoss::IsDamage() {
	if (damage_flag && enemy_hp > 1 && damage_frame < max_damage) {
		SetAnimation(anim_model, (int)Motion::DAMAGE, (int)Motion::MAX_MOTION);
		damage_frame += delta;
		return true;
	}
	else {
		damage_frame = 0.0f;
		damage_flag = false;
		return false;
	}
}

void MidBoss::IsDeath() {
	if (die_flag) {
		SetAnimation(anim_model, (int)Motion::CONFUSE, (int)Motion::MAX_MOTION);


		if (dead_frame >= 0.0f) {
			confetti_effect_flag = true;
			effect_count = CONFINETTI;
		}

		if (dead_frame >= 1.7f) {
			death_effect_flag = true;
			effect_count = DEATH;
		}
	}
}

bool MidBoss::LifeDeathDecision() {
	if (die_flag && dead_frame > max_dead)
		return DEAD;

	return LIVE;
}