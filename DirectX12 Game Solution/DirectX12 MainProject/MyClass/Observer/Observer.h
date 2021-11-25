#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"
#include "MyClass/EnemyManager/EnemyManager.h"


class Observer {
public:
	int  Update(PlayerBase* player, EnemyManager* enemy);
	void CollisionDetection(PlayerBase* player, EnemyManager* enemy);
};