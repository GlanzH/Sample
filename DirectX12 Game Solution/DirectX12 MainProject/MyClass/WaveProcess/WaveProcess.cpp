#include "WaveProcess.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/EnemyManager/EnemyFactory/EnemyFactory.h"

WaveProcess::WaveProcess() {

}

WaveProcess::~WaveProcess() {

}

bool WaveProcess::Initialize() {
	stage_num = 0;

	now_time = 0;
	time_one_digit = 0.0f;
	time_two_digit = 0;
	time_num_scale = 1.0f;
	scale_mode = EXPAND;
	one_digit_flag = false;

	time = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Time/TIME.png");
	time_number = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Time/numbers_timer.png");


	return true;
}

int WaveProcess::Update(EnemyManager* enemy, const float deltaTime) {
	StatusManager::Instance().WaveTimeLimit(deltaTime);

	now_time = StatusManager::Instance().GetTime();
	time_one_digit = (now_time % 10) * TIME_NUM_WIDTH;
	time_two_digit = (now_time / 10) * TIME_NUM_WIDTH;

	//if (StatusManager::Instance().GetWave() == 0) {
	//	max_stop = 0.01f;
	//}

	if (StatusManager::Instance().GetWave() < StatusManager::Instance().GetMaxWave() && now_time == 0) {
		if (stop_frame < max_stop) {
			one_digit_flag = false;
			stop_frame += deltaTime;
		}
		else {
			StatusManager::Instance().ResetWaveTime();
			StatusManager::Instance().SetWave(stage_num++);
			enemy->ResetRemainEnemy();
			enemy->ResetDeathEnemy();
			stop_frame = 0.0f;
			time_num_scale = 1.0f;
		}
	}

	if (now_time < 10) {
		one_digit_flag = true;
	}
	else {
		one_digit_flag = false;
	}

	if (one_digit_flag && now_time > 0) {
		if (scale_mode == EXPAND) {
			time_num_scale += 2.0f * deltaTime;
			if (time_num_scale > 2.0f) {
				scale_mode = SHRINK;
			}
		}
		if (scale_mode == SHRINK) {
			time_num_scale -= 2.0f * deltaTime;
			if (time_num_scale < 1.0f) {
				scale_mode = EXPAND;
			}
		}
	}

	return 0;
}

void WaveProcess::Render() {


	if (StatusManager::Instance().GetWave() > 0) {
		if (!one_digit_flag) {
			DX9::SpriteBatch->DrawSimple(
				time.Get(),
				SimpleMath::Vector3(TIME_POS_X, TIME_POS_Y, 0.0f)
			);

			DX9::SpriteBatch->DrawSimple(
				time_number.Get(),
				SimpleMath::Vector3(ONE_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
				RectWH(time_one_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
			);

			DX9::SpriteBatch->DrawSimple(
				time_number.Get(),
				SimpleMath::Vector3(TWO_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
				RectWH(time_two_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
			);
		}
		else {
			DX9::SpriteBatch->DrawSimple(
				time.Get(),
				SimpleMath::Vector3(TIME_POS_X, TIME_POS_Y, 0.0f),
				Rect(0, 0, TIME_WIDTH, TIME_HIGHT),
				DX9::Colors::RGBA(COLOR_MAX, 0, 0, COLOR_MAX)
			);

			DX9::SpriteBatch->Draw(
				time_number.Get(),
				SimpleMath::Vector3(TIME_POS_X + 50.0f, TIME_POS_Y + 70.0f, 0.0f),
				RectWH(time_one_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT),
				DX9::Colors::RGBA(COLOR_MAX, 0, 0, COLOR_MAX),
				SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
				SimpleMath::Vector3(TIME_NUM_ORIGIN_X, TIME_NUM_ORIGIN_Y, 0.0f),
				SimpleMath::Vector2(time_num_scale, time_num_scale)
			);
			DX9::SpriteBatch->ResetTransform();
		}
	}
}