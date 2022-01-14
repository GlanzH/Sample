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

	//敵撃破コンボ
	void AddKillCombo();	//コンボ増加
	void ResetKillCombo();	//コンボ数リセット
	void KillComboTime(const float deltaTime);	//コンボ時間計る
	bool GetKillFlag() { return kill_combo_flag; }	//コンボフラグの返し

	//オーディエンス
	void BonusScore();	//
	void AddAudience (float add_size	   );	//値を取得
	void CalcAudience(const float deltaTime);	//オーディエンス計算
	void UpAudience	 (const float deltaTime);	//アップ
	void DownAudience(const float deltaTime);	//ダウン
	float ReturnAudience() { return audience * AUDIENCE_GAUGE_DIVIDE; }	//ゲージ描画時呼び出し
	float ReturnScore() { return audience; }	//スコア判定時使用

	//ソード(必殺技ゲージ)
	void HeartCount();	//敵撃破時呼び出し
	void HeartReset();	//必殺技発動時呼び出し
	float ReturnHeart() { return heart; }	//必殺技使用時呼び出し
	float ReturnRenderHeart() { return heart * HEART_GAUGE_DIVIDE; }//ゲージ描画時呼び出し

	//ウェーブ
	void SetWave(int wave_num);//ウェーブ数設定
	void WaveTimeLimit(const float deltaTime);//ウェーブの時間
	int GetWave() { return wave; }//ウェーブ数返し
	bool GetWaveFlag() { return wave_change_flag; }//ウェーブ切り替えフラグ返し

private:
	//敵撃破コンボ
	int kill_combo;//コンボ数
	float kill_combo_time;//コンボ継続時間
	bool kill_combo_flag;//true:コンボ継続可能 false:継続不可

	const float WAVE_ONE_TIME_LIMIT = 30.0f;//1ウェーブ目の制限時間

	//オーディエンス
	float audience;
	float now_audience;    //現在のオーディエンス数
	bool plus_audience_flag;


	const float AUDIENCE_START_VALUE  =  100.0f;	//初期値設定
	const float AUDIENCE_MAX_VALUE	  = 1000.0f;	//スコアの最大値
	const float AUIDENCE_DN_SPEED	  =  300.0f;	//オーディエンス減スピード
	const float AUDIENCE_GAUGE_DIVIDE =  0.334f;	//人ゲージ1000分の1の数(描画時使用)

	//剣ゲージ(必殺技ゲージ)
	float heart;
	const float HEART_MAX = 20.0f;
	const float HEART_GAUGE_DIVIDE = 4.45f;

	//ウェーブ
	int wave;	//現在のウェーブ
	float wave_time;	//ウェーブの制限時間
	bool wave_change_flag;	//true:ウェーブ切り替え可能 false:切り替え不可
};