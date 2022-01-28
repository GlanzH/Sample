#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Base/DX12Effekseer.h"

using namespace DirectX;

class Coin {
public:
	void LoadAssets(SimpleMath::Vector3 position);
	int Update();
	void Render();

	int  LifeDeathDecision();
	void GetCoin() { get_coin_flag = true; }

	BoundingBox GetBox() { return box; }

private:
	DX9::MODEL  collision;
	BoundingBox box;

	EFFECTHANDLE many_coin_handle, coin_handle;
	EFFECT       many_coin, coin;

	SimpleMath::Vector3 pos;
	SimpleMath::Vector3 col_pos;

	bool get_coin_flag = false;
};