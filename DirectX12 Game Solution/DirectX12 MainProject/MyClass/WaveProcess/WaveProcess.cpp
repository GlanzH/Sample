#include "WaveProcess.h"
#include "MyClass/StatusManager/StatusManager.h"

WaveProcess::WaveProcess() {

}

WaveProcess::~WaveProcess() {

}

bool WaveProcess::Initialize() {
	stage_num = 0;

	now_time = 0;
	time_one_digit = 0.0f;
	one_digit_pos_x = TIME_POS_X + 45.0f;
	time_two_digit = 0;
	one_digit_flag = false;

	time = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/TIME.png");
	time_number = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/numbers_timer.png");


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
			stop_frame += deltaTime;
		}
		else {
			StatusManager::Instance().SetWave(stage_num++);
			enemy->ResetRemainEnemy();
			enemy->ResetDeathEnemy();
			wave_enemy = enemy->GetWaveEnemy();
			stop_frame = 0.0f;
		}
	}

	if (now_time < 10) {
		one_digit_flag = true;
		one_digit_pos_x = TIME_POS_X + 15.0f;
	}
	else {
		one_digit_flag = false;
		one_digit_pos_x = TIME_POS_X + 45.0f;
	}

	return 0;
}

void WaveProcess::Render() {

	DX9::SpriteBatch->DrawSimple(
		time.Get(),
		SimpleMath::Vector3(TIME_POS_X, TIME_POS_Y, 0.0f)
	);

	if (StatusManager::Instance().GetWave() > 0) {
		if (!one_digit_flag) {
			DX9::SpriteBatch->DrawSimple(
				time_number.Get(),
				SimpleMath::Vector3(one_digit_pos_x, TIME_NUM_POS_Y, 0.0f),
				RectWH(time_one_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT),
				DX9::Colors::RGBA(255, 255, 255, 255)
			);

			DX9::SpriteBatch->DrawSimple(
				time_number.Get(),
				SimpleMath::Vector3(TWO_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
				RectWH(time_two_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
			);
		}
		else {
			DX9::SpriteBatch->DrawSimple(
				time_number.Get(),
				SimpleMath::Vector3(one_digit_pos_x, TIME_NUM_POS_Y, 0.0f),
				RectWH(time_one_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT),
				DX9::Colors::RGBA(255, 0, 0, 255)
			);
		}
	}
}