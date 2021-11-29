
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MultiLighting.h"

MultiPointLighting::MultiPointLighting()
{
}

//------------------------------------------------------------------------------
//	初期化
//------------------------------------------------------------------------------
void MultiPointLighting::Init()
{
	shader = DX9::Shader::CreateFromFile(DXTK->Device9, L"PointLight.fx");
	for (int i = 0; i < 10; i++)
	{
		m_lightsPos[i] = SimpleMath::Vector4::Zero;
		m_lightsColor[i] = SimpleMath::Vector4::Zero;
		m_lightsPower[i] = 1.0f;
		m_maxLight = 10;
	}
}

//------------------------------------------------------------------------------
//	ライトのポジション設定
//------------------------------------------------------------------------------
void MultiPointLighting::SetLightPos(SimpleMath::Vector4 pos, int numLight)
{
	m_lightsPos[numLight] = pos;
}

//------------------------------------------------------------------------------
//	ライトの色設定
//------------------------------------------------------------------------------
void MultiPointLighting::SetLightColor(SimpleMath::Vector4 color, int numLight)
{
	m_lightsColor[numLight] = color;
}

//------------------------------------------------------------------------------
//	ライトの強さ（範囲）
//------------------------------------------------------------------------------
void MultiPointLighting::SetLightPower(float pow, int numLight)
{
	m_lightsPower[numLight] = pow;
}

//------------------------------------------------------------------------------
//	ライトの数
//------------------------------------------------------------------------------
void MultiPointLighting::SetMax(int maxLight)
{
	m_maxLight = maxLight;
}

//------------------------------------------------------------------------------
//	モデルの描画前のシェーダー設定 モデル版
//------------------------------------------------------------------------------
void MultiPointLighting::Begin(DX9::CAMERA camera, DX9::MODEL& model)
{
	shader->SetVectorArray("g_vLightPos",m_lightsPos,m_maxLight);
	shader->SetVectorArray("g_Diffuse",m_lightsColor,m_maxLight);
	shader->SetFloatArray("g_Pow", m_lightsPower, m_maxLight);
	shader->SetParameter("g_numLight", m_maxLight);

	auto wvp = model->GetWorldTransform() * camera->ViewMatrix * camera->ProjectionMatrix;

	shader->SetParameter("g_vEye", (camera->GetForwardVector(), 0));
	shader->SetParameter("g_mW", model->GetWorldTransform());
	shader->SetParameter("g_mWVP", wvp);

	shader->Begin();
	shader->BeginPass(0);
}

//------------------------------------------------------------------------------
//　アニメーション付きモデル版
//------------------------------------------------------------------------------
void MultiPointLighting::Begin(DX9::CAMERA camera, DX9::SKINNEDMODEL& model)
{
	shader->SetVectorArray("g_vLightPos", m_lightsPos, m_maxLight);
	shader->SetVectorArray("g_Diffuse", m_lightsColor, m_maxLight);
	shader->SetFloatArray("g_Pow", m_lightsPower, m_maxLight);
	shader->SetParameter("g_numLight", m_maxLight);

	auto wvp = model->GetWorldTransform() * camera->ViewMatrix * camera->ProjectionMatrix;

	shader->SetParameter("g_vEye", (camera->GetForwardVector(), 0));
	shader->SetParameter("g_mW", model->GetWorldTransform());
	shader->SetParameter("g_mWVP", wvp);

	shader->Begin();
	shader->BeginPass(0);
}

//------------------------------------------------------------------------------
//	モデルの描画後
//------------------------------------------------------------------------------
void MultiPointLighting::End()
{
	shader->EndPass();
	shader->End();
}



