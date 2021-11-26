#include "MyClass/RankJudgeManager/RankJudgeManager.h"
#include "MyClass/StatusManager/StatusManager.h"

void RankJudgeManager::Initialize() {

	co_routine = ReleaseRank();        // コルーチンの生成
	co_routine_it = co_routine.begin(); // コルーチンの実行開始
	
	return;
}

void RankJudgeManager::GetVoltage() {
	now_score = StatusManager::Instance().ReturnVolt();
}

void RankJudgeManager::JudgeRnak() {

	if (now_score <= 0.0f) {
		now_rank = D;
	}
	else if (now_score >= 1.0f && now_score <= 50.0f) {
		now_rank = C;
	}
	else if (now_score >= 51.0f && now_score <= 99.0f) {
		now_rank = B;
	}
	else if (now_score >= 100.0f && now_score <= 199.0f) {
		now_rank = A;
	}
	else if (now_score >= 200.0f) {
		now_rank = S;
	}

	return;
}

cppcoro::generator<int> RankJudgeManager::ReleaseRank()
{
	co_yield 0;

	while (true) {
		co_yield 1;
	}
	co_return;
}