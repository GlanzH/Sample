#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "../../EnemyBase.h"

using namespace DirectX;

class FootHoldBase : public EnemyBase{
public:
	bool Initialize(std::string tag, bool time_stop_flag, int hp);
	int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);
	void Render();

	void OnCollisionEnter();
	void NotCollisionEnter();

	BoundingBox GetBox() { return box; }
	bool GetScaffoldFlag() { return scaffold_flag; }

private:
	DX9::MODEL model;
	DX9::MODEL collision;
	BoundingBox box;

	bool scaffold_flag = false;
};