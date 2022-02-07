#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "cppcoro/generator.h"
#include "MyClass/StatusManager/StatusManager.h"

using namespace DirectX;

class RankJudgeManager {
public:
	RankJudgeManager() {};
	~RankJudgeManager() {};

	void Initialize();
	void LoadAseet();
	void Update(const float deltaTime);
	void Render();



	void JudgeRnak();

	bool SceneChange() { return scene_flag; }
	
private:

	DX9::SPRITEFONT font;

	//�����N
	DX9::SPRITE rank[6];
	float rank_hight;
	int rank_width;
	float rank_alpha;
	int now_rank;
	int score;	//�����N�t���Ɏg�p

	enum RANK {
		E, D, C, B, A, S
	};

	//�X�R�A
	DX9::SPRITE score_empty;
	DX9::SPRITE score_max;
	float score_width;
	float score_alpha;

	const int SCORE_MAX_HIGHT = 96;
	const int SCORE_MIN_WIDTH = 81;
	const float SCORE_EMPTY_POS_Z = 0.0f;
	const float SCORE_MAX_POS_Z = -1.0f;

	//���U���g�^�C�g��
	DX9::SPRITE result_title;
	float title_alpha;
	float title_anim_frame;
	float title_hight;

	const int TITLE_WIDTH = 550;
	const int TITLE_MIN_HIGHT = 100;

	//���U���g��
	DX9::SPRITE result_shadow;
	float shadow_alpha;

	//����
	int money;
	int digit_state;
	int one_digit;
	int two_digit;
	int three_digit;
	int four_digit;

	float money_alpha;
	float yen_icon_alpha;

	SimpleMath::Vector2 money_pos;
	SimpleMath::Vector2 yen_icon_pos;

	enum DIGIT_STATE
	{
		ONE_DIGIT,
		TWO_DIGIT,
		THREE_DIGIT,
		FOUR_DIGIT
	};
	int digit_pos;
	const int YEN_ICON_WIDTH = 30;
	const int YEN_ICON_HIGHT = 51;
	const int YEN_NUM_WIDTH = 40;
	const int YEN_NUM_HIGHT = 70;
	const float MONEY_START_POS_X = 580.0f;
	const float YEN_ICON_START_POS_X = MONEY_START_POS_X - 70.0f;
	//const float THREE_DIGIT_POS_X = MONEY_START_POS_X - 80.0f;
	//const float FOUR_DIGIT_POS_X  = MONEY_START_POS_X - 120.0f;
	const float YEN_NUM_POS_Y = 0.0f;

	//���X�^�[�g
	DX9::SPRITE restart;
	float restart_hight;

	const int RESTART_WIDTH = 400;
	const int RESTART_MIN_HIGHT = 40;

	const int SPRITE_HIGHT = 720;	//�摜�̍ő�\������
	const int SPRITE_WIDTH = 1280;	//�摜�̍ő�\����

	const float COLOR_MAX = 255.0f;	//RGBA�ő�l
	bool scene_flag;	//�V�[���؂�ւ��\�t���O

	//����
	float time_delta;
	float stop_time;
	const float ALPHA_SPEED		  = 700.0f;//�A���t�@�l�����X�s�[�h
	const float SPRITE_MOVE_SPEED = 100.0f;//�摜�̈ړ��X�s�[�h

	// �R���[�`���̃v���g�^�C�v�錾
	//���U���g���o
	cppcoro::generator<int> ReleaseRank();
	cppcoro::generator<int>                  co_result;
	cppcoro::detail::generator_iterator<int> co_result_it;
};