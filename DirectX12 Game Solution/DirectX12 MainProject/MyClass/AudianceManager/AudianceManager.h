#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

class AudianceManager {
public:
	AudianceManager() {}
	~AudianceManager() {}
	void LoadAssets();
	int  Update();
	void Render();
private:
	DX9::MODEL audiance;
};