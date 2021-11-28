#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};

	void AddCombo(const float deltaTime);
	int Update(const float deltaTime);

	int GetCombo() { return combo; }

	float GetTime() { return combo_time; }


	static StatusManager&Instance(){
		static StatusManager instance;
		return instance;
	}

	//�{���e�[�W
	void  GetVoltage (float volt_size);	//�l���擾
	void  JudgeVolt  ();	//�A�b�vor�_�E������
	void  AddVoltage (const float deltaTime);	//�l�̒ǉ�
	void  UpVoltage	 (const float deltaTime);	//�A�b�v
	void  DownVoltage(const float deltaTime);	//�_�E��
	float ReturnVolt () { return voltage; }	//�Q�[�W�`�掞�Ăяo��

	//�p���B
	void ParryCount();	//�p���B�������Ăяo��
	void ParryReset();	//�K�E�Z�������Ăяo��
	float ReturnParry() { return parry; }	//�Q�[�W�`�掞�Ăяo��

private:
	//�R���{
	float combo_time = 0.0f;
	const float combo_time_max = 1.0f;//[3]{ 0.617f,0.517f,0.583f };
	int combo = 0;
	const int combo_max = 4;

	//�{���e�[�W
	float voltage  = 50.0f;		//�����l�ݒ�
	float now_volt = voltage;	//���݂̃{���e�[�W
	const float VOL_UPDN_SPEED = 100.0f; //�{���e�[�W�����X�s�[�h

	bool volt_add_flag = plus;	//�{���e�[�W�𑫂���������t���O
	enum {
		minus,	//����
		plus	//����
	};

	//�p���B
	float parry = 0.0f;

};