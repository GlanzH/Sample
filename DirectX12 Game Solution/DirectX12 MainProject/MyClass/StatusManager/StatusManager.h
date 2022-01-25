#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};


	void Initialize();
	void Update(const float deltaTime);


	static StatusManager& Instance() {
		static StatusManager instance;
		return instance;
	}

	//�G���j�R���{
	void AddKillCombo();	//�R���{����
	void AddKillComboTime();//�R���{���ԑ���
	void ResetKillCombo();	//�R���{�����Z�b�g
	float GetKillComboTime() { return kill_combo_time; }	//���j�R���{�p������
	bool GetKillFlag() { return kill_combo_flag; }	//�R���{�t���O

	//�A�j���[�V����
	void ResetaAnimeFlag() { anime_flag = false; }	//�A�j���t���O�̃��Z�b�g
	bool GetAnimeFlag() { return anime_flag; }	//�A�j���[�V�����Đ��t���O

	//�X�R�A
	void SetAddScore(float score_size);	//�X�R�A�̒l�����
	float GetAddScore() { return add_score_size; }
	float GetScoreGauge() { return score * SCORE_GAUGE_DIVIDE; }	//�Q�[�W�`�掞�Ăяo��
	float GetScore() { return now_score; }	//���݂̃X�R�A
	float SetRemainEnemy(int remain_enemy) { enemy_num = remain_enemy; return 0; }
	bool GetGoodFlag() { return good_flag; }	//�X�R�AUI�`�掞�g�p


	//�E�F�[�u
	void SetWave(int wave_num);	//�E�F�[�u���ݒ�
	int  GetWave() { return wave; }	//���݂̃E�F�[�u
	bool GetWaveFlag() { return wave_change_flag; }	//�E�F�[�u�؂�ւ��t���O

	void WaveTimeLimit(const float deltaTime);	//�E�F�[�u�̎���
	void ResetWaveTime();	//�E�F�[�u���Ԃ�0�ɂ���
	float GetTime() { return wave_time; } //���Ԃ̎擾

private:
	void KillComboTime(const float deltaTime);	//�R���{���Ԍv��

	void ComboScore();	//
	void CalcScore(const float deltaTime);	//�X�R�A�v�Z
	void ScoreUp(const float deltaTime);	//�A�b�v
	void ScoreDown(const float deltaTime);	//�_�E��


	//�G���j�R���{
	int	  kill_combo;	//�R���{��
	float kill_combo_time;	//�R���{�p������
	bool  kill_combo_flag;	//true:�R���{�p���\ false:�p���s��

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
	const float SCORE_GAUGE_DIVIDE = 0.422f;	//�X�R�A�Q�[�W1000����1�̐�(�`�掞�g�p)


	//�E�F�[�u
	int wave;	//���݂̃E�F�[�u
	float wave_time;	//�E�F�[�u�̐�������
	bool wave_change_flag;	//true:�E�F�[�u�؂�ւ��\ false:�؂�ւ��s��

	const float WAVE_TIME_LIMIT_ONE = 30.0f;	//1�E�F�[�u�ڂ̐�������
};