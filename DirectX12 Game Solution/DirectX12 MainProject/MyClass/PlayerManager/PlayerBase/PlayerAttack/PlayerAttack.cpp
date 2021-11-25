#include "PlayerAttack.h"
#include "MyClass/StatusManager/StatusManager.h"


void PlayerAttack::LoadAssets() {
	DX12Effect.Initialize();
	Sword_Effect_1 = DX12Effect.Create(L"Effect\\SwordEffect\\one\\first_attack.efk");
	Sword_Effect_2 = DX12Effect.Create(L"Effect\\SwordEffect\\two\\second_attack.efk");
	Sword_Effect_3 = DX12Effect.Create(L"Effect\\SwordEffect\\three\\third_attack.efk");

}

void PlayerAttack::Player_Attack(const float deltaTime) {


}