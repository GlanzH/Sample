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


	void GetAudience();

	void JudgeRnak();

	bool SceneChange() { return scene_flag; }
	
private:
	//�����N
	DX9::SPRITE rank_s;
	DX9::SPRITE rank_a;
	DX9::SPRITE rank_b;
	DX9::SPRITE rank_c;
	DX9::SPRITE rank_d;
	DX9::SPRITE rank_e;
	SimpleMath::Vector3 rank_pos;
	const float RANK_START_POS_Y = -40.0f;

	float rank_alpha;
	int now_rank;
	float now_score;	//�����N�t���Ɏg�p

	enum RANK {
		E, D, C, B, A, S
	};

	//�e�����N�͈̔�
	const float E_RANK_MAX = 0.0f;
	const float D_RANK_MIN = 1.0f;
	const float D_RANK_MAX = 29.0f;
	const float C_RANK_MIN = 30.0f;
	const float C_RANK_MAX = 59.0f;
	const float B_RANK_MIN = 60.0f;
	const float B_RANK_MAX = 89.0f;
	const float A_RANK_MIN = 90.0f;
	const float A_RANK_MAX = 99.0f;
	const float S_RANK_MIN = 100.0f;

	//�t�H���g
	DX9::SPRITEFONT font;
	SimpleMath::Vector2 font_pos;
	const int font_size = 100;//�t�H���g�T�C�Y
	const float FONT_STSRT_POS_X = 680.0f;
	const float FONT_STSRT_POS_Y = 130.0f;
	const float TWO_DIGIT_POS	= 590.0f;//�ϋq�l��2���̍��W
	const float THREE_DIGIT_POS = 500.0f;//�ϋq�l��3���̍��W


	//�l��
	DX9::SPRITE	people_ui;
	SimpleMath::Vector3 people_pos;
	int people;
	const int multiple = 3;//�ϋq�l���̔{��

	//�ē�
	DX9::SPRITE director;
	SimpleMath::Vector3 director_pos;

	//�����o��
	DX9::SPRITE text_box;
	SimpleMath::Vector3 text_box_pos;
	float text_box_alpha;
	const float TEXTBOX_START_POS_X = -50.0f;

	//�e�L�X�g
	DX9::SPRITE text;
	SimpleMath::Vector3 text_pos;
	float text_alpha;

	const float TEXT_START_POS_Y = 40.0f;

	//EXIT
	DX9::SPRITE exit;
	SimpleMath::Vector3 exit_pos;
	float exit_alpha;


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
	cppcoro::generator<int> ReleaseRank();
	cppcoro::generator<int>                  co_result;
	cppcoro::detail::generator_iterator<int> co_result_it;
};