
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "SpotLight.h"

SpotLight::SpotLight()
{
}

//------------------------------------------------------------------------------
//	初期化
//------------------------------------------------------------------------------
void SpotLight::Init(int num)
{
	shader = DX9::Shader::CreateFromFile(DXTK->Device9, L"Shader/SpotLightBone.fx");
	shader2 = DX9::Shader::CreateFromFile(DXTK->Device9, L"Shader/SpotLight.fx");


	m_maxLight = num;

	for (int i = 0; i < m_maxLight; i++)
	{
		m_lightsPower[i] = 1.0f;
		m_cone[i] = 5.0f;
		m_range[i] = 1000.0f;
		m_diffuseColor[i] = Vector4(1, 1, 1, 1);
		m_ambientColor[i] = Vector4(0.2, 0.2, 0.2, 1.0f);
		m_lightsPos[i] = Vector3(0, 50, 40);
		m_lightDir[i] = Vector3(0, -1, 0);
		m_att[i] = Vector3(0.03f, 0.01f, 0.0f);
	}

	TextureLight tex;
	tex.Init();
}

//------------------------------------------------------------------------------
//	ライトのポジション設定
//------------------------------------------------------------------------------
void SpotLight::SetPosition(Vector3 pos, int index)
{
	m_lightsPos[index] = pos;
}

//------------------------------------------------------------------------------
//	ライトの色設定
//------------------------------------------------------------------------------
void SpotLight::SetLightColor(Vector4 color, int index)
{
	auto fixColor = Vector4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w);
	m_diffuseColor[index] = fixColor;
}

//------------------------------------------------------------------------------
//	ライトの環境色設定
//------------------------------------------------------------------------------
void SpotLight::SetAmbientColor(Vector4 color, int index)
{
	auto fixColor = Vector4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w);
	m_ambientColor[index] = fixColor;
}

//------------------------------------------------------------------------------
//	ライトの角度設定
//------------------------------------------------------------------------------
void SpotLight::SetAngle(Vector3 angle, int index)
{
	m_lightDir[index] = angle;
	m_lightDir[index].Normalize();
}

void SpotLight::SetAtt(Vector3 att, int index)
{
	m_att[index] = att;
}

//------------------------------------------------------------------------------
//	ライトの照らす範囲
//------------------------------------------------------------------------------
void SpotLight::SetCone(float angle, int index)
{
	m_cone[index] = angle;
}

//------------------------------------------------------------------------------
//	ライトの強さ（範囲）
//------------------------------------------------------------------------------
void SpotLight::SetPower(float pow, int index)
{
	m_lightsPower[index] = pow;
}

//------------------------------------------------------------------------------
//	ライトが届く距離
//------------------------------------------------------------------------------
void SpotLight::SetRange(float range, int index)
{
	m_range[index] = range;
}

//------------------------------------------------------------------------------
//	モデルの描画前のシェーダー設定 モデル版
//------------------------------------------------------------------------------
void SpotLight::PointRender(DX9::CAMERA camera, DX9::SKINNEDMODEL& model)
{
	shader->SetData("g_LightPos" , m_lightsPos, (sizeof(Vector3) * m_maxLight));
	shader->SetData("g_LightDir", m_lightDir, sizeof(Vector3) * m_maxLight);
	shader->SetData("g_LightAtt", m_att, sizeof(Vector3) * m_maxLight);
	shader->SetData("g_Cone", m_cone, sizeof(float) * m_maxLight);
	shader->SetData("g_AColor", m_ambientColor, sizeof(Vector4) * m_maxLight);
	shader->SetData("g_Color", m_diffuseColor, sizeof(Vector4) * m_maxLight);
	shader->SetData("g_LightRange",m_range, sizeof(float) * m_maxLight);
	shader->SetData("g_Pow", m_lightsPower, sizeof(float) * m_maxLight);
	shader->SetParameter("g_Count", m_maxLight);

	auto wvp = model->GetWorldTransform() * camera->GetViewProjectionMatrix();

	shader->SetParameter("g_WVP", wvp);
	shader->SetParameter("g_VP", camera->GetViewProjectionMatrix());
	shader->SetParameter("g_World", model->GetWorldTransform());

	model->Draw(shader);
}

void SpotLight::PointRender(DX9::CAMERA camera, DX9::MODEL& model)
{
	shader2->SetData("g_LightPos", m_lightsPos, (sizeof(Vector3) * m_maxLight));
	shader2->SetData("g_LightDir", m_lightDir, sizeof(Vector3) * m_maxLight);
	shader2->SetData("g_LightAtt", m_att, sizeof(Vector3) * m_maxLight);
	shader2->SetData("g_Cone", m_cone, sizeof(float) * m_maxLight);
	shader2->SetData("g_AColor", m_ambientColor, sizeof(Vector4) * m_maxLight);
	shader2->SetData("g_Color", m_diffuseColor, sizeof(Vector4) * m_maxLight);
	shader2->SetData("g_LightRange", m_range, sizeof(float) * m_maxLight);
	shader2->SetData("g_Pow", m_lightsPower, sizeof(float) * m_maxLight);
	shader2->SetParameter("g_Count", m_maxLight);

	auto wvp = model->GetWorldTransform() * camera->GetViewProjectionMatrix();

	shader2->SetParameter("g_WVP", wvp);
	shader2->SetParameter("g_VP", camera->GetViewProjectionMatrix());
	shader2->SetParameter("g_World", model->GetWorldTransform());

	shader2->Begin();
	shader2->BeginPass(0);
	model->Draw();
	shader2->EndPass();
	shader2->End();
}

void SpotLight::ShadeRender(DX9::SKINNEDMODEL& model, SimpleMath::Vector4 color)
{
	SimpleMath::Vector3 lightPos = SimpleMath::Vector3(1, 1, 0);
	auto plane = SimpleMath::Plane(SimpleMath::Vector4(0, 1, 0, 0));

	auto shadow = SimpleMath::Matrix::CreateShadow(lightPos, plane);
	shadow = shadow * SimpleMath::Matrix::CreateScale(0.1f);
	auto modelPos = model->GetPosition();
	shadow *= SimpleMath::Matrix::CreateTranslation(modelPos.x,0,modelPos.z);

	DXTK->Device9->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, 0);

	// レンダリングステート設定
	DXTK->Device9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DXTK->Device9->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	// アルファブレンド設定
	DXTK->Device9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	DXTK->Device9->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DXTK->Device9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DXTK->Device9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA);
	DXTK->Device9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DXTK->Device9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// ステンシル設定
	DXTK->Device9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
	DXTK->Device9->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	DXTK->Device9->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	DXTK->Device9->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	DXTK->Device9->SetRenderState(D3DRS_STENCILREF, 1);
	DXTK->Device9->SetRenderState(D3DRS_STENCILENABLE, TRUE);


	D3DMATERIAL9 mat;
	mat.Diffuse = DX9::Colors::Value(color.x, color.y, color.z, color.w);
	mat.Ambient = DX9::Colors::Value(color.x, color.y, color.z, color.w);
	mat.Specular = DX9::Colors::Value(0, 0, 0, 0);
	mat.Emissive = DX9::Colors::Value(0, 0, 0, 0);
	mat.Power = 0;
	DXTK->Device9->SetMaterial(&mat);
	DXTK->Device9->SetTexture(0, nullptr);
	model->DrawShadow(shadow);

	DXTK->Device9->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	DXTK->Device9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	DXTK->Device9->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG);
	DXTK->Device9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}




