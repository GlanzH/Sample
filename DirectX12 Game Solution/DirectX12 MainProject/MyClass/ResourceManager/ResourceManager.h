#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Base/DX12Effekseer.h"
#include <map>
#include <string>


class ResourceManager {
public:

	//DX9::SKINNEDMODEL& LoadSkinnedModel(TCHAR skinned_model_name);
	//DX9::MODEL&		   LoadModel(TCHAR model_name);

	DX9::SPRITE		  LoadSprite(std::wstring sprite_name);
	DX9::SPRITEFONT   CreateFontFromFile(std::wstring font_file,std::wstring font_name, float size);
	DX9::SPRITEFONT   CreateFontFromName(std::wstring font_name, float size);

	EFFECT LoadEffect(std::wstring effect_name);

	static ResourceManager& Instance() {
		static ResourceManager instance;
		return instance;
	}

private:
	//std::map<TCHAR,DX9::SKINNEDMODEL>  resource_skined_model;
	//std::map<TCHAR,DX9::MODEL>		  resource_model;

	std::map<std::wstring, DX9::SPRITE>		  resource_sprite;
	std::map<std::wstring, DX9::SPRITEFONT>   resource_font;
	std::map<std::wstring, EFFECT>			  resource_effect;
};