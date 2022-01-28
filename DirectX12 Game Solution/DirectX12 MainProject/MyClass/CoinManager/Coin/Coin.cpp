#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/ResourceManager/ResourceManager.h"
#include "Coin.h"

void Coin::LoadAssets(SimpleMath::Vector3 position) {
	pos  = position;
	coin = ResourceManager::Instance().LoadEffect(L"Effect/CoinEffect/coin/coin.efk");

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.0f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	collision = DX9::Model::CreateBox(DXTK->Device9,5, 5, 10);
	collision->SetMaterial(material);

	collision->SetPosition(pos.x, pos.y + 4, 50);
	
	box.Center = position;
	
}

int Coin::Update() {

	if (!get_coin_flag) {
		if (!DX12Effect.CheckAlive(coin_handle))
			coin_handle = DX12Effect.Play(coin, pos);
	}

	return 0;
}

void Coin::Render() {
	collision->Draw();
}

int Coin::LifeDeathDecision() {
	if (get_coin_flag)
		return DEAD;

	return LIVE;
}