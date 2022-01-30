#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/EnumManager/EnumManager.h"
#include "Coin.h"


void Coin::LoadAssets() {


}

int Coin::Update() {
	return 0;
}

int Coin::LifeDeathDecision() {
	if (get_coin_flag)
		return DEAD;

	return LIVE;
}
