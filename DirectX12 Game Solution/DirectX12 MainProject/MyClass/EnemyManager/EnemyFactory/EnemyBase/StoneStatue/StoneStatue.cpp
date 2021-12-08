#include "StoneStatue.h"

int StoneStatue::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player, special_attack_flag, thorow_things_flag, deltaTime);

	collision->SetPosition(FLT_MAX, FLT_MAX, FLT_MAX);
	col.box.Center = SimpleMath::Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

	return 0;
}
