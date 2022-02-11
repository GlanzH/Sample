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

	//攻撃ヒットコンボ
	void AddHitCombo();	//コンボ増加
	void AddHitComboTime();//コンボ時間増加
	void ResetHitCombo();	//コンボ数リセット
	int GetHitCombo() { return combo; }
	float GetHitComboTime() { return combo_time; }	//撃破コンボ継続時間
	bool GetComboFlag() { return combo_flag; }	//コンボフラグ

	void StopComboTime() { combo_time_flag = false; }    //コンボ継続時間ストップ
	void StartComboTime() { combo_time_flag = true; }    //コンボ継続時間スタート
	//アニメーション
	void ResetaAnimeFlag() { anime_flag = false; }	//アニメフラグのリセット
	bool GetAnimeFlag() { return anime_flag; }	//アニメーション再生フラグ

	//スコア
	void SetAddScore(float score_size);	//スコアの値を入力
	int GetCoinNum() { return coin_num; }//コインの取得数
	float GetAddScore() { return add_score_size; }
	float GetScoreGauge() { return score * SCORE_GAUGE_DIVIDE; }	//ゲージ描画時呼び出し
	float GetScore() { return now_score; }	//現在のスコア
	bool GetGoodFlag() { return good_flag; }	//スコアUI描画時使用
	void SetRemainEnemy(int remain_enemy) { enemy_num = remain_enemy; }
	//ウェーブ
	void SetWave(int wave_num);	//ウェーブ数設定
	void WaveTimeLimit(const float deltaTime);	//ウェーブの時間
	void ResetWaveTime();	//ウェーブ時間を0にする
	int GetWave() { return wave; }	//現在のウェーブ
	int GetMaxWave() { return MAX_WAVE; }	//ウェーブの最大数
	float GetTime() { return wave_time; } //時間の取得
	float GetOnceExec() { return once_exec_time; }
	bool GetWaveFlag() { return wave_change_flag; }	//ウェーブ切り替えフラグ	//コイン
	bool GetCoinFlag() { return coin_get_flag; }//コイン取得フラグ
	void ResetCoinFlag() { coin_get_flag = false; }
	int GetCoin() { return coin_num; }

private:
	void ComboTime(const float deltaTime);	//コンボ時間計る

	void ComboScore();	//コンボ数に応じてスコア加算
	void CalcScore(const float deltaTime);	//スコア計算
	void ScoreUp(const float deltaTime);	//アップ
	void ScoreDown(const float deltaTime);	//ダウン


	//攻撃ヒットコンボ
	int	  combo;	//コンボ数
	float combo_time_num;	//コンボの時間
	float combo_time;	//コンボ継続時間
	bool  combo_flag;	//true:コンボ継続可能 false:継続不可
	bool combo_miss_flag;
	bool combo_time_flag;
	//アニメーション
	bool anime_flag;	//true:アニメーション再生 false:停止

	//スコア
	int coin_num;
	float score;
	float now_score;    //現在のスコア
	float add_score_size;
	float enemy_num;
	bool plus_score_flag;	//true:スコアアップ false:スコアダウン
	bool good_flag;
	bool coin_get_flag;	//コイン獲得フラグ

	const float SCORE_START_VALUE = 300.0f;	//初期値設定
	const float SCORE_MAX_VALUE = 3000.0f;	//スコアの最大値
	const float SCORE_UPDN_SPEED = 300.0f;	//スコア増減スピード
	const float SCORE_GAUGE_DIVIDE = 0.113f;	//スコアゲージ3000分の1の数(描画時使用)


	//ウェーブ
	int wave;	//現在のウェーブ
	float wave_time;	//ウェーブの制限時間
	float once_exec_time;
	bool wave_change_flag;	//true:ウェーブ切り替え可能 false:切り替え不可

	const int MAX_WAVE = 12;	//ウェーブの最大数
	const float STAGE_ONE_TIME = 70.0f;//1ステージ目の制限時間
	const float STAGE_TWO_TIME = 40.0f;//2ステージ目移行の制限時間
};