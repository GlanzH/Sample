#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CoinManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/EnumManager/EnumManager.h"

void CoinManager::LoadAssets() {
	for (auto coin : coin_base) {
		coin->LoadAssets();
	}
}

int CoinManager::Update() {
	Iterator();
	Generator();
	for (auto coin : coin_base) {
		coin->Update();
	}
	return 0;
}

void CoinManager::Iterator() {
	for (auto itr = coin.begin(); itr != coin.end();)
	{
		if ((*itr)->LifeDeathDecision() == LIVE) {
			itr++;
		}
		else {
			itr = coin.erase(itr);
		}
	}
}

void CoinManager::OnCollisionEnter(Coin* this_coin) {
	this_coin->GetCoin();
}