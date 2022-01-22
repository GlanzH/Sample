#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};


	void Initialize();
	void Update(const float deltaTime);


	static StatusManager& Instance(){
		static StatusManager instance;
		return instance;
	}

	//敵撃破コンボ
	void AddKillCombo();	//コンボ増加
	void ResetKillCombo();	//コンボ数リセット
	float GetKillComboTime() { return kill_combo_time; }	//撃破コンボ継続時間
	bool GetKillFlag() { return kill_combo_flag; }	//コンボフラグ
	
	//アニメーション
	void ResetaAnimeFlag() { anime_flag = false; }	//アニメフラグのリセット
	bool GetAnimeFlag() { return anime_flag; }	//アニメーション再生フラグ

	//スコア
	void SetAddScore(float score_size);	//スコアの値を入力
	float GetScoreGauge() { return score * SCORE_GAUGE_DIVIDE; }	//ゲージ描画時呼び出し
	float GetScore() { return now_score; }	//現在のスコア
	bool GetGoodFlag() { return good_flag; }	//スコアUI描画時使用


	//ウェーブ
	void SetWave(int wave_num);	//ウェーブ数設定
	int  GetWave() { return wave; }	//現在のウェーブ
	bool GetWaveFlag() { return wave_change_flag; }	//ウェーブ切り替えフラグ
	
private:
	void KillComboTime(const float deltaTime);	//コンボ時間計る

	void BonusScore();	//
	void CalcScore(const float deltaTime);	//スコア計算
	void ScoreUp(const float deltaTime);	//アップ
	void ScoreDown(const float deltaTime);	//ダウン

	void WaveTimeLimit(const float deltaTime);	//ウェーブの時間


	//敵撃破コンボ
	int	  kill_combo;	//コンボ数
	float kill_combo_time;	//コンボ継続時間
	bool  kill_combo_flag;	//true:コンボ継続可能 false:継続不可

	//アニメーション
	bool anime_flag;	//true:アニメーション再生 false:停止

	//スコア
	float score;
	float now_score;    //現在のスコア
	bool plus_score_flag;	//true:スコアアップ false:スコアダウン
	bool good_flag;

	const float SCORE_START_VALUE  = 100.0f;	//初期値設定
	const float SCORE_MAX_VALUE	   = 1000.0f;	//スコアの最大値
	const float SCORE_UPDN_SPEED   = 300.0f;	//スコア増減スピード
	const float SCORE_GAUGE_DIVIDE = 0.422f;	//スコアゲージ1000分の1の数(描画時使用)


	//ウェーブ
	int wave;	//現在のウェーブ
	float wave_time;	//ウェーブの制限時間
	bool wave_change_flag;	//true:ウェーブ切り替え可能 false:切り替え不可

	const float WAVE_TIME_LIMIT_ONE = 30.0f;	//1ウェーブ目の制限時間
};