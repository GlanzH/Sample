#pragma once

class GroundManager {
public:
	GroundManager() {};
	~GroundManager() {};

	void LoadAsset();
	void Render();
	DX9::MODEL& GetModel() { return model; }

private:
	DX9::MODEL model;

	const float pos_z = 50.0f;
};