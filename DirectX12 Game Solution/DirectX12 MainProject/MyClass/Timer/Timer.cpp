#include "Timer.h"
#include "MyClass/StatusManager/StatusManager.h"

Timer::Timer() {

}

Timer::~Timer() {

}

bool Timer::Initialize() {
	font = DX9::SpriteFont::CreateFromFontName(DXTK->Device9,L"Ÿà–¾’©",40);
	stage_num = init_stage_num;
	return true;
}

int Timer::Update(const float deltaTime) {
	StatusManager::Instance().WaveTimeLimit(deltaTime);

	if (StatusManager::Instance().GetWave() < 3 && StatusManager::Instance().GetTime() == 0.0f) {

		if (stop_frame < max_stop) {
			stop_frame += deltaTime;
		}
		else {
			StatusManager::Instance().SetWave(stage_num++);
			stop_frame = 0.0f; 
		}
	}

	return 0;
}

void Timer::Render() {
	if (StatusManager::Instance().GetWave() > 0) {
		DX9::SpriteBatch->DrawString(font.Get(),
			SimpleMath::Vector2(1170.0f, 45.0f),
			DX9::Colors::White,
			L"%d", StatusManager::Instance().GetTime()
		);
	}
}