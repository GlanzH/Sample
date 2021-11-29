#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/MyAlgorithm/MyAlgorithm.h"
#include "Slime.h"

int Slime::Update(SimpleMath::Vector3 player, const float deltaTime) {
	EnemyBase::Update(player, deltaTime);

	Rotate(player, deltaTime);
	Move(player,deltaTime);
   
	return 0;
}

void Slime::Rotate(SimpleMath::Vector3 player, const float deltaTime) {
	//!プレイヤーの座標 - 敵の座標でプレイヤーのいる方向に向く
	float rotation = MathHelper_Atan2(-(player.z - position.z), (player.x - position.x)) - adjust_y;

	anim_model->SetRotation(0.0f, rotation, 0.0f);
}

void Slime::Move(SimpleMath::Vector3 player, const float deltaTime) {
	if (player.x < position.x)
		position.x -= move_speed * deltaTime;
	else
		position.x += move_speed * deltaTime;
}
