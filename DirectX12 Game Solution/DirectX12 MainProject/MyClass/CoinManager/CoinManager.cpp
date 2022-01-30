#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CoinManager.h"
#include"Coin/Coin.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/EnumManager/EnumManager.h"
#include <MyClass/ResourceManager/ResourceManager.h>

/**
 * @detail コインを出現させる条件させるになったら、
 * 　　　　コインを出現させる枚数を決める関数をもとに求めた個数分
 * 　　　　Generator関数でコインを作る。
 */

void CoinManager::LoadAssets(SimpleMath::Vector3 position)
{
	manycoin = ResourceManager::Instance().LoadEffect(L"Effect/CoinEffect/many_coin/many_coin.efk");
	pos.x = rand() % 10 + -1;
	pos.y = 0.0f;
	pos.z = 50.0f;
}

int CoinManager::Update(const float deltaTime) {
	Iterator();

	Generator();

	if (coin.size() > 0) {
		for (auto coins : coin) {
			coins->Update(deltaTime);
		}
	}

	return 0;
}

/**
 * @fn 条件によってモーションを切り替える
 * @return なし
 * @detail 敵を倒した数(コンボ数)によってコインを出現させる枚数を決める関数を作り、
 * 　　　　for文でその数コインを作成させる
 */
void CoinManager::Generator() {
	std::random_device pos_x_seed;
	random = std::mt19937(pos_x_seed());

	//for(int i = 0; i < 個数; ++i){
	distribute = std::uniform_int_distribution<int>(-60, 60);
	 int pos_x = distribute(random);


	 for (combo = 0; combo<6; combo++)
	 {
		 ComboCoin(combo);
	 }
	//coin.push_back(Create(SimpleMath::Vector3(pos_x, 0,80)));
	//}
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
			if ((*itr)->LifeDeathDecision() == DEAD) {
				StatusManager::Instance().SetAddScore(30);
				itr = coin.erase(itr);
			}
			else {
				itr = coin.erase(itr);
			}
		}
	}
}

void CoinManager::OnCollisionEnter(Coin* this_coin) {
	this_coin->GetCoin();
}

void CoinManager::ComboCoin(int coincount)
{
	switch (combo)
	{
	case 1:
		manycoin_handle = DX12Effect.Play(manycoin, pos);
		break;
	case 2:
		manycoin_handle = DX12Effect.Play(manycoin, pos);
		break;
	case 3:
		manycoin_handle = DX12Effect.Play(manycoin, pos);
		break;
	case 4:
		manycoin_handle = DX12Effect.Play(manycoin, pos);
		break;
	case 5:
		manycoin_handle = DX12Effect.Play(manycoin, pos);
		break;
	default:
		if (combo >= 6) {
			manycoin_handle = DX12Effect.Play(manycoin, pos);
		}
		break;
	}
}
