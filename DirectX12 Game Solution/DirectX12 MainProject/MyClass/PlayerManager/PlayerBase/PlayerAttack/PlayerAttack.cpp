#include "PlayerAttack.h"
#include "MyClass/StatusManager/StatusManager.h"


void PlayerAttack::LoadAssets() {
	DX12Effect.Initialize();
	DX12Effect.Create(L"Effect\\SwordEffect\\one\\first_attack.efk","first");
	DX12Effect.Create(L"Effect\\SwordEffect\\two\\second_attack.efk","second");
	DX12Effect.Create(L"Effect\\SwordEffect\\three\\third_attack.efk","third");

}

void PlayerAttack::Player_Attack(const float deltaTime) {


}