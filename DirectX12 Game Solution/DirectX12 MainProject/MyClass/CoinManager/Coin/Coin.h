#pragma once
#include "Base/DX12Effekseer.h"

class Coin {
public:
	void LoadAssets();
	int Update();

	int  LifeDeathDecision();
	void GetCoin() { get_coin_flag = true; }

private:
	EFFECTHANDLE many_coin_handle, coin_handle;
	EFFECT       many_coin, coin;

	bool get_coin_flag = false;
};