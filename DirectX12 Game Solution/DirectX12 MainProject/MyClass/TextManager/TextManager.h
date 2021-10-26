#pragma once
#include <string>

class TextManager
{
public:
	TextManager() {};
	~TextManager() {};

	bool Initialize();
	void  Update(const float deltaTime);
	void LoadText();
	void Render();
	void Render2D();
private:
	std::basic_string<wchar_t>text[5];	//文章を入れる変数
	DX9::SPRITEFONT font;
	DX9::SPRITEFONT red_font;
	DX9::SPRITEFONT blue_font;

	float write[5];
	std::basic_string<wchar_t>read;	//文章を入れる変数
	bool writeFlag;
	bool changeFlag;

	const float WRITE_SPEED = 10.0f;
};