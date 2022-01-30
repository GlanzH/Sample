#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CoinManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/EnumManager/EnumManager.h"

void CoinManager::LoadAssets() {
	for (auto coin : coin) {
		coin->LoadAssets();
	}
}

int CoinManager::Update() {
	Iterator();
	Generator();
	for (auto coin : coin) {
		coin->Update();
	}
	return 0;
}


void CoinManager::Generator() {

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

void CoinManager::ComboCoin()
{
	switch (combo)
	{
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	default:
		if (combo >= 5) {
			float BonusCoin = (combo * 50.0f) - 100.0f;
		

		}
		break;
	}
}
