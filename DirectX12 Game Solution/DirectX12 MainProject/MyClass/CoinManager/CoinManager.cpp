#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CoinManager.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/EnumManager/EnumManager.h"

int CoinManager::Update() {
	Iterator();

	if (!test_flag) {
		Generator();
		test_flag = true;
	}

	for (auto coins : coin) {
		coins->Update();
	}
	return 0;
}

void CoinManager::Render() {
	for (auto coins : coin) {
		coins->Render();
	}
}

void CoinManager::Generator() {
	coin.push_back(Create(SimpleMath::Vector3(30,0,70)));
}

Coin* CoinManager::Create(SimpleMath::Vector3 position) {
	Coin* create_coin = new Coin;
	create_coin->LoadAssets(position);

	return create_coin;
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