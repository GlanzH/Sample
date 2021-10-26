#include "Base/pch.h"
#include "Base/dxtk.h"
#include "TextManager.h"

bool TextManager::Initialize() {
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	write = 0.0f;
	writeFlag = false;
	return true;
}

void TextManager::LoadText() {
	FILE* fp;

	if (fopen_s(&fp, "Text.csv", "r,ccs=UTF-8") != 0) {
		assert(!"Text.csvがひらけません");
		throw std::exception();
	}

	wchar_t read_line[256];

	for (int i = 0; i < 1; ++i) {
		fgetws(read_line, 255, fp);
		text[i] = read_line;

		//改行を設定する
		for (int j = 0; j < text[i].length(); ++j) {
			if (text[i].at(j) == L'@')
				text[i].at(j) = L'\n';
		}
	}
	fclose(fp);	//ファイルを閉じる
}

void TextManager::Update(const float deltaTime) {
	if (DXTK->KeyEvent->pressed.Enter)
		writeFlag = true;

	if (writeFlag == true)
		write += 50.0f * deltaTime;
		//write = std::min(write + 10.0f * deltaTime, text[0].length());
	
	if (write > text[0].length())
		write = text[0].length();
	
	return;
}

void TextManager::Render() {

}

void TextManager::Render2D() {
	Rect dest = RectWH(0, 0, 1000, 1000);
	DX9::SpriteBatch->DrawText(font.Get(), text[0].c_str(), (int)write, dest, DX9::Colors::Black);

}