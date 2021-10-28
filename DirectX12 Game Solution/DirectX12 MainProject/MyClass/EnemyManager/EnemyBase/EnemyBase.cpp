#include "Base/pch.h"
#include "Base/dxtk.h"
#include "EnemyBase.h"

bool EnemyBase::Initialize() {

	return false;
}

void EnemyBase::LoadAsset() {

}

int EnemyBase::Update(const float deltaTime) {
	return LIVE;
}

void EnemyBase::Damage() {
	hp--;
}

void EnemyBase::Render() {

}