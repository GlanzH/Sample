#pragma once
#include "Base/DX12Effekseer.h"

class Coin {
public:
	void LoadAssets();
	int Update();

	void GetCoin() {}

private:
	EFFECTHANDLE many_coin_handle, coin_handle;
	EFFECT       many_coin, coin;
};