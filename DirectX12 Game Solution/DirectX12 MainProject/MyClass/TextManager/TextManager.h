#pragma once
#include <string>
#include"MyClass/EnemyManager/EnemyManager.h"
#include "cppcoro/generator.h"

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
	enum { TEXT_MAX = 3 };

	std::basic_string<wchar_t>text[TEXT_MAX];	//文章を入れる変数
	DX9::SPRITEFONT font;
	DX9::SPRITEFONT red_font;
	DX9::SPRITEFONT blue_font;

	float write;
	std::basic_string<wchar_t>read;	//文章を入れる変数
	bool writeFlag;
	bool changeFlag;

	const float WRITE_SPEED = 10.0f;

	EnemyManager enemy;
	int enemy_death_count;

	float timedelta;
	// コルーチンのプロトタイプ宣言
	cppcoro::generator<int> CharaMove();
	cppcoro::generator<int>                  co_routine;
	cppcoro::detail::generator_iterator<int> co_routine_it;
};