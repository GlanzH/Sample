#include "MyClass/DialogueManager/DialogueManager.h"

void DialogueManager::LoadAssets() {
	dialogue_1 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage1/dialogue_01_02.png");
	dialogue_2 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage1/dialogue_01_04.png");
	dialogue_3 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage1/dialogue_01_05.png");
	dialogue_4 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage1/dialogue_01_06.png");
	dialogue_5 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage1/dialogue_01_07.png");
	dialogue_6 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage1/dialogue_01_08.png");

	dialogue_7 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage2/dialogue_02_02.png");
	dialogue_8 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage2/dialogue_02_03.png");
	dialogue_9 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage2/dialogue_02_04.png");
	dialogue_10 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage2/dialogue_02_05.png");
	dialogue_11 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage2/dialogue_02_06.png");
	dialogue_12 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage2/dialogue_02_07.png");

	dialogue_13 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage3/dialogue_03_01.png");
	dialogue_14 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage3/dialogue_03_02.png");
	dialogue_15 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage3/dialogue_03_03.png");
	dialogue_16 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage3/dialogue_03_04.png");
	dialogue_17 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage3/dialogue_03_05.png");
	dialogue_18 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage3/dialogue_03_06.png");

	dialogue_19 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage4/dialogue_04_01.png");
	dialogue_20 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage4/dialogue_04_02.png");
	dialogue_21 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage4/dialogue_04_03.png");
	dialogue_22 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage4/dialogue_04_04.png");
	dialogue_23 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage4/dialogue_04_05.png");
	dialogue_24 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/Stage4/dialogue_04_06.png");
}

void DialogueManager::AddCount(bool time_stop_flag) {
	if (time_stop_flag && DXTK->KeyEvent->pressed.B ||
		time_stop_flag && DXTK->GamePadEvent[0].b == GamePad::ButtonStateTracker::PRESSED ||
		time_stop_flag && DXTK->GamePadEvent[0].a == GamePad::ButtonStateTracker::PRESSED
		)
		dialogue_state++;
}

//!ステージの始まりごとに描画させる画像
void DialogueManager::Render(int dialogue_count) {
	switch (dialogue_count)
	{
	case FIRST:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_1.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_2.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;

	case SECOND:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_3.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_4.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		break;

	case THIRD:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_5.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_6.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case FOUR:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_7.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_8.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case FIVE:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_9.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_10.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case SIX:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_11.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_12.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case SEVEN:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_13.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_14.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case EIGHT:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_15.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_16.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case NINE:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_17.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_18.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case TEN:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_19.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_20.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case ELEVEN:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_21.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_22.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	case TWELVE:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_23.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));
		else
			DX9::SpriteBatch->DrawSimple(dialogue_24.Get(), SimpleMath::Vector3(0.0f, 0.0f, -3.0f));

		break;
	}
}