#pragma once

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;
using namespace SimpleMath;

class TextureLight {
public:
	struct SCorner
	{
		Vector3 UL;
		Vector3 UR;
		Vector3 BL;
		Vector3 BR;
	};

	void Init();
	void Update();
	void Render();
	void SetPos(SCorner Corner);
	void SetColor(Vector4 Color) { color = Color; }

private:
	void LoadTexture();

	DX9::VertexColor vertex[6];
	SimpleMath::Vector3 pos[4];

	Vector4 color;

	IDirect3DTexture9* texture;
};