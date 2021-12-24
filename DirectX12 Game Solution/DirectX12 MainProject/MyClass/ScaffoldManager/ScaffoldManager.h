#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ScaffoldManager {
public:
	void LoadAssets();
	int Update();
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