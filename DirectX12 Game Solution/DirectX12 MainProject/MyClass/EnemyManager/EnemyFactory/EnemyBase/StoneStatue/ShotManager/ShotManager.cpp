#include "ShotManager.h"


// Initialize a variable and audio resources.
void ShotManager::Initialize()
{
	for (int i = 0; i < MAX_SHOT; ++i)
		shot[i].Initialize();
}

// Allocate all memory the Direct3D and Direct2D resources.
void ShotManager::LoadAssets()
{
	for (int i = 0; i < MAX_SHOT; ++i)
		shot[i].LoadAssets();
}

// Updates the scene.
void ShotManager::Update(const float deltaTime)
{
	// TODO: Add your game logic here.
	for (int i = 0; i < MAX_SHOT; ++i)
		shot[i].Update(deltaTime);
}

void ShotManager::Shots(SimpleMath::Vector3 shot_pos) {
	for (int i = 0; i < MAX_SHOT; ++i) {
		if (!shot[i].IsShot()) {
			shot[i].Shots(shot_pos);
			break;
		}
	}
}

// Draws the scene.
void ShotManager::Render()
{
	for (int i = 0; i < MAX_SHOT; ++i)
		shot[i].Render();
}