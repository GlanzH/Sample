#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Ground {
public:
	Ground() {};
	~Ground() {};

	void LoadAsset();
	int Update(const float deltaTime);
	void Render();

	DX9::MODEL& GetModel() { return a; }

private:
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack, int max_motion);
	DX9::MODEL model;
	DX9::MODEL a;
	DX9::SKINNEDMODEL town;
	DX9::SKINNEDMODEL forest;
	DX9::SKINNEDMODEL ruins;

	enum class Forest {
		START,
		MOVE,
		PLAY,
		SCROLL,
		END,
		MAX_MOTION
	};

	SimpleMath::Vector3 pos;

	const float box_size =   2.0f;
	const float pos_y	 = 25.0f;
};