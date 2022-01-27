#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "MyClass/EnemyManager/EnemyManager.h"

using namespace DirectX;

class WaveProcess {
public:
	WaveProcess();
	~WaveProcess();
	bool Initialize();
	int Update(EnemyManager* enemy, const float deltaTime);
	void Render();
private:
	DX9::SPRITEFONT font;

	DX9::SPRITE time;
	DX9::SPRITE time_number;

	int time_one_digit;	//1桁目表示変数
	int time_two_digit;	//2桁目表示変数
	int now_time;	//現在の時間

	float one_digit_pos_x; //1桁目の場所
	bool one_digit_flag;	//タイムが1桁になったかフラグ

	const int TIME_NUM_WIDTH = 56;
	const int TIME_NUM_HIGHT = 70;

	const float TIME_POS_X = 560.0f;
	const float TIME_POS_Y = 20.0f;
	const float TWO_DIGIT_POS_X = TIME_POS_X - 5.0f;
	const float TIME_NUM_POS_Y = TIME_POS_Y + 40.0f;


	float stop_frame = 0.0f;
	float max_stop   = 2.0f;

	int stage_num = 0;
};