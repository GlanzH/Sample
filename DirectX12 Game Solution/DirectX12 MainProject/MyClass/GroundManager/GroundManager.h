#pragma once

class GroundManager {
public:
	GroundManager();
	~GroundManager();

	bool Initialize();
	int  Update();
	void Render();
	DX9::MODEL& GetModel() { return model; }

private:
	DX9::MODEL model;
};