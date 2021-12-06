#pragma once
#include "Base/pch.h"
#include "cppcoro/generator.h"

class RankJudgeManager {
public:
	RankJudgeManager() {};
	~RankJudgeManager() {};

	void Initialize();
	void Update();

	void GetAudience();

	void JudgeRnak();

	int ReturnRank() { return now_rank; }

private:
	float now_score;
	int now_rank;
	enum RANK {
		E,D,C,B,A,S
	};
	// コルーチンのプロトタイプ宣言
	cppcoro::generator<int> ReleaseRank();
	cppcoro::generator<int>                  co_routine;
	cppcoro::detail::generator_iterator<int> co_routine_it;
};