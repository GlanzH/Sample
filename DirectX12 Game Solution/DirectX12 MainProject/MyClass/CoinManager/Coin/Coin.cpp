#include "MyClass/EnumManager/EnumManager.h"
#include "MyClass/ResourceManager/ResourceManager.h"
#include "Coin.h"

void Coin::LoadAssets() {
	pos  = Vector3::Zero;
	coin = ResourceManager::Instance().LoadEffect(L"Effect/CoinEffect/coin/coin.efk");
	plus = ResourceManager::Instance().LoadEffect(L"Effect/CoinEffect/plus/plus.efk");
	getcoin = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM_SE/BGM/coin05.mp3");
	D3DMATERIAL9 material;
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.0f);
	material.Ambient = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);
	material.Specular = DX9::Colors::Value(0.0f, 0.0f, 0.0f, 0.0f);

	collision = DX9::Model::CreateBox(DXTK->Device9,5, 5, 5);
	collision->SetMaterial(material);

	death_coin_flag = false;

	wait_frame    = 0.0f;
	
}

int Coin::Update(const float deltaTime) {
	
	if (dest_frame < max_dest)
		dest_frame += deltaTime;

	if (dest_frame >= max_dest)
	{
		DX12Effect.Stop(coin_handle);
		death_coin_flag = true;
	}
		

	return 0;
}

void Coin::RenderCoin()
{
	death_coin_flag = false;
	SimpleMath::Vector3 col_pos = SimpleMath::Vector3(pos.x, pos.y + 4, 50);
	collision->SetPosition(col_pos);
	box = collision->GetBoundingBox();
	box.Center = col_pos;

	if (!DX12Effect.CheckAlive(coin_handle))
		coin_handle = DX12Effect.Play(coin, pos);
}

void Coin::OnCollisionEnter()
{
	box.Center = Vector3(INT_MAX, INT_MAX, INT_MAX);

	if (!DX12Effect.CheckAlive(plus_handle))
		plus_handle = DX12Effect.Play(plus, pos);

	StatusManager::Instance().SetAddScore(30);
	getcoin->Play();
	DX12Effect.Stop(coin_handle);

	dest_frame = 0;
	death_coin_flag = true;
}
