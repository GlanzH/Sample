#include "FootHoldBase.h"

bool FootHoldBase::Initialize(std::string tag, bool time_stop_flag, int hp) {
	EnemyBase::Initialize(tag,time_stop_flag,hp);

	return true;
}

int FootHoldBase::Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime) {
	EnemyBase::Update(player,special_attack_flag,thorow_things_flag,deltaTime);
	//scaffold_flag = false;

	return 0;
}

void FootHoldBase::Render() {
	EnemyBase::Render();
	//model->Draw();
	//collision->Draw();
}

void FootHoldBase::OnCollisionEnter() {
	scaffold_flag = true;
}

void FootHoldBase::NotCollisionEnter() {
	scaffold_flag = false;
}