#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};


	void Initialize();
	int Update(const float deltaTime);




	static StatusManager& Instance(){
		static StatusManager instance;
		return instance;
	}

	//�G���j�R���{
	void AddKillCombo();	//�R���{����
	void ResetKillCombo();	//�R���{�����Z�b�g
	void KillComboTime(const float deltaTime);	//�R���{���Ԍv��
	bool GetKillFlag() { return kill_combo_flag; }	//�R���{�t���O�̕Ԃ�

	//�I�[�f�B�G���X
	void BonusScore();	//
	void AddAudience (float add_size	   );	//�l���擾
	void CalcAudience(const float deltaTime);	//�I�[�f�B�G���X�v�Z
	void UpAudience	 (const float deltaTime);	//�A�b�v
	void DownAudience(const float deltaTime);	//�_�E��
	float ReturnAudience() { return audience * AUDIENCE_GAUGE_DIVIDE; }	//�Q�[�W�`�掞�Ăяo��
	float ReturnScore() { return audience; }	//�X�R�A���莞�g�p

	//�\�[�h(�K�E�Z�Q�[�W)
	void HeartCount();	//�G���j���Ăяo��
	void HeartReset();	//�K�E�Z�������Ăяo��
	float ReturnHeart() { return heart; }	//�K�E�Z�g�p���Ăяo��
	float ReturnRenderHeart() { return heart * HEART_GAUGE_DIVIDE; }//�Q�[�W�`�掞�Ăяo��

	//�E�F�[�u
	void SetWave(int wave_num);//�E�F�[�u���ݒ�
	void WaveTimeLimit(const float deltaTime);//�E�F�[�u�̎���
	int GetWave() { return wave; }//�E�F�[�u���Ԃ�
	bool GetWaveFlag() { return wave_change_flag; }//�E�F�[�u�؂�ւ��t���O�Ԃ�

private:
	//�G���j�R���{
	int kill_combo;//�R���{��
	float kill_combo_time;//�R���{�p������
	bool kill_combo_flag;//true:�R���{�p���\ false:�p���s��

	const float WAVE_ONE_TIME_LIMIT = 30.0f;//1�E�F�[�u�ڂ̐�������

	//�I�[�f�B�G���X
	float audience;
	float now_audience;    //���݂̃I�[�f�B�G���X��
	bool plus_audience_flag;


	const float AUDIENCE_START_VALUE  =  100.0f;	//�����l�ݒ�
	const float AUDIENCE_MAX_VALUE	  = 1000.0f;	//�X�R�A�̍ő�l
	const float AUIDENCE_DN_SPEED	  =  300.0f;	//�I�[�f�B�G���X���X�s�[�h
	const float AUDIENCE_GAUGE_DIVIDE =  0.334f;	//�l�Q�[�W1000����1�̐�(�`�掞�g�p)

	//���Q�[�W(�K�E�Z�Q�[�W)
	float heart;
	const float HEART_MAX = 20.0f;
	const float HEART_GAUGE_DIVIDE = 4.45f;

	//�E�F�[�u
	int wave;	//���݂̃E�F�[�u
	float wave_time;	//�E�F�[�u�̐�������
	bool wave_change_flag;	//true:�E�F�[�u�؂�ւ��\ false:�؂�ւ��s��
};