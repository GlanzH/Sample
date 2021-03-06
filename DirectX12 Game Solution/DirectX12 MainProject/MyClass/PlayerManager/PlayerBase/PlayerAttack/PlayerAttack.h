#pragma once

#include "Base/DX12Effekseer.h"
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

using namespace DirectX;

class PlayerAttack
{
public:
	PlayerAttack();
	virtual ~PlayerAttack() = 0;

	void Initialize();
	void LoadAssets();

	//降り下ろし
	void Swing_Down(DX9::SKINNEDMODEL model, const float deltaTime);
	//切り上げ
	void Reverse_Slash(DX9::SKINNEDMODEL model, const float deltaTime);

private:



};