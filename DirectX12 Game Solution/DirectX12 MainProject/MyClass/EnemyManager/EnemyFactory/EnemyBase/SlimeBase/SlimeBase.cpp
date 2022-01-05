#include "SlimeBase.h"

SlimeClass::SlimeClass()
{
}

int SlimeClass::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime)
{
	delta = deltaTime;
	player_pos = player;

	if (enemy_tag == "S" || enemy_tag == "H") {
		EnemyAnimation();
		anim_box.Center = anim_model->GetPosition();
		anim_model->SetPosition(position);
		anim_collision->SetPosition(anim_model->GetPosition() + SimpleMath::Vector3(0, fit_collision_y, 0));
	}

	if (retreat_flag && retreat_count < max_retreat) {
		if (player.x < position.x)
			position.x += retreat_dist * deltaTime;
		else
			position.x -= retreat_dist * deltaTime;

		retreat_count++;
	}
	else {
		retreat_flag = false;
		retreat_count = 0;
	}

	if (position.z < 15.0f) {
		explode.Update(position, delta);

		if (!reduce_audience_flag) {
			if (enemy_tag == "S")
				StatusManager::Instance().AddAudience(6);
			else if (enemy_tag == "H")
				StatusManager::Instance().AddAudience(8);
			reduce_audience_flag = true;
		}
	}

	StatusManager::Instance().DownAudience(delta);

	return 0;
}
