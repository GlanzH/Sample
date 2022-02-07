#include "Base/pch.h"
#include "Base/dxtk.h"
#include "RandSwordMan.h"
#include "MyClass/EnumManager/EnumManager.h"

void RandSwordMan::LoadAsset(LPCWSTR model_name, SimpleMath::Vector3 initial_position) {
	EnemyBase::LoadAsset(model_name, initial_position);

	col.weapon = col.box;

	//コリジョンモデルの作成
	sword_col = DX9::Model::CreateBox(
		DXTK->Device9,
		col.weapon.Extents.x * 3,
		col.weapon.Extents.y * 20,
		col.weapon.Extents.z * 5
	);

	sword_col->SetMaterial(material);
	sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);

	col.weapon.Center = sword_pos;
}

int RandSwordMan::Update(SimpleMath::Vector3 player, bool destroy_flag, const float deltaTime) {
	EnemyBase::Update(player, destroy_flag, deltaTime);
	EnemyBase::NormalDeathEffect(max_dead, confetti_effect_flag, death_effect_flag, effect_count);
	EnemyBase::AdjustAnimCollision();
	EnemyBase::TemporaryDeath();
	Freeze();
	IsDamage();
	IsDeath();

	if (!damage_flag && !retreat_flag && !temporary_death_flag && !die_flag)
		Action();

	if (is_freeze < max_is_damage && is_damage < max_is_damage)
		anim_model->AdvanceTime(delta / 1.0f);

	sword_col->SetPosition(sword_pos);
	col.weapon.Center = SimpleMath::Vector3(sword_pos.x, 0, sword_pos.z);
	collision->SetPosition(anim_model->GetPosition() + SimpleMath::Vector3(0, 6, 0));
	return 0;
}

void RandSwordMan::Render() {
	anim_model->Draw();
	//collision->Draw();
	//sword_col->Draw();
}

void RandSwordMan::Action() {

	switch (action)
	{
	case (int)ActionNum::FIRST_WAIT:
		InitDirect();

		if (init_wait_frame < max_init_wait) {
			init_wait_frame += delta;
			Run();
		}
		else {
			action = (int)ActionNum::INIT;
		}
		break;

	case (int)ActionNum::INIT:
		Run();
		attack_frame = 0.0f;
		move_pos_x = player_pos.x;
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
		Attack();

		if (attack_frame < max_attack) {
			if (enemy_posture == "U")
				SetAnimation(anim_model, (int)Motion::ATTACK_UP, (int)Motion::MAX_MOTION);
			else
				SetAnimation(anim_model, (int)Motion::ATTACK_DOWN, (int)Motion::MAX_MOTION);

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

void RandSwordMan::InitDirect() {
	if (enemy_direct == "L") {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LEFT;
	}
	else {
		anim_model->SetRotation(0, rotate, 0);
		direct = RIGHT;
	}
}

void RandSwordMan::Rotate() {
	if (direct == LEFT && position.x >= max_range) {
		anim_model->SetRotation(0, rotate, 0);
		direct = RIGHT;
	}

	if (direct == RIGHT && position.x <= -max_range) {
		anim_model->SetRotation(0, -rotate, 0);
		direct = LEFT;
	}
}

void RandSwordMan::Move() {
	if (direct == LEFT)
		position.x += move_speed * delta;

	else if (direct == RIGHT)
		position.x -= move_speed * delta;
}

void RandSwordMan::Run() {
	if (enemy_posture == "U")
		SetAnimation(anim_model, (int)Motion::RUN_UP, (int)Motion::MAX_MOTION);
	else
		SetAnimation(anim_model, (int)Motion::RUN_DOWN, (int)Motion::MAX_MOTION);
}

void RandSwordMan::IsRetreat() {
	EnemyBase::IsRetreat();

	if (enemy_hp > 0 && retreat_flag)
		SetAnimation(anim_model, (int)Motion::BOUNCE, (int)Motion::MAX_MOTION);
}

void RandSwordMan::Freeze() {
	if (enemy_hp <= 0 && !die_flag) {
		SetAnimation(anim_model, (int)Motion::FREEZE, (int)Motion::MAX_MOTION);
		is_freeze += delta;
	}

	if (StatusManager::Instance().GetHitComboTime() == 0.0f) {
		Run();
		is_freeze = 0.0f;
	}
}

void RandSwordMan::Damage() {

	if (enemy_hp > 0 && !damage_flag) {
		std::random_device postune_seed;
		random = std::mt19937(postune_seed());
		distribute = std::uniform_int_distribution<int>(UPPER, LOWER);
		postune_num = distribute(random);

		if (postune_num == UPPER)
			enemy_posture = "U";
		else
			enemy_posture = "D";
	}

	EnemyBase::Damage();
}

void RandSwordMan::IsDamage() {
	EnemyBase::IsDamage();

	if (damage_flag) {
		is_damage += delta;
		SetAnimation(anim_model, (int)Motion::DAMAGE, (int)Motion::MAX_MOTION);
	}
	else {
		is_damage = 0.0f;
	}
}

void RandSwordMan::IsDeath() {
	if (die_flag) {
		is_freeze = 0.0f;
		SetAnimation(anim_model, (int)Motion::DEATH, (int)Motion::MAX_MOTION);


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

void RandSwordMan::Attack() {
	if (direct == LEFT) {
		if (attack_frame >= 0.8f)
			sword_pos = SimpleMath::Vector3(position.x + 5.0f, fit_collision_y, position.z);
	}
	else {
		if (attack_frame >= 0.8f)
			sword_pos = SimpleMath::Vector3(position.x - 5.0f, fit_collision_y, position.z);
	}

	if (attack_frame >= max_attack)
		sword_pos = SimpleMath::Vector3(INT_MAX, INT_MAX, INT_MAX);
}

bool RandSwordMan::LifeDeathDecision() {
	if (die_flag && dead_frame > max_dead)
		return DEAD;

	if (StatusManager::Instance().GetTime() == 0.0f)
		return AUTO;

	return LIVE;
}