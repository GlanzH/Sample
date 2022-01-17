#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};


	void Initialize();
	void AddCombo(const float deltaTime);
	int Update(const float deltaTime);




	static StatusManager& Instance(){
		static StatusManager instance;
		return instance;
	}

	//�v���C���[�̃R���{
	int GetAtkCombo() { return atk_combo; }	//�U���R���{���g�p
	float GetKillComboTime(const float deltaTime);	//�ƂǂߍU���̃R���{�����\����

	//�I�[�f�B�G���X
	void AddAudience (float add_size	   );	//�l���擾
	void CalcAudience(const float deltaTime);	//�I�[�f�B�G���X�v�Z
	void UpAudience	 (const float deltaTime);	//�A�b�v
	void DownAudience(const float deltaTime);	//�_�E��
	float ReturnAudience() { return audience * AUDIENCE_GAUGE_DIVIDE; }	//�Q�[�W�`�掞�Ăяo��
	float ReturnScore() { return audience; }	//�X�R�A���莞�g�p
	void BonusScore(int kill_combo);

	//�n�[�g(�K�E�Z�Q�[�W)
	void HeartCount();	//�G���j���Ăяo��
	void HeartReset();	//�K�E�Z�������Ăяo��
	float ReturnHeart() { return heart; }	//�K�E�Z�g�p���Ăяo��
	float ReturnRenderHeart() { return heart * HEART_GAUGE_DIVIDE; }//�Q�[�W�`�掞�Ăяo��

private:
	//�v���C���[�̍U���R���{
	int atk_combo;
	int atk_combo_count;
	float atk_combo_time;
	float kill_combo_time;
	bool atk_combo_flag;

	const int ATK_COMBO_MAX = 4;
	const float ATK_COMBO_TIME_MAX[3]{ 0.617f,0.517f,0.583f };
	const float KILL_COMBO_TIME_MAX = 3.0f;

	//�I�[�f�B�G���X
	float audience;
	float now_audience;    //���݂̃I�[�f�B�G���X��
	bool plus_audience_flag;


	const float AUDIENCE_START_VALUE  =  100.0f;	//�����l�ݒ�
	const float AUDIENCE_MAX_VALUE	  = 1000.0f;	//�X�R�A�̍ő�l
	const float AUIDENCE_DN_SPEED	  =  300.0f;	//�I�[�f�B�G���X���X�s�[�h
	const float AUDIENCE_GAUGE_DIVIDE =  0.334f;	//�l�Q�[�W1000����1�̐�(�`�掞�g�p)


	//�n�[�g
	float heart;
	const float HEART_MAX = 20.0f;
	const float HEART_GAUGE_DIVIDE = 4.45f;
};