#include "MyClass/DialogueManager/DialogueManager.h"

void DialogueManager::LoadAssets() {
	dialogue_1 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/dialogue_1.png");
	dialogue_2 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/dialogue_2.png");
	dialogue_3 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/dialogue_3.png");
	dialogue_4 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/dialogue_4.png");
	dialogue_5 = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Dialogue/dialogue_5.png");
}

void DialogueManager::AddCount(bool time_stop_flag) {
	if (time_stop_flag && DXTK->KeyEvent->pressed.B)
		dialogue_state++;
}

void DialogueManager::Render(int dialogue_count) {
	switch (dialogue_count)
	{
	case FIRST:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_1.Get(), SimpleMath::Vector3::Zero);
		else
			DX9::SpriteBatch->DrawSimple(dialogue_2.Get(), SimpleMath::Vector3::Zero);

		break;

	case SECOND:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_3.Get(), SimpleMath::Vector3::Zero);
		else
			DX9::SpriteBatch->DrawSimple(dialogue_4.Get(), SimpleMath::Vector3::Zero);
		break;

	case THIRD:
		if (dialogue_state == 0)
			DX9::SpriteBatch->DrawSimple(dialogue_5.Get(), SimpleMath::Vector3::Zero);
		break;

	default:
		break;
	}
}