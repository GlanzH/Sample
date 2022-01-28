#pragma once
#include "Base/DX12Effekseer.h"
#include "Coin/Coin.h"

using namespace DirectX;

class CoinManager {
public:
	CoinManager() {}
	~CoinManager() {}

	int  Update();
	void Render();

	std::vector<Coin*> GetCoin() { return coin; }
	void OnCollisionEnter(Coin* this_coin);
private:
	void Iterator();
	void Generator();
	Coin* Create(SimpleMath::Vector3 position);

	std::vector<Coin*> coin;
	bool test_flag = false;
};