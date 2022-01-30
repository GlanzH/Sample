#pragma once
#include "Base/DX12Effekseer.h"
#include "Coin/Coin.h"


class CoinManager {
public:
	CoinManager() {}
	~CoinManager() {}

	void LoadAssets();
	int  Update();

	std::vector<Coin*> GetCoin() { return coin; }
	void Iterator();
	void Generator();
	void OnCollisionEnter(Coin* this_coin);
private:
	std::vector<Coin*> coin;
};