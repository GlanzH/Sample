#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class AudienceManager {
public:
	AudienceManager() {}
	~AudienceManager() {}
	void LoadAssets();
	int  Update(const float deltaTime);
	void Render();
	bool GetThrowThingsFlag() { return throw_things_flag; }
private:
	void SetAnimation(DX9::SKINNEDMODEL& model, const int enabletack);

	DX9::MODEL		  audience;
	DX9::SKINNEDMODEL model;
	DX9::SKINNEDMODEL throw_things_lv2;

	bool throw_things_flag = false;

	enum {
		FIRST,
		MAX_MOTION
	};
};