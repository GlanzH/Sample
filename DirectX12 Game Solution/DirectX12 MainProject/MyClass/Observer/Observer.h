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
};