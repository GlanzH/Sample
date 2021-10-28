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
	std::basic_string<wchar_t>text[5];	//•¶Í‚ğ“ü‚ê‚é•Ï”
	DX9::SPRITEFONT font;
	DX9::SPRITEFONT red_font;
	DX9::SPRITEFONT blue_font;

	float write[5];
	std::basic_string<wchar_t>read;	//•¶Í‚ğ“ü‚ê‚é•Ï”
	bool writeFlag;
	bool changeFlag;

	const float WRITE_SPEED = 10.0f;
};