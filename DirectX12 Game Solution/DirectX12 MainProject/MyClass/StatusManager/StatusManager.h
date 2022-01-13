#pragma once
#include "Base/pch.h"

class StatusManager {
public:
	StatusManager() {};
	~StatusManager() {};


	void Initialize();
	void AddCombo(const float deltaTime);
	int Update(const float deltaTime);




	static StatusManager& Instance(){
		static StatusManager instance;
		return instance;
	}

	//プレイヤーのコンボ
	int GetAtkCombo() { return atk_combo; }	//攻撃コンボ時使用
	float GetKillComboTime(const float deltaTime);	//とどめ攻撃のコンボ増加可能時間

	//オーディエンス
	void AddAudience (float add_size	   );	//値を取得
	void CalcAudience(const float deltaTime);	//オーディエンス計算
	void UpAudience	 (const float deltaTime);	//アップ
	void DownAudience(const float deltaTime);	//ダウン
	float ReturnAudience() { return audience * AUDIENCE_GAUGE_DIVIDE; }	//ゲージ描画時呼び出し
	float ReturnScore() { return audience; }	//スコア判定時使用
	void BonusScore(int kill_combo);

	//ハート(必殺技ゲージ)
	void HeartCount();	//敵撃破時呼び出し
	void HeartReset();	//必殺技発動時呼び出し
	float ReturnHeart() { return heart; }	//必殺技使用時呼び出し
	float ReturnRenderHeart() { return heart * HEART_GAUGE_DIVIDE; }//ゲージ描画時呼び出し

private:
	//プレイヤーの攻撃コンボ
	int atk_combo;
	int atk_combo_count;
	float atk_combo_time;
	float kill_combo_time;
	bool atk_combo_flag;

	const int ATK_COMBO_MAX = 4;
	const float ATK_COMBO_TIME_MAX[3]{ 0.617f,0.517f,0.583f };
	const float KILL_COMBO_TIME_MAX = 3.0f;

	//オーディエンス
	float audience;
	float now_audience;    //現在のオーディエンス数
	bool plus_audience_flag;


	const float AUDIENCE_START_VALUE  =  100.0f;	//初期値設定
	const float AUDIENCE_MAX_VALUE	  = 1000.0f;	//スコアの最大値
	const float AUIDENCE_DN_SPEED	  =  300.0f;	//オーディエンス減スピード
	const float AUDIENCE_GAUGE_DIVIDE =  0.334f;	//人ゲージ1000分の1の数(描画時使用)


	//ハート
	float heart;
	const float HEART_MAX = 20.0f;
	const float HEART_GAUGE_DIVIDE = 4.45f;
};