#include "ResourceManager.h"

//DX9::SKINNEDMODEL& ResourceManager::LoadSkinnedModel(TCHAR skinned_model_name) {
//	auto&& itr = resource_skined_model.find(skinned_model_name);
//
//	if (itr != resource_skined_model.end()) {
//		return itr->second;
//	}
//	else {
//		DX9::SKINNEDMODEL skinned_model =
//			DX9::SkinnedModel::CreateFromFile(
//				DXTK->Device9,
//				skinned_model_name.c_str();
//			);
//
//		resource_skined_model.emplace_hint(
//			resource_skined_model.end(),
//			skinned_model_name,
//			skinned_model
//		);
//
//		return resource_skined_model[skinned_model_name];
//	}
//}
//
//DX9::MODEL& ResourceManager::LoadModel(std::wstring model_name) {
//	auto&& itr = resource_model.find(model_name);
//
//	if (itr != resource_model.end()) {
//		return itr->second;
//	}
//	else {
//		DX9::MODEL model =
//			DX9::Model::CreateFromFile(
//				DXTK->Device9,
//				model_name.c_str()
//			);
//
//		resource_model.emplace_hint(
//			resource_model.end(),
//			model_name,
//			model
//		);
//
//		return resource_model[model_name];
//	}
//}

DX9::SPRITE	ResourceManager::LoadSprite(std::wstring sprite_name) {
	auto&& itr = resource_sprite.find(sprite_name);

	if (itr != resource_sprite.end()) {
		return itr->second;
	}
	else {
		DX9::SPRITE sprite = 
			DX9::Sprite::CreateFromFile(
				DXTK->Device9,
				sprite_name.c_str()
			);

		resource_sprite.emplace_hint(
			resource_sprite.end(),
			sprite_name,
			sprite
		);

		return resource_sprite[sprite_name];
	}
}

DX9::SPRITEFONT ResourceManager::LoadFontFromFile(std::wstring font_file,std::wstring font_name, float size) {
	auto&& itr = resource_font.find(font_file);

	if (itr != resource_font.end()) {
		return itr->second;
	}
	else {
		DX9::SPRITEFONT font = 
			DX9::SpriteFont::CreateFromFontFile(
				DXTK->Device9,
				font_file.c_str(),
				font_name.c_str(),
				size
			);

		resource_font.emplace_hint(
			resource_font.end(),
			font_file,
			font
		);

		return resource_font[font_file];
	}
}

DX9::SPRITEFONT ResourceManager::LoadFontFromName(std::wstring font_name, float size) {
	auto&& itr = resource_font.find(font_name);

	if (itr != resource_font.end()) {
		return itr->second;
	}
	else {
		DX9::SPRITEFONT font =
			DX9::SpriteFont::CreateFromFontName(
				DXTK->Device9,
				font_name.c_str(),
				size
			);

		resource_font.emplace_hint(
			resource_font.end(),
			font_name,
			font
		);

		return resource_font[font_name];
	}
}

EFFECT ResourceManager::LoadEffect(std::wstring effect_name) {
	auto&& itr = resource_effect.find(effect_name);

	if (itr != resource_effect.end()) {
		return itr->second;
	}
	else {
		EFFECT effect = DX12Effect.Create(effect_name.c_str());

		resource_effect.emplace_hint(
			resource_effect.end(),
			effect_name,
			effect
		);

		return resource_effect[effect_name];
	}
}