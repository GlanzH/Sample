#pragma once


#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class SwordManager
{
public:

	SwordManager(){}
	~SwordManager(){};

	bool Initialize();
	void LoadAssets();
	int Update(const float deltaTime);
	void Render();

private:

	DX9::MODEL sword_model_;
	SimpleMath::Vector3 sword_pos = SimpleMath::Vector3(0.0f, 5.0f, 50.0f);
	

};