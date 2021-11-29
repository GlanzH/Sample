#pragma once
#include "Base/pch.h"
#include "cppcoro/generator.h"

class RankJudgeManager {
public:
	RankJudgeManager() {};
	~RankJudgeManager() {};

	void Initialize();

	void GetVoltage();

	int JudgeRnak();

private:
	float now_score;
	int now_rank;
	enum RANK {
		D,C,B,A,S
	};
	// コルーチンのプロトタイプ宣言
	cppcoro::generator<int> ReleaseRank();
	cppcoro::generator<int>                  co_routine;
	cppcoro::detail::generator_iterator<int> co_routine_it;
};