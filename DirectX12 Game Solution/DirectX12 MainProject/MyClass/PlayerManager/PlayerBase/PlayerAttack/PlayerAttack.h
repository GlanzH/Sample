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

	//ç~ÇËâ∫ÇÎÇµ
	void Swing_Down(DX9::SKINNEDMODEL model, const float deltaTime);
	//êÿÇËè„Ç∞
	void Reverse_Slash(DX9::SKINNEDMODEL model, const float deltaTime);

private:



};