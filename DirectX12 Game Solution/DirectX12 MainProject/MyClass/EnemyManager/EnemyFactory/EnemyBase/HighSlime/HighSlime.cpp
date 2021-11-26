#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/MyAlgorithm/MyAlgorithm.h"
#include "HighSlime.h"

HighSlime::HighSlime()
{
}

int HighSlime::Update(PlayerBase* player, const float deltaTime)
{
    Move(player, deltaTime);
    Rotate(player, deltaTime);
	Jump(deltaTime);
   // SetAnimation(model, WAIT);

	//model->AdvanceTime(deltaTime / 1.0f);

	if (enemy_hp < 0)
		return DEAD;

	return LIVE;
}

void HighSlime::Move(PlayerBase* player, const float deltaTime) {
    float player_pos = player->GetModel()->GetPosition().x;

    if (player_pos < position.x)
        position.x -= move_speed * deltaTime;
    else
        position.x += move_speed * deltaTime;
}

void HighSlime::Rotate(PlayerBase* player, const float deltaTime) {
    //!プレイヤーの座標 - 敵の座標でプレイヤーのいる方向に向く
    SimpleMath::Vector3 player_pos = player->GetModel()->GetPosition();

    float now_rotate = model->GetRotation().y;
    float rotation = MathHelper_Atan2(-(player_pos.z - position.z), (player_pos.x - position.x)) - 45.0f;

    model->SetRotation(0.0f,rotation, 0.0f);
}

void HighSlime::Jump(const float deltaTime)
{
    if (!jump_flag) {
        jump_time = 0;
        jump_flag = true;
    }
    else{
        jump_time  += deltaTime;
        position.y += jump_speed * deltaTime;
        position.y  = position.y + (jump_speed * jump_time * jump_power * gravity * jump_time * jump_time * deltaTime);

        if (position.y < 0.0f) {
            position.y = 0.0f;
            jump_flag = false;
        }

    }
    collision->SetPosition(model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
    box.Center = model->GetPosition();
    model->SetPosition(position);
}
