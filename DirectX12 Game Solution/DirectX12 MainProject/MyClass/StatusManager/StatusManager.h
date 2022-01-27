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

	//攻撃ヒットコンボ
	void AddHitCombo();	//コンボ増加
	void AddHitComboTime();//コンボ時間増加
	void ResetHitCombo();	//コンボ数リセット
	int GetHitCombo() { return combo; }
	float GetHitComboTime() { return combo_time; }	//撃破コンボ継続時間
	bool GetComboFlag() { return combo_flag; }	//コンボフラグ

	//アニメーション
	void ResetaAnimeFlag() { anime_flag = false; }	//アニメフラグのリセット
	bool GetAnimeFlag() { return anime_flag; }	//アニメーション再生フラグ

	//スコア
	void SetAddScore(float score_size);	//スコアの値を入力
	float GetAddScore() { return add_score_size; }
	float GetScoreGauge() { return score * SCORE_GAUGE_DIVIDE; }	//ゲージ描画時呼び出し
	float GetScore() { return now_score; }	//現在のスコア
	float SetRemainEnemy(int remain_enemy) { enemy_num = remain_enemy; return 0; }
	bool GetGoodFlag() { return good_flag; }	//スコアUI描画時使用


	//ウェーブ
	void SetWave(int wave_num);	//ウェーブ数設定
	void WaveTimeLimit(const float deltaTime);	//ウェーブの時間
	void ResetWaveTime();	//ウェーブ時間を0にする
	int GetWave() { return wave; }	//現在のウェーブ
	int GetMaxWave() { return MAX_WAVE; }	//ウェーブの最大数
	float GetTime() { return wave_time; } //時間の取得
	float GetOnceExec() { return once_exec_time; }
	bool GetWaveFlag() { return wave_change_flag; }	//ウェーブ切り替えフラグ

private:
	void ComboTime(const float deltaTime);	//コンボ時間計る

	void ComboScore();	//コンボ数に応じてスコア加算
	void CalcScore(const float deltaTime);	//スコア計算
	void ScoreUp(const float deltaTime);	//アップ
	void ScoreDown(const float deltaTime);	//ダウン


	//攻撃ヒットコンボ
	int	  combo;	//コンボ数
	float combo_time;	//コンボ継続時間
	bool  combo_flag;	//true:コンボ継続可能 false:継続不可
	bool combo_miss_flag;

	const float COMBO_TIME_NUM = 7.0f;	//コンボの時間
	//アニメーション
	bool anime_flag;	//true:アニメーション再生 false:停止

	//スコア
	float score;
	float now_score;    //現在のスコア
	float add_score_size;
	float enemy_num;
	bool plus_score_flag;	//true:スコアアップ false:スコアダウン
	bool good_flag;

	const float SCORE_START_VALUE = 100.0f;	//初期値設定
	const float SCORE_MAX_VALUE = 1000.0f;	//スコアの最大値
	const float SCORE_UPDN_SPEED = 300.0f;	//スコア増減スピード
	const float SCORE_GAUGE_DIVIDE = 0.339f;	//スコアゲージ1000分の1の数(描画時使用)


	//ウェーブ
	int wave;	//現在のウェーブ
	float wave_time;	//ウェーブの制限時間
	float once_exec_time;
	bool wave_change_flag;	//true:ウェーブ切り替え可能 false:切り替え不可

	const int MAX_WAVE = 9;	//ウェーブの最大数
	const float WAVE_TIME_LIMIT_ONE = 30.0f;	//1ウェーブ目の制限時間
	const float WAVE_TIME_LIMIT_TWO = 40.0f;
	const float TUTORIAL_TIME = 99.0f;
};