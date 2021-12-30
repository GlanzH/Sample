#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};


	void Initialize();
	void AddCombo(const float deltaTime);
	int Update(const float deltaTime);

	int GetCombo() { return combo; }

	float GetTime() { return combo_time; }


	static StatusManager& Instance(){
		static StatusManager instance;
		return instance;
	}

	//�I�[�f�B�G���X
	void AddAudience (float add_size	   );	//�l���擾
	void CalcAudience(const float deltaTime);	//�I�[�f�B�G���X�v�Z
	void UpAudience	 (const float deltaTime);	//�A�b�v
	void DownAudience(const float deltaTime);	//�_�E��
	float ReturnAudience() { return audience * AUDIENCE_GAUGE_DIVIDE; }	//�Q�[�W�`�掞�Ăяo��
	float ReturnScore() { return audience; }	//�X�R�A���莞�g�p

	//�n�[�g(�K�E�Z�Q�[�W)
	void HeartCount();	//�G���j���Ăяo��
	void HeartReset();	//�K�E�Z�������Ăяo��
	float ReturnHeart() { return heart; }	//�K�E�Z�g�p���Ăяo��
	float ReturnRenderHeart() { return heart * HEART_GAUGE_DIVIDE; }//�Q�[�W�`�掞�Ăяo��

private:
	//�R���{
	float combo_time;
	const float COMBO_TIME_MAX[3]{ 0.617f,0.517f,0.583f };
	int combo;
	const int COMBO_MAX = 4;

	bool combo_flag = false;
	int  combo_count = 0;


	//�I�[�f�B�G���X
	float audience;
	float now_audience;    //���݂̃I�[�f�B�G���X��
	bool plus_audience_flag;

	const float AUDIENCE_START_VALUE = 100.0f;    //�����l�ݒ�
	const float AUDIENCE_MAX_VALUE = 1000.0f;	//�X�R�A�̍ő�l
	const float AUIDENCE_DN_SPEED = 300.0f;    //�I�[�f�B�G���X���X�s�[�h
	const float AUDIENCE_GAUGE_DIVIDE = 0.306f;    //�l�Q�[�W1000����1�̐�(�`�掞�g�p)


	//�n�[�g
	float heart;
	const float HEART_MAX = 20.0f;
	const float HEART_GAUGE_DIVIDE = 4.45f;
};