#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

typedef struct AudieceCol
{
	BoundingBox lv2_box;
};

class AudienceManager {
public:
	AudienceManager() {}
	~AudienceManager() {}
	void LoadAssets();
	int  Update(float appeal_time, const float deltaTime);
	void Render();
	bool GetThrowThingsFlag() { return throw_things_flag; }

	AudieceCol GetBox() { return col; }

private:
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack);

	DX9::MODEL		  audience;
	DX9::SKINNEDMODEL throw_things_lv1;
	DX9::SKINNEDMODEL throw_things_lv2;

	DX9::MODEL  collision;

	AudieceCol col;

	SimpleMath::Vector3 fill_theater_pos = SimpleMath::Vector3(  0, 20, 50);
	SimpleMath::Vector3 fill_theater_col = SimpleMath::Vector3(250, 50, 10);

	float time = 0.0f;

	float throw_frame = 0.0f;
	const float max_throw = 3.0f;

	float col_frame = 0.0f;
	const float  max_col = 0.1f;

	bool throw_things_flag = false;

	enum {
		FIRST,
		MAX_MOTION
	};
};