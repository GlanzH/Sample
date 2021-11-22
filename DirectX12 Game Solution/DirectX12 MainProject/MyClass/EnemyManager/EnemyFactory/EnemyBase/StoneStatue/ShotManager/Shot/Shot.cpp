#include "Shot.h"

// Initialize a variable and audio resources.
bool Shot::Initialize()
{
	return true;
}

// Allocate all memory the Direct3D and Direct2D resources.
void Shot::LoadAssets()
{

}

// Updates the scene.
int Shot::Update(const float deltaTime)
{
	// TODO: Add your game logic here.
	
	//shot_flag‚ªtrue‚È‚ç’e‚ð“®‚©‚·
	//if (shot_flag)

	//’e‚Ìä`‘Ñ‹——£‚Ü‚Å“ž’B‚µ‚½‚çshot_flag‚ðfalse‚É‚·‚é
	//if (pos.x > max_move_bullet.x)

	return 0;
}

void Shot::Shots(SimpleMath::Vector3 shot_pos) {
	shot_flag = true;
	pos = shot_pos + adjust_position;
}

// Draws the scene.
void Shot::Render()
{
	//if (shot_flag)
	//	model->Draw();
}