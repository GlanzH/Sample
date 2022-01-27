#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/EnemyManager/EnemyManager.h"
#include "MyClass/AudianceManager/AudianceManager.h"


class Observer {
public:
	int  Update(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience);
	void CollisionDetection(PlayerBase* player, EnemyManager* enemy, AudienceManager* audience);

	void Hit_Stop(const float deltaTime);

	bool GetHitStop() { return hit_stop_flag; }

	int GetHitCount() { return hit_stop_count; }

private:
	bool hit_stop_flag = false;
	float hit_stop_start = 0.0f;
	float hit_stop_end = 0.1f;

	//ヒットストップの終わり
	int hit_stop_count = 0;

	bool hit_attack_flag;
	float hit_attack_start = 0.0f;
	float hit_attack_end = 0.633f;

};