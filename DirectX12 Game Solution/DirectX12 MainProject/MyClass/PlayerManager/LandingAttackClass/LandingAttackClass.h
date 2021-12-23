#pragma once
#include"Base/pch.h"
#include"Base/pch.h"
#include <Base/DX12Effekseer.h>
#include <random>

using namespace DirectX;

class LandingAttackClass
{
public:
	LandingAttackClass() {};
	~LandingAttackClass() {};
	void Initialize();
	void LoadAseets();
	void Update();
	void Render();
	//
	void tarai_attack(Vector3 enemy_pos);
private:
	SimpleMath::Vector3 enemy_pos;
	DX9::MODEL tarai;
	std::mt19937 random_landing;
	std::uniform_int_distribution<int> distribute;
	SimpleMath::Vector3 tarai_pos;
	float deltaTime;
	enum RANDOMTARAI
	{
		MIN = 20,
		MAX =30
	};
};

