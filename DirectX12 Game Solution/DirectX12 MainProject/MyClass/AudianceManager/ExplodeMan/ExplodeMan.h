#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ExplodeMan {
public:
	ExplodeMan() {}
	~ExplodeMan() {}

	void LoadAssets(float x);
	int  Update(SimpleMath::Vector3 position, const float deltaTime);
	void Render();
private:
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack);
	DX9::SKINNEDMODEL man;

	enum {
		EXPLODE_MAN,
		MAX_MOTION
	};

};