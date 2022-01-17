#include "PlayerAttack.h"

#include "MyClass/PlayerManager/PlayerBase/PlayerBase.h"

PlayerAttack::PlayerAttack() {
	//First
	first_burst_flag  = false;
	first_burst_start = 0.0f;
	first_burst_end   = 0.0f;

	//Second
	second_burst_flag  = false;
	second_burst_start = 0.0f;
	second_burst_end   = 0.0f;

	//THIRD
	third_burst_flag  = false;
	third_burst_start = 0.0f;
	third_burst_end   = 0.0f;

}

void PlayerAttack::Initialize() {

}

//First
void PlayerAttack::First_Burst(const float deltaTime) {

}
//Second
void PlayerAttack::Second_Burst(const float deltaTime) {

}
//Third
void PlayerAttack::Third_Burst(const float deltaTime) {

}

