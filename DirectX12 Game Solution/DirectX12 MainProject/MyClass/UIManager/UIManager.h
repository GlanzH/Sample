#pragma ones
#include "Base/pch.h"

class UIManager {
public:
	UIManager() {};
	~UIManager() {};

	bool Initialize();
	void LoadAsset();
	int Update(const float deltaTime);
	int GetTensionCount(int count) { return 0; }
	void Render();
	
private:
	
};