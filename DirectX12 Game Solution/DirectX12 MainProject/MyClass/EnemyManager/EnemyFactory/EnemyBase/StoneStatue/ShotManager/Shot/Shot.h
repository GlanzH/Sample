#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Shot {
public:
	Shot() {};
	~Shot() {};

	// These are the functions you will implement.
	bool Initialize();
	void LoadAssets();

	int Update(const float deltaTime);
	void Render();

	void Shots(SimpleMath::Vector3 shot_pos);

	//DX9::MODEL& GetCollision() { return collision; }

	bool  IsShot()	   { return shot_flag; }
	bool GetShotFlag() { return shot_flag; }

private:
	SimpleMath::Vector3 pos;
	SimpleMath::Vector3 speed;

	//’e‚Ì‰ŠúˆÊ’u’²®
	SimpleMath::Vector3 adjust_position;
	
	//’e‚ÌÅ‘åˆÚ“®‹——£
	SimpleMath::Vector3 max_move_bullet;

	DX9::MODEL model;
	DX9::MODEL collision;

	bool shot_flag = false;
};