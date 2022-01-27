#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};


	void Initialize();
	void Update(const float deltaTime, int remain_enemy);


	static StatusManager& Instance() {
		static StatusManager instance;
		return instance;
	}

	//�U���q�b�g�R���{
	void AddHitCombo();	//�R���{����
	void AddHitComboTime();//�R���{���ԑ���
	void ResetHitCombo();	//�R���{�����Z�b�g
	int GetHitCombo() { return combo; }
	float GetHitComboTime() { return combo_time; }	//���j�R���{�p������
	bool GetComboFlag() { return combo_flag; }	//�R���{�t���O

	//�A�j���[�V����
	void ResetaAnimeFlag() { anime_flag = false; }	//�A�j���t���O�̃��Z�b�g
	bool GetAnimeFlag() { return anime_flag; }	//�A�j���[�V�����Đ��t���O

	//�X�R�A
	void SetAddScore(float score_size);	//�X�R�A�̒l�����
	float GetAddScore() { return add_score_size; }
	float GetScoreGauge() { return score * SCORE_GAUGE_DIVIDE; }	//�Q�[�W�`�掞�Ăяo��
	float GetScore() { return now_score; }	//���݂̃X�R�A
	bool GetGoodFlag() { return good_flag; }	//�X�R�AUI�`�掞�g�p


	//�E�F�[�u
	void SetWave(int wave_num);	//�E�F�[�u���ݒ�
	void WaveTimeLimit(const float deltaTime);	//�E�F�[�u�̎���
	void ResetWaveTime();	//�E�F�[�u���Ԃ�0�ɂ���
	int GetWave() { return wave; }	//���݂̃E�F�[�u
	int GetMaxWave() { return MAX_WAVE; }	//�E�F�[�u�̍ő吔
	float GetTime() { return wave_time; } //���Ԃ̎擾
	float GetOnceExec() { return once_exec_time; }
	bool GetWaveFlag() { return wave_change_flag; }	//�E�F�[�u�؂�ւ��t���O

private:
	void ComboTime(const float deltaTime);	//�R���{���Ԍv��

	void ComboScore();	//�R���{���ɉ����ăX�R�A���Z
	void CalcScore(const float deltaTime);	//�X�R�A�v�Z
	void ScoreUp(const float deltaTime);	//�A�b�v
	void ScoreDown(const float deltaTime);	//�_�E��


	//�U���q�b�g�R���{
	int	  combo;	//�R���{��
	float combo_time;	//�R���{�p������
	bool  combo_flag;	//true:�R���{�p���\ false:�p���s��
	bool combo_miss_flag;

	const float COMBO_TIME_NUM = 7.0f;	//�R���{�̎���
	//�A�j���[�V����
	bool anime_flag;	//true:�A�j���[�V�����Đ� false:��~

	//�X�R�A
	float score;
	float now_score;    //���݂̃X�R�A
	float add_score_size;
	float enemy_num;
	bool plus_score_flag;	//true:�X�R�A�A�b�v false:�X�R�A�_�E��
	bool good_flag;

	const float SCORE_START_VALUE = 100.0f;	//�����l�ݒ�
	const float SCORE_MAX_VALUE = 1000.0f;	//�X�R�A�̍ő�l
	const float SCORE_UPDN_SPEED = 300.0f;	//�X�R�A�����X�s�[�h
	const float SCORE_GAUGE_DIVIDE = 0.339f;	//�X�R�A�Q�[�W1000����1�̐�(�`�掞�g�p)


	//�E�F�[�u
	int wave;	//���݂̃E�F�[�u
	float wave_time;	//�E�F�[�u�̐�������
	float once_exec_time;
	bool wave_change_flag;	//true:�E�F�[�u�؂�ւ��\ false:�؂�ւ��s��

	const int MAX_WAVE = 9;	//�E�F�[�u�̍ő吔
	const float WAVE_TIME_LIMIT_ONE = 30.0f;	//1�E�F�[�u�ڂ̐�������
	const float WAVE_TIME_LIMIT_TWO = 40.0f;
	const float TUTORIAL_TIME = 99.0f;
};