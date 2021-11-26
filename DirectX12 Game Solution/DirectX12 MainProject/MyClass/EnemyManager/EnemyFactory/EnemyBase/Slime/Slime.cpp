#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/MyAlgorithm/MyAlgorithm.h"
#include "Slime.h"

int Slime::Update(PlayerBase* player, const float deltaTime) {
	Rotate(player, deltaTime);
	Move(player,deltaTime);
	//SetAnimation(model, WAIT);

//	model->AdvanceTime(deltaTime / 1.0f);

	if (enemy_hp < 0)
		return DEAD;
   
	return LIVE;
}

void Slime::Rotate(PlayerBase* player, const float deltaTime) {
	//!プレイヤーの座標 - 敵の座標でプレイヤーのいる方向に向く
	SimpleMath::Vector3 player_pos = player->GetModel()->GetPosition();

	float now_rotate = model->GetRotation().y;
	float rotation = MathHelper_Atan2(-(player_pos.z - position.z), (player_pos.x - position.x)) - 45.0f;

	model->SetRotation(0.0f, rotation, 0.0f);
}

void Slime::Move(PlayerBase* player, const float deltaTime) {
	float player_pos = player->GetModel()->GetPosition().x;

	if (player_pos < position.x)
		position.x -= move_speed * deltaTime;
	else
		position.x += move_speed * deltaTime;

	box.Center = model->GetPosition();
	model->SetPosition(position);
	collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
}
