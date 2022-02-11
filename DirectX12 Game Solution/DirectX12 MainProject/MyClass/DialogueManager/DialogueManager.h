#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class DialogueManager {
public:
	void LoadAssets();
	void Render(int dialogue_count);
	void AddCount(bool time_stop_flag);
	void ResetCount() { dialogue_state = 0; }
private:
	DX9::SPRITE dialogue_1;
	DX9::SPRITE dialogue_2;
	DX9::SPRITE dialogue_3;
	DX9::SPRITE dialogue_4;
	DX9::SPRITE dialogue_5;
	DX9::SPRITE dialogue_6;
	DX9::SPRITE dialogue_7;
	DX9::SPRITE dialogue_8;
	DX9::SPRITE dialogue_9;
	DX9::SPRITE dialogue_10;
	DX9::SPRITE dialogue_11;
	DX9::SPRITE dialogue_12;
	DX9::SPRITE dialogue_13;
	DX9::SPRITE dialogue_14;
	DX9::SPRITE dialogue_15;
	DX9::SPRITE dialogue_16;
	DX9::SPRITE dialogue_17;
	DX9::SPRITE dialogue_18;
	DX9::SPRITE dialogue_19;
	DX9::SPRITE dialogue_20;
	DX9::SPRITE dialogue_21;
	DX9::SPRITE dialogue_22;
	DX9::SPRITE dialogue_23;
	DX9::SPRITE dialogue_24;

	int dialogue_state = 0;

	enum DialogueNum {
		FIRST  = 1,
		SECOND,
		THIRD,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		ELEVEN,
		TWELVE
	};
};