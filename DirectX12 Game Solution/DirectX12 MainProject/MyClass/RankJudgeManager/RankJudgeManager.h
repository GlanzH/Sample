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

	float rank_alpha;
	int now_rank;
	float now_score;	//�����N�t���Ɏg�p

	enum RANK {
		E, D, C, B, A, S
	};

	//�t�H���g
	DX9::SPRITEFONT font;
	SimpleMath::Vector2 font_pos;
	const int font_size = 100;

	//�l��
	DX9::SPRITE	people_ui;
	SimpleMath::Vector3 people_pos;
	int people;

	//�ē�
	DX9::SPRITE director;
	SimpleMath::Vector3 director_pos;

	//�����o��
	DX9::SPRITE text_box;
	SimpleMath::Vector3 text_box_pos;
	float text_box_alpha;

	//�R�����g
	DX9::SPRITE text;
	SimpleMath::Vector3 text_pos;
	float text_alpha;

	const int SPRITE_HIGHT = 720;	//�摜�̍ő�\������
	const int SPRITE_WIDTH = 1280;	//�摜�̍ő�\����

	const float COLOR_MAX = 255.0f;	//RGBA�ő�l
	bool scene_flag;

	//����
	float time_delta;
	float stop_time;

	// �R���[�`���̃v���g�^�C�v�錾
	cppcoro::generator<int> ReleaseRank();
	cppcoro::generator<int>                  co_result;
	cppcoro::detail::generator_iterator<int> co_result_it;
};