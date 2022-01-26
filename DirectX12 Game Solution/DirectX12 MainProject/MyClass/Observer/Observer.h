#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/EnemyManager/EnemyManager.h"
#include "MyClass/AudianceManager/AudianceManager.h"


class Observer {
public:
	int  Update(PlayerBase* player, EnemyManager* enemy,AudienceManager* audience);
	void CollisionDetection(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience);

	void Hit_Stop(const float deltaTime);

	bool GetHitStop() { return hit_stop_flag; }

private:
	bool hit_stop_flag = false;
	float hit_stop_start = 0.0f;
	float hit_stop_end = 0.1f;

};