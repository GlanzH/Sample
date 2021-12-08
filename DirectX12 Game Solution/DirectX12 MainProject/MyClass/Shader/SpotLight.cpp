
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "SpotLight.h"

SpotLight::SpotLight()
{
}

//------------------------------------------------------------------------------
//	初期化
//------------------------------------------------------------------------------
void SpotLight::Init()
{
	shader = DX9::Shader::CreateFromFile(DXTK->Device9, L"SpotLight.fx");
	m_lightsPower = 1.0f;
	m_cone = 5.0f;
	m_range = 1000.0f;
	m_diffuseColor = Vector4(1, 1, 1, 1);
	m_ambientColor = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	m_lightsPos = Vector3(0, 50, 40);
	m_lightDir = Vector3(0, -1, 0);
}

//------------------------------------------------------------------------------
//	ライトのポジション設定
//------------------------------------------------------------------------------
void SpotLight::SetPosition(Vector3 pos)
{
	m_lightsPos = pos;
}

//------------------------------------------------------------------------------
//	ライトの色設定
//------------------------------------------------------------------------------
void SpotLight::SetLightColor(SimpleMath::Vector4 color)
{
	auto fixColor = Vector4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w);
	m_diffuseColor = fixColor;
}

//------------------------------------------------------------------------------
//	ライトの環境色設定
//------------------------------------------------------------------------------
void SpotLight::SetAmbientColor(Vector4 color)
{
	auto fixColor = Vector4(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w);
	m_ambientColor = fixColor;
}

//------------------------------------------------------------------------------
//	ライトの照らす範囲
//------------------------------------------------------------------------------
void SpotLight::SetCone(float angle)
{
	m_cone = angle;
}

//------------------------------------------------------------------------------
//	ライトの強さ（範囲）
//------------------------------------------------------------------------------
void SpotLight::SetPower(float pow = 1.0f)
{
	m_lightsPower = pow;
}

//------------------------------------------------------------------------------
//	ライトが届く距離
//------------------------------------------------------------------------------
void SpotLight::SetRange(float range)
{
	m_range = range;
}

//------------------------------------------------------------------------------
//	ライトの数
//------------------------------------------------------------------------------
void SpotLight::SetMax(int maxLight)
{
	m_maxLight = maxLight;
}

//------------------------------------------------------------------------------
//	モデルの描画前のシェーダー設定 モデル版
//------------------------------------------------------------------------------
void SpotLight::PointRender(DX9::CAMERA camera, DX9::MODEL& model)
{

	shader->SetParameter("g_LightPos" , m_lightsPos);
	shader->SetParameter("g_LightDir", m_lightDir);
	shader->SetParameter("g_LightAtt", Vector3(0.03f, 0.01f, 0.0f));
	shader->SetParameter("g_Cone", m_cone);
	shader->SetParameter("g_AColor", m_ambientColor);
	shader->SetParameter("g_Color", m_diffuseColor);
	shader->SetParameter("g_LightRange",m_range);
	shader->SetParameter("g_Pow", m_lightsPower);

	auto wvp = model->GetWorldTransform() * camera->GetViewProjectionMatrix();

	//shader->SetParameter("g_World", model->GetWorldTransform());
	//shader->SetParameter("g_View", camera->GetViewMatrix());
	//shader->SetParameter("g_Projection", camera->GetProjectionMatrix());
	shader->SetParameter("g_WVP", wvp);
	shader->SetParameter("g_World", model->GetWorldTransform());

	shader->Begin();
	shader->BeginPass(0);
	model->Draw();
	shader->EndPass();
	shader->End();
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

//------------------------------------------------------------------------------
//　アニメーション付きモデル版
//------------------------------------------------------------------------------
//void MultiPointLighting::Begin(DX9::CAMERA camera, DX9::SKINNEDMODEL model)
//{
//	shader->SetVectorArray("g_vLightPos", m_lightsPos, m_maxLight);
//	shader->SetVectorArray("g_Diffuse", m_lightsColor, m_maxLight);
//	shader->SetFloatArray("g_Pow", m_lightsPower, m_maxLight);
//	shader->SetParameter("g_numLight", m_maxLight);
//
//	auto wvp = model->GetWorldTransform() * camera->ViewMatrix * camera->ProjectionMatrix;
//
//	shader->SetParameter("g_vEye", (camera->GetForwardVector(), 0));
//	shader->SetParameter("g_mW", model->GetWorldTransform());
//	shader->SetParameter("g_mWVP", wvp);
//
//	shader->Begin();
//	shader->BeginPass(0);
//}




