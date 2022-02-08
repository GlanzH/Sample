#pragma once
#include "Base/DX12Effekseer.h"
#include "Coin/Coin.h"
#include <random>

using namespace DirectX;

class CoinManager {
public:
	CoinManager() {}
	~CoinManager() {}
	void LoadAssets();
	int  Update(SimpleMath::Vector3 position, bool death_flag, int death_enemy, const float deltaTime);

	std::vector<Coin*> GetCoin() { return coin; }
	void ComboCoin(int combocoin);
private:
	void Generator();

	std::mt19937 random;
	std::uniform_int_distribution<int> distribute;

	EFFECT manycoin;
	EFFECTHANDLE manycoin_handle;
	SimpleMath::Vector3 pos;

	std::vector<Coin*> coin;
	int create_coins;

	bool create_coin_flag;

	float effect_frame;

	const int COIN_MAX = 16;
	const float max_effect = 1.8f;
};