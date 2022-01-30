#pragma once
#include "Base/DX12Effekseer.h"
#include "Coin/Coin.h"
#include <random>

using namespace DirectX;

class CoinManager {
public:
	CoinManager() {}
	~CoinManager() {}

	int  Update(const float deltaTime);

	std::vector<Coin*> GetCoin() { return coin; }
	void OnCollisionEnter(Coin* this_coin);
	void ComboCoin();
private:
	void Iterator();
	void Generator();
	Coin* Create(SimpleMath::Vector3 position);

	std::mt19937 random;
	std::uniform_int_distribution<int> distribute;

	std::vector<Coin*> coin;
	int combo;
};