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
	int  Update(SimpleMath::Vector3 position,bool death_flag, int death_enemy,const float deltaTime);

	std::vector<Coin*> GetCoin() { return coin; }
	void OnCollisionEnter(Coin* this_coin);
	void ComboCoin(int combocoin);
private:
	void Iterator();
	void Generator();

	Coin* Create(SimpleMath::Vector3 position);

	EFFECT manycoin;
	EFFECTHANDLE manycoin_handle;
	SimpleMath::Vector3 pos;
	std::mt19937 random;
	std::uniform_int_distribution<int> distribute;

	std::vector<Coin*> coin;
	int create_coins;

	bool create_coin_flag;

	float effect_frame;
	const float max_effect = 1.8f;
};