#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class AudienceManager {
public:
	AudienceManager() {}
	~AudienceManager() {}
	void LoadAssets();
	int  Update(const float deltaTime);
	void Render();

private:
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack);

	DX9::MODEL	audience;
	DX9::MODEL  collision;

	float time = 0.0f;
	float delta;

	float throw_frame = 0.0f;
	const float max_throw = 3.0f;

	float col_frame = 0.0f;

	enum {
		FIRST,
		MAX_MOTION
	};
};