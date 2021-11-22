#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Shot/Shot.h"

using namespace DirectX;

class ShotManager {
public:
	ShotManager(){}
	~ShotManager() {}

	void Initialize();
	void LoadAssets();

	void Update(const float deltaTime);
	void Render();

	void Shots(SimpleMath::Vector3 shot_pos);

private:
	enum { MAX_SHOT = 5 };
	Shot shot[MAX_SHOT];
};