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

	//オーディエンス
	void AddAudience (float add_size	   );	//値を取得
	void DownAudience(const float deltaTime);	//ダウン
	float ReturnAudience() { return audience * AUDIENCE_GAUGE_DIVIDE; }	//ゲージ描画時呼び出し
	float ReturnScore() { return audience; }	//スコア判定時使用

	//ハート(必殺技ゲージ)
	void HeartCount();	//敵撃破時呼び出し
	void HeartReset();	//必殺技発動時呼び出し
	float ReturnHeart() { return heart; }	//必殺技使用時呼び出し
	float ReturnRenderHeart() { return heart * HEART_GAUGE_DIVIDE; }//ゲージ描画時呼び出し

private:
	//コンボ
	float combo_time;
	const float COMBO_TIME_MAX[3]{ 0.617f,0.517f,0.583f };
	int combo;
	const int COMBO_MAX = 4;

	bool combo_flag = false;
	int  combo_count = 0;


	//オーディエンス
	float audience;
	float now_audience;    //現在のオーディエンス数

	const float AUDIENCE_START_VALUE = 100.0f;    //初期値設定
	const float AUIDENCE_DN_SPEED = 20.0f;    //オーディエンス減スピード
	const float AUDIENCE_GAUGE_DIVIDE = 3.06f;    //人ゲージ100分の1の数(描画時使用)

	//ハート
	float heart;
	const float HEART_MAX = 20.0f;
	const float HEART_GAUGE_DIVIDE = 4.45f;
};