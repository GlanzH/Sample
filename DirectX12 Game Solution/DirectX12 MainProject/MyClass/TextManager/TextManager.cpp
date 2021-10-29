#include "Base/pch.h"
#include "Base/dxtk.h"
#include "TextManager.h"

bool TextManager::Initialize() {
	font = DX9::SpriteFont::CreateFromFontName(DXTK->Device9, L"�l�r �S�V�b�N", 22);

	write = 0.0f;

	writeFlag  = false;
	changeFlag = false;
	
	read = 0.0f;

	timedelta = 0.0f;

	enemy_death_count = 0;
	co_routine = CharaMove();        // �R���[�`���̐���
	co_routine_it = co_routine.begin(); // �R���[�`���̎��s�J�n

	return true;
}

void TextManager::LoadText() {
	FILE* fp;

	if (fopen_s(&fp, "Text.csv", "r,ccs=UTF-8") != 0) {
		assert(!"Text.csv���Ђ炯�܂���");
		throw std::exception();
	}

	wchar_t read_line[256];

	for (int i = 0; i < TEXT_MAX; ++i) {
		fgetws(read_line, 255, fp);
		const int LEN = lstrlenW(read_line);
		if (LEN <= 1)
			continue;

		read_line[LEN - 1] = '\0';
		text[i] = read_line;

		//���s��ݒ肷��
		//for (int j = 0; j < text[i].length(); ++j) {
		//	if (text[i].at(j) == L'@')
		//		text[i].at(j) = L'\n';
		//}
	}
	fclose(fp);	//�t�@�C�������
}

void TextManager::Update(const float deltaTime) {
	timedelta = deltaTime;

	enemy_death_count = enemy.GetDeathEnemyCount();

	//co_rutine�̍Ōザ��Ȃ����co_routine_it(�R���[�`���̃C�e���[�^)���P�i�߂�
	if (co_routine_it != co_routine.end())
		co_routine_it++;

	return;
}

void TextManager::Render() {

}

void TextManager::Render2D() {
	Rect dest = RectWH(0, 0, 1000, 1000);
	DX9::SpriteBatch->DrawText(font.Get(), read.c_str(), (int)write, dest, DX9::Colors::Black);

	//dest = RectWH(426, 0, 1000, 1000);
	//DX9::SpriteBatch->DrawText(font.Get(), text[2].c_str(), (int)write[2], dest, DX9::Colors::Black);

	//dest = RectWH(116, 0, 1000, 1000);
	//DX9::SpriteBatch->DrawText(font.Get(), text[3].c_str(), (int)write[3], dest, DX9::Colors::Red);

	//dest = RectWH(116, 0, 1000, 1000);
	//DX9::SpriteBatch->DrawText(font.Get(), text[4].c_str(), (int)write[4], dest, DX9::Colors::Blue);

}

// �R���[�`���̃v���g�^�C�v�錾
cppcoro::generator<int> TextManager::CharaMove() {
	co_yield 0;
	if (enemy_death_count > 0) {	//�G��|�����ꍇ

		write = 0.0f;
		read = text[0] + text[2];

		while (write < read.length()) {
			write += WRITE_SPEED * timedelta;
			co_yield 1;
		}
		write = read.length();
	}
	else {		//�G��|���Ȃ������ꍇ
		co_yield 0;
		write = 0.0f;
		read = text[0] + text[1];

		while (write < read.length()) {
			write += WRITE_SPEED * timedelta;
			co_yield 1;
		}
		write = read.length();
	}
	co_return;
}