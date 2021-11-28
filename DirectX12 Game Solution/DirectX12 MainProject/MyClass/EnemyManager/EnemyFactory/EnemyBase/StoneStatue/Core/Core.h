#pragma once
#include "../../EnemyBase.h"

using namespace DirectX;

class Core : public EnemyBase
{
public:
	Core();
	~Core() {}
    bool Initialize(std::string tag,SimpleMath::Vector3 speed, int hp);
	int Update(SimpleMath::Vector3 player, const float deltaTime);
	void Attack(const float deltaTime);
	void Render();

private:
	void Shot();
	SimpleMath::Vector3 player_pos;

	int wait_count;
	enum class stone
	{
		STORAGE,
		CHARGE,
		ATTACK,
		WAIT,
		BACK,
		INIT,
	};
	stone  attack_method;
};