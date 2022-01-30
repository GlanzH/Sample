#include "PlayerManager.h"

#include "MyClass/StatusManager/StatusManager.h"


bool PlayerManager::Initialize() {
	
	player_base.Initialize();
	
	return 0;
}

void PlayerManager::LoadAssets() {
	player_base.LoadAssets();

}

int PlayerManager::Update(const float deltaTime, bool temp)
{

	player_base.Update(deltaTime, temp);

	return 0;
}

void PlayerManager::Render() 
{
	player_base.Render();
	player_base.Debug();
}