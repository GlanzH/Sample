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
	
	int GetWaveEnemyNum() { return wave_enemy; }

private:
	DX9::SPRITEFONT font;

	DX9::SPRITE time;
	DX9::SPRITE time_number;

	int wave_enemy = 0;

	int time_one_digit;	//1���ڕ\���ϐ�
	int time_two_digit;	//2���ڕ\���ϐ�
	int now_time;	//���݂̎���

	float one_digit_pos_x; //1���ڂ̏ꏊ
	bool one_digit_flag;	//�^�C����1���ɂȂ������t���O

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