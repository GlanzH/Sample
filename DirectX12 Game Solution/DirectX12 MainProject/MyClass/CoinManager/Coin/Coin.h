#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Base/DX12Effekseer.h"
#include "MyClass/StatusManager/StatusManager.h"

using namespace DirectX;

class Coin {
public:
	Coin() {};
	~Coin() {};
	void LoadAssets();
	int Update(const float deltaTime);
	void RenderCoin();

	void OnCollisionEnter();
	void SetPos(Vector3 Pos) { pos = Pos; }

	bool CheckDeath() { return death_coin_flag; };
	BoundingBox GetBox() { return box; }

private:
	DX9::MODEL  collision;
	BoundingBox box;

	EFFECTHANDLE  plus_handle,coin_handle;
	EFFECT        plus, coin;

	SimpleMath::Vector3 pos;
	SimpleMath::Vector3 col_pos;
	DX9::MEDIARENDERER getcoin;
	bool death_coin_flag;

	float dest_frame;
	const float max_dest = 10.0f;

	float wait_frame;
	const float max_wait = 0.5f;
};