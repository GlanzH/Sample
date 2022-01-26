#include "Timer.h"
#include "MyClass/StatusManager/StatusManager.h"

Timer::Timer() {

}

Timer::~Timer() {

}

bool Timer::Initialize() {
	stage_num = 0;

	time_one_digit = 0.0f;
	time_two_digit = 0;

	time = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/TIME.png");
	time_number = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/numbers_timer.png");

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	return true;
}

int Timer::Update(EnemyManager* enemy, const float deltaTime) {
	StatusManager::Instance().WaveTimeLimit(deltaTime);

	time_one_digit = StatusManager::Instance().GetTime();

	if (StatusManager::Instance().GetWave() < 3 && StatusManager::Instance().GetTime() == 0.0f) {

		if (stop_frame < max_stop) {
			stop_frame += deltaTime;
			time_one_digit = std::max(time_one_digit - deltaTime, 0.0f);
		}
		else {
			StatusManager::Instance().SetWave(stage_num++);
			enemy->ResetRemainEnemy();
			enemy->ResetDeathEnemy();
			stop_frame = 0.0f; 
		}
	}

	return 0;
}

void Timer::Render() {

		DX9::SpriteBatch->DrawSimple(
			time.Get(),
			SimpleMath::Vector3(TIME_POS_X, TIME_POS_Y, 0.0f)
		);

		//DX9::SpriteBatch->DrawString(
		//	font.Get(),,
		//	SimpleMath::Vector3(1000, 50, 0.0f)
		//);

	if (StatusManager::Instance().GetWave() > 0) {
		DX9::SpriteBatch->DrawSimple(
			time_number.Get(),
			SimpleMath::Vector3(ONE_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
			RectWH(((int)time_one_digit % 10) * TIME_NUM_WIDTH, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
		);

		DX9::SpriteBatch->DrawSimple(
			time_number.Get(),
			SimpleMath::Vector3(TWO_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
			RectWH(((int)time_one_digit / 10) * TIME_NUM_WIDTH, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
		);
	}
}