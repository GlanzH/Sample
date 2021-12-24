#include "Base/pch.h"
#include "Base/dxtk.h"

#include "TextureLight.h"


void TextureLight::Init()
{
	color = SimpleMath::Vector4(255, 255, 255, 60);

	pos[0] = Vector3(-20, 0, 50);
	pos[1] = Vector3(-50, 70, 50);
	pos[2] = Vector3(-20, 50, 50);
	pos[3] = Vector3(20, 0, 50);


	vertex[0].position = pos[0];
	vertex[0].uv = Vector2(0, 1);
	vertex[0].color = DX9::Colors::RGBA(color.x, color.y, color.z, color.w);
	vertex[1].position = pos[1];
	vertex[1].uv = Vector2(0, 0);
	vertex[1].color = DX9::Colors::RGBA(color.x, color.y, color.z, color.w);
	vertex[2].position = pos[2];
	vertex[2].uv = Vector2(1, 0);
	vertex[2].color = DX9::Colors::RGBA(color.x, color.y, color.z, color.w);

	vertex[3].position = pos[2];
	vertex[3].uv = Vector2(1, 0);
	vertex[3].color = DX9::Colors::RGBA(color.x, color.y, color.z, color.w);
	vertex[4].position = pos[3];
	vertex[4].uv = Vector2(1, 1);
	vertex[4].color = DX9::Colors::RGBA(color.x, color.y, color.z, color.w);
	vertex[5].position = pos[0];
	vertex[5].uv = Vector2(0, 1);
	vertex[5].color = DX9::Colors::RGBA(color.x, color.y, color.z, color.w);

	LoadTexture();
}

void TextureLight::Render()
{
	SimpleMath::Matrix mat = SimpleMath::Matrix::Identity;
	DXTK->Direct3D9->SetTransform(D3DTS_WORLD, *(D3DXMATRIX*)&mat);
	DXTK->Direct3D9->SetTexture(0, texture);
	DXTK->Direct3D9->SetRenderState(Lighting_Disable);
	//DXTK->Direct3D9->AlphaBendEnable(true);
	DXTK->Direct3D9->DrawInstanced(D3DPT_TRIANGLELIST, 2, &vertex[0], DX9::VertexColor::FVF);
	//DXTK->Direct3D9->AlphaBendEnable(false);
	DXTK->Direct3D9->SetRenderState(Lighting_Enable);
}

void TextureLight::SetPos(SCorner corner)
{
	pos[0] = corner.BL;
	pos[1] = corner.UL;
 	pos[2] = corner.UR;
 	pos[3] = corner.BR;
}
 
void TextureLight::LoadTexture()
{
	auto re = D3DXCreateTextureFromFile(
		DXTK->Device9,
		L"Shader/spotlight.png",
		&texture
	);
	

}



