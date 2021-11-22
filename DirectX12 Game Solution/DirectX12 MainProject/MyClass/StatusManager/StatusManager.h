#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};

	void AddCombo(const float deltaTime);
	int Update(const float deltaTime);

	int GetCombo() { return combo; }

	static StatusManager&Instance(){
		static StatusManager instance;
		return instance;
	}

	//ボルテージ
	void  GetVoltage (float volt_size);	//値を取得
	void  JudgeVolt  ();	//アップorダウン判定
	void  AddVoltage (const float deltaTime);	//値の追加
	void  UpVoltage	 (const float deltaTime);	//アップ
	void  DownVoltage(const float deltaTime);	//ダウン
	float ReturnVolt () { return voltage; }	//ゲージ描画時呼び出し

	//パリィ
	void ParryCount();	//パリィ成功時呼び出し
	void ParryReset();	//必殺技発動時呼び出し
	float ReturnParry() { return parry; }	//ゲージ描画時呼び出し

private:
	//コンボ
	float combo_time = 0.0f;
	const float combo_time_max =  0.7f;
	int combo = 0;
	const int combo_max = 3;

	//ボルテージ
	float voltage  = 50.0f;		//初期値設定
	float now_volt = voltage;	//現在のボルテージ
	const float VOL_UPDN_SPEED = 100.0f; //ボルテージ増減スピード

	bool volt_add_flag = plus;	//ボルテージを足し引きするフラグ
	enum {
		minus,	//引く
		plus	//足す
	};

	//パリィ
	float parry = 0.0f;

};