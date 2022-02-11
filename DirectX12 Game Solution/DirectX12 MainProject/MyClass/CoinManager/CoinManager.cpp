#include "Base/pch.h"
#include "Base/dxtk.h"
#include "CoinManager.h"
#include "MyClass/EnumManager/EnumManager.h"
#include"MyClass/StatusManager/StatusManager.h"
#include <MyClass/ResourceManager/ResourceManager.h>

/**
 * @detail コインを出現させる条件させるになったら、
 * 　　　　コインを出現させる枚数を決める関数をもとに求めた個数分
 * 　　　　Generator関数でコインを作る。
 */

void CoinManager::LoadAssets()
{
	manycoin = ResourceManager::Instance().LoadEffect(L"Effect/CoinEffect/many_coin/many_coin.efk");

	effect_frame = 0.0f;

	create_coins = 0;
	create_coin_flag = false;
	for (int i = 0; i < COIN_MAX; i++)
	{
		coin.push_back(new Coin());
		coin[i]->LoadAssets();
	}

}

int CoinManager::Update(SimpleMath::Vector3 position, bool death_flag, int death_enemy, const float deltaTime) {

	pos = SimpleMath::Vector3(position.x, 0, 50);
	DX12Effect.SetRotation(manycoin_handle, Vector3(0, 160, 0));

	if (death_flag && death_enemy > 0) {
		if (!DX12Effect.CheckAlive(manycoin_handle))
		{
			if (StatusManager::Instance().GetTime()>=0.1f)
			{
				manycoin_handle = DX12Effect.Play(manycoin, pos);
			}
		}
			

		create_coin_flag = true;
	}

	if (create_coin_flag) {
		if (effect_frame < max_effect) {
			effect_frame += deltaTime;
		}
		else {
			if (StatusManager::Instance().GetTime()>=0.1f)
			{
				ComboCoin(death_enemy);
				create_coin_flag = false;
			}
			
		}
	}

	for (int i = 0; i < create_coins; i++) {
		coin[i]->Update(deltaTime);
	}
	
	for (int i = 0; i < create_coins; i++)
	{
		if (coin[i]->CheckDeath())
			continue;
		if (!coin[create_coins - 1]->CheckDeath())
			create_coins = 0;
	}

	return 0;
}

/**
 * @fn 条件によってモーションを切り替える
 * @detail 敵を倒した数(コンボ数)によってコインを出現させる枚数を決める関数を作り、
 * 　　　　for文でその数コインを作成させる
 */
void CoinManager::Generator() {
	std::random_device pos_x_seed;
	random = std::mt19937(pos_x_seed());

	for (int i = 0; i < create_coins; ++i) {
		distribute = std::uniform_int_distribution<int>(-60, 60);
		int pos_x = distribute(random);
		coin[i]->SetPos(Vector3(pos_x, 0, 80));
		coin[i]->RenderCoin();
	}
}

void CoinManager::ComboCoin(int combocoin)
{
	switch (combocoin)
	{
	case 1:
		create_coins = 1;
		Generator();
		break;
	case 2:
		create_coins = 2;
		Generator();
		break;
	case 3:
		create_coins = 4;
		Generator();
		break;
	case 4:
		create_coins = 7;
		Generator();
		break;
	case 5:
		create_coins = 11;
		Generator();
		break;
	case 6:
		create_coins = 13;
			Generator();
		break;
	case 7:
		create_coins = 15;
			Generator();
		break;
	default:
		if (combocoin >= 8) {
			create_coins = 16;
		}
		Generator();
		break;
	}
}
