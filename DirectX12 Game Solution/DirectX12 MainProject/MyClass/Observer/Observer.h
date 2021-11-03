#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/PlayerManager/PlayerManager.h"
#include "MyClass/EnemyManager/EnemyManager.h"

class Observer {
public:
	int  Update(PlayerManager* player, EnemyManager* enemy, Sword* sword);
	void CollisionDetection(PlayerManager* player, EnemyManager* enemy, Sword* sword);
};