#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/MyAlgorithm/MyAlgorithm.h"
#include "Slime.h"

int Slime::Update(SimpleMath::Vector3 player, const float deltaTime) {
	EnemyBase::Update(player, deltaTime);

	Rotate(player, deltaTime);
	Move(player,deltaTime);

	if (EnemyBase::IsDamage())
		SetAnimation(anim_model, WAIT);
	else
		SetAnimation(anim_model, DAMAGE);

	anim_model->AdvanceTime(deltaTime / 1.0f);

	if (enemy_hp < 0)
		return DEAD;
   
	return LIVE;
}

void Slime::Rotate(SimpleMath::Vector3 player, const float deltaTime) {
	//!プレイヤーの座標 - 敵の座標でプレイヤーのいる方向に向く
	float rotation = MathHelper_Atan2(-(player.z - position.z), (player.x - position.x)) - 45.0f;

	anim_model->SetRotation(0.0f, rotation, 0.0f);
}

void Slime::Move(SimpleMath::Vector3 player, const float deltaTime) {
	if (player.x < position.x)
		position.x -= move_speed * deltaTime;
	else
		position.x += move_speed * deltaTime;
}
