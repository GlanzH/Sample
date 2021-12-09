#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class DialogueManager {
public:
	void LoadAssets();
	int Update(bool time_stop_flag);
	void Render(int dialogue_count);
private:
	DX9::SPRITE dialogue_1;
	DX9::SPRITE dialogue_2;
	DX9::SPRITE dialogue_3;
	DX9::SPRITE dialogue_4;
	DX9::SPRITE dialogue_5;
	DX9::SPRITE dialogue_6;

	int dialogue_state = 0;

	enum DialogueNum {
		FIRST  = 1,
		SECOND = 2,
		THIRD  = 3
	};
};