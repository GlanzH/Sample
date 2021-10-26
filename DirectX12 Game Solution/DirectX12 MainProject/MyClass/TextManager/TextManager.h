#pragma once

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
	std::basic_string<wchar_t>text[1];	//���͂�����ϐ�
	DX9::SPRITEFONT font;
	float write;
	bool writeFlag;

};