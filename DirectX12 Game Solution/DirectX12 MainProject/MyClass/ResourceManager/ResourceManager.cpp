#include "Base/pch.h"
#include "Base/dxtk.h"
#include "ResourceManager.h"

EFFECT ResourceManager::LoadEffect(LPCWSTR effect) {
	auto&& itr = effect_name.find(effect);

	if (itr != effect_name.end()) {
		return itr->second;
	}
	else {
		EFFECT efk = DX12Effect.Create(effect);
		effect_name.emplace_hint(effect_name.end(),effect,efk);
		return effect_name[effect];
	}

}