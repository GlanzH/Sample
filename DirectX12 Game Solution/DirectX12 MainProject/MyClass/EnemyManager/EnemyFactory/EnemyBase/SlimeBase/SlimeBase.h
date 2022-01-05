#pragma once
#include "Base/DX12Effekseer.h"

using namespace DirectX;

class SlimeClass
{
public:
	SlimeClass();
	~SlimeClass() {};

	virtual int Update(SimpleMath::Vector3 player, bool special_attack_flag, bool thorow_things_flag, const float deltaTime);

	std::string GetTag() { return enemy_tag; };
private:

	float delta;
	const float retreat_dist = 15.0f;
	bool retreat_flag;
	bool reduce_audience_flag = false;
	const int max_retreat = 30;
	int   retreat_count = 0;
	std::string enemy_tag;
	DX9::SKINNEDMODEL anim_model;
	SimpleMath::Vector3 player_pos;
	SimpleMath::Vector3 position;
protected:
	BoundingBox		  anim_box;
	DX9::MODEL		  anim_collision;
	const float fit_collision_y = 4.0f;
};

