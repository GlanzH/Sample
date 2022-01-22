
#include "Timer.h"
#include "MyClass/StatusManager/StatusManager.h"

bool Timer::Initialize() {
	font = DX9::SpriteFont::CreateFromFontName(DXTK->Device9,L"Ÿà–¾’©",40);
	return true;
}

int Timer::Update(const float deltaTime) {
	StatusManager::Instance().WaveTimeLimit(deltaTime);
	return 0;
}

void Timer::Render() {
	DX9::SpriteBatch->DrawString(font.Get(),
		SimpleMath::Vector2(1170.0f, 45.0f),
		DX9::Colors::White,
		L"%d", StatusManager::Instance().GetTime()
	);
}