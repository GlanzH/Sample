#include "Base/pch.h"
#include "Base/dxtk.h"
#include "TextManager.h"

bool TextManager::Initialize() {
	font = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"ＭＳ ゴシック", 22);
	for (int i = 0; i < 5; ++i)
		write[i] = 0.0f;

	writeFlag = false;
	changeFlag = false;
	
	read = 0.0f;

	return true;
}

void TextManager::LoadText() {
	FILE* fp;

	if (fopen_s(&fp, "Text.csv", "r,ccs=UTF-8") != 0) {
		assert(!"Text.csvがひらけません");
		throw std::exception();
	}

	wchar_t read_line[256];

	for (int i = 0; i < 5; ++i) {
		fgetws(read_line, 255, fp);
		const int LEN = lstrlenW(read_line);
		if (LEN <= 1)
			continue;

		read_line[LEN - 1] = '\0';
		text[i] = read_line;

		//改行を設定する
		//for (int j = 0; j < text[i].length(); ++j) {
		//	if (text[i].at(j) == L'@')
		//		text[i].at(j) = L'\n';
		//}
	}
	fclose(fp);	//ファイルを閉じる
}

void TextManager::Update(const float deltaTime) {
	if (DXTK->KeyEvent->pressed.Enter)
		writeFlag = true;
	
	
	read = text[0] + text[1] + text[3];

	if (writeFlag == true) {
		for (int i = 1; i < 2; ++i) {
			if(write[i] < read.length()) {
				write[i] += WRITE_SPEED * deltaTime;
			}

			//if (write > text[i].length())
			//	write = text[i].length();
		}
	
		if (DXTK->KeyEvent->pressed.Space) {
			write[1] = 3.0f;
			changeFlag = true;
			writeFlag = false;
		}
	}

	
	if (changeFlag == true) {
		read = text[0] + text[2] + text[3];
		write[1] += WRITE_SPEED * deltaTime;

		if (write[1] > read.length()) {
			write[1] = read.length();
		}
	}
	return;
}

void TextManager::Render() {

}

void TextManager::Render2D() {
	Rect dest = RectWH(0, 0, 1000, 1000);
	DX9::SpriteBatch->DrawText(font.Get(), read.c_str(), (int)write[1], dest, DX9::Colors::Black);

	//dest = RectWH(426, 0, 1000, 1000);
	//DX9::SpriteBatch->DrawText(font.Get(), text[2].c_str(), (int)write[2], dest, DX9::Colors::Black);

	//dest = RectWH(116, 0, 1000, 1000);
	//DX9::SpriteBatch->DrawText(font.Get(), text[3].c_str(), (int)write[3], dest, DX9::Colors::Red);

	//dest = RectWH(116, 0, 1000, 1000);
	//DX9::SpriteBatch->DrawText(font.Get(), text[4].c_str(), (int)write[4], dest, DX9::Colors::Blue);

}