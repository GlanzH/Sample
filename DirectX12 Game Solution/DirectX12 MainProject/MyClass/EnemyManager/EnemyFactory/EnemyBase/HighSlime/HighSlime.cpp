#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/MyAlgorithm/MyAlgorithm.h"
#include "HighSlime.h"

HighSlime::HighSlime()
{
}

bool HighSlime::Initialize()
{
   
    return false;
}

int HighSlime::Update(SimpleMath::Vector3 player, const float deltaTime)
{
    EnemyBase::Update(player, deltaTime);

    Move(player, deltaTime);
    Rotate(player, deltaTime);
	Jump(deltaTime);

	return 0;
}

void HighSlime::Move(SimpleMath::Vector3 player, const float deltaTime) {
    if (player.x < position.x)
        position.x -= move_speed * deltaTime;
    else
        position.x += move_speed * deltaTime;
}

void HighSlime::Rotate(SimpleMath::Vector3 player, const float deltaTime) {
    //!プレイヤーの座標 - 敵の座標でプレイヤーのいる方向に向く
    float rotation = MathHelper_Atan2(-(player.z - position.z), (player.x - position.x)) - 45.0f;
    anim_model->SetRotation(0.0f,rotation, 0.0f);
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
}
