#include "WaveProcess.h"
#include "MyClass/StatusManager/StatusManager.h"
#include "MyClass/EnemyManager/EnemyFactory/EnemyFactory.h"

WaveProcess::WaveProcess() {

}

WaveProcess::~WaveProcess() {

}

bool WaveProcess::Initialize() {
	stage_num = 0;
	wave_num = 0;

	now_time = 0;
	time_one_digit = 0.0f;
	time_two_digit = 0;
	time_num_scale = 1.0f;
	scale_mode = EXPAND;
	one_digit_flag = false;

	wave_anim_x = 0.0f;
	wave_anim_y = 0.0f;
	black_alpha = 0.0f;
	anim_alpha = 0.0f;
	wait_time = 0.0f;
	time_delta = 0.0f;
	anim_end_flag = false;
	co_start_flag = false;


	return true;
}

void WaveProcess::LoadAssets() {
	wave_anim[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage1/stage1_wave1_anim.png");
	wave_anim[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage1/stage1_wave2_anim.png");
	wave_anim[2] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage1/stage1_wave3_anim.png");
	wave_anim[3] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage2/stage2_wave1_anim.png");
	wave_anim[4] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage2/stage2_wave2_anim.png");
	wave_anim[5] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage2/stage2_wave3_anim.png");
	wave_anim[6] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage3/stage3_wave1_anim.png");
	wave_anim[7] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage3/stage3_wave2_anim.png");
	wave_anim[8] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage3/stage3_wave3_anim.png");
	wave_anim[9] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage4/stage4_wave1_anim.png");
	wave_anim[10] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage4/stage4_wave2_anim.png");
	wave_anim[11] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Wave/Stage4/stage4_wave3_anim.png");

	black = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/kuro.png");

	time = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Time/TIME.png");
	time_number = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/Time/numbers_timer.png");
}

int WaveProcess::Update(EnemyManager* enemy, const float deltaTime) {
	StatusManager::Instance().WaveTimeLimit(deltaTime);

	now_time = StatusManager::Instance().GetTime();
	time_one_digit = (now_time % 10) * TIME_NUM_WIDTH;
	time_two_digit = (now_time / 10) * TIME_NUM_WIDTH;
	wave_num = StatusManager::Instance().GetWave();
	//if (StatusManager::Instance().GetWave() == 0) {
	//	max_stop = 0.01f;
	//}

	if (wave_num < StatusManager::Instance().GetMaxWave() && now_time == 0) {
		if (stop_frame < max_stop) {
			one_digit_flag = false;
			stop_frame += deltaTime;
		}
		else {
			StatusManager::Instance().ResetWaveTime();
			StatusManager::Instance().SetWave(++stage_num);
			enemy->ResetRemainEnemy();
			enemy->ResetDeathEnemy();
			stop_frame = 0.0f;
			time_num_scale = 1.0f;
			co_start_flag = false;
			anim_end_flag = false;
		}
	}

	if (enemy->GetWaveEnemy() == enemy->GetDeathEnemyCount())
		StatusManager::Instance().ResetWaveTime();

	if (now_time < 10) {
		one_digit_flag = true;
	}
	else {
		one_digit_flag = false;
	}

	if (one_digit_flag && now_time > 0) {
		if (scale_mode == EXPAND) {
			time_num_scale += 2.0f * deltaTime;
			if (time_num_scale > 2.0f) {
				scale_mode = SHRINK;
			}
		}
		if (scale_mode == SHRINK) {
			time_num_scale -= 2.0f * deltaTime;
			if (time_num_scale < 1.0f) {
				scale_mode = EXPAND;
			}
		}
	}

	return 0;
}

void WaveProcess::Render() {

	if (wave_num > 0) {
		if (!one_digit_flag) {
			DX9::SpriteBatch->DrawSimple(
				time.Get(),
				SimpleMath::Vector3(TIME_POS_X, TIME_POS_Y, 0.0f)
			);

			DX9::SpriteBatch->DrawSimple(
				time_number.Get(),
				SimpleMath::Vector3(ONE_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
				RectWH(time_one_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
			);

			DX9::SpriteBatch->DrawSimple(
				time_number.Get(),
				SimpleMath::Vector3(TWO_DIGIT_POS_X, TIME_NUM_POS_Y, 0.0f),
				RectWH(time_two_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT)
			);
		}
		else {
			DX9::SpriteBatch->DrawSimple(
				time.Get(),
				SimpleMath::Vector3(TIME_POS_X, TIME_POS_Y, 0.0f),
				Rect(0, 0, TIME_WIDTH, TIME_HIGHT),
				DX9::Colors::RGBA(COLOR_MAX, 0, 0, COLOR_MAX)
			);

			DX9::SpriteBatch->Draw(
				time_number.Get(),
				SimpleMath::Vector3(TIME_POS_X + 50.0f, TIME_POS_Y + 70.0f, 0.0f),
				RectWH(time_one_digit, 0, TIME_NUM_WIDTH, TIME_NUM_HIGHT),
				DX9::Colors::RGBA(COLOR_MAX, 0, 0, COLOR_MAX),
				SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
				SimpleMath::Vector3(TIME_NUM_ORIGIN_X, TIME_NUM_ORIGIN_Y, 0.0f),
				SimpleMath::Vector2(time_num_scale, time_num_scale)
			);
			DX9::SpriteBatch->ResetTransform();
		}
	}

	DX9::SpriteBatch->DrawSimple(
		black.Get(),
		SimpleMath::Vector3::Zero,
		Rect(0, 0, 1280, 720),
		DX9::Colors::RGBA(255, 255, 255, black_alpha)
	);

	DX9::SpriteBatch->DrawSimple(
		wave_anim[wave_num].Get(),
		SimpleMath::Vector3(450.0f, 330.0f, 0.0f),
		RectWH(WAVE_WIDTH * (int)wave_anim_x, WAVE_HIGHT * (int)wave_anim_y, WAVE_WIDTH, WAVE_HIGHT),
		DX9::Colors::RGBA(255, 255, 255, (int)anim_alpha)
	);
}

void WaveProcess::WaveAnimation(const float deltaTime) {
	time_delta = deltaTime;
	
	if (!co_start_flag) {
		co_anim = WaveChangeAinm();        // コルーチンの生成
		co_anim_it = co_anim.begin(); // コルーチンの実行開始
		co_start_flag = true;
	}

	if (co_anim_it != co_anim.end()) {
		co_anim_it++;
	}

	if (co_anim_it != co_anim.end()) {
		co_anim.begin();
	}
}

cppcoro::generator<int> WaveProcess::WaveChangeAinm() {
	co_yield 0;
	anim_alpha = 255.0f;
	black_alpha = 0.0f;
	wave_anim_x = 0.0f;
	wave_anim_y = -1.0f;

	//フェードイン
	while (true)
	{
		wait_time += time_delta;
		black_alpha = std::min(black_alpha + 300.0f * time_delta, 200.0f);
		if (black_alpha >= 200.0f) {
			break;
		}
		co_yield 1;
	}

	//待機
	while (wait_time < 2.0f) {
		wait_time += time_delta;
		co_yield 2;
	}
	wait_time = 0.0f;

	//アニメーション
	if (wave_num == 0 || wave_num % 3 == 0) {
		//章が切り替わる
		while (true) {
			wave_anim_y += 10.0f * time_delta;
			if (wave_anim_y > 24.0f) {
				if (wave_anim_x < 1) {
					wave_anim_x = 1.0f;
					wave_anim_y = 0.0f;
				}
				else {
					break;
				}
			}
			co_yield 3;
		}
		wave_anim_x = 1.0f;
	}
	else {
		//幕が切り替わる
		while (true) {
			wave_anim_y += 10.0f * time_delta;
			if (wave_anim_y > 24.0f) {
				break;
			}
			co_yield 3;
		}
	}
	wave_anim_y = 24.0f;
	
	
	//待機
	while (wait_time < 2.0f) {
		wait_time += time_delta;
		co_yield 3;
	}
	wait_time = 0.0f;

	//フェードアウト
	while (anim_alpha > 0.0f) {
		black_alpha = std::max(black_alpha - 300.0f * time_delta, 0.0f);
		anim_alpha  = std::max(anim_alpha  - 300.0f * time_delta, 0.0f);
		co_yield 4;
	}

	//待機
	while (wait_time < 2.0f) {
		wait_time += time_delta;
		co_yield 3;
	}
	wait_time = 0.0f;

	anim_end_flag = true;
	co_return;
}