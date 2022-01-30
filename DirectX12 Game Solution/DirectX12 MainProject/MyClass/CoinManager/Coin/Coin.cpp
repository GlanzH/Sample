#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/ResourceManager/ResourceManager.h"
#include "Coin.h"

void Coin::LoadAssets(SimpleMath::Vector3 position) {
	pos  = position;
	coin = ResourceManager::Instance().LoadEffect(L"Effect/CoinEffect/coin/coin.efk");
	plus = ResourceManager::Instance().LoadEffect(L"Effect/CoinEffect/plus/plus.efk");

	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.0f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	collision = DX9::Model::CreateBox(DXTK->Device9,5, 5, 5);
	collision->SetMaterial(material);
	
	SimpleMath::Vector3 col_pos = SimpleMath::Vector3(pos.x, pos.y + 4, 50);
	collision->SetPosition(col_pos);

	box = collision->GetBoundingBox();
	box.Center = col_pos;

	stop_flag     = false;
	get_coin_flag = false;
	wait_frame    = 0.0f;

	if (!DX12Effect.CheckAlive(coin_handle))
		coin_handle = DX12Effect.Play(coin, pos);
	
}

int Coin::Update(const float deltaTime) {
	if (get_coin_flag) {
		if (wait_frame < max_wait)
			wait_frame += deltaTime;

		 if (!DX12Effect.CheckAlive(plus_handle))
			 plus_handle = DX12Effect.Play(plus, pos);

		else
			stop_flag = true;
	}

	if (dest_frame < max_dest)
		dest_frame += deltaTime;

	return 0;
}

int Coin::LifeDeathDecision() {
	if (stop_flag) {
		DX12Effect.Stop(coin_handle);
		return DEAD;
	}

	if (dest_frame >= max_dest) {
		DX12Effect.Stop(coin_handle);
		return AUTO;
	}

	return LIVE;
}