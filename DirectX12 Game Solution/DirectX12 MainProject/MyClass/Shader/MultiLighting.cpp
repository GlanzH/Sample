
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "MultiLighting.h"

MultiPointLighting::MultiPointLighting()
{
}

//------------------------------------------------------------------------------
//	������
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
//	���C�g�̃|�W�V�����ݒ�
//------------------------------------------------------------------------------
void MultiPointLighting::SetLightPos(SimpleMath::Vector4 pos, int numLight)
{
	m_lightsPos[numLight] = pos;
}

//------------------------------------------------------------------------------
//	���C�g�̐F�ݒ�
//------------------------------------------------------------------------------
void MultiPointLighting::SetLightColor(SimpleMath::Vector4 color, int numLight)
{
	m_lightsColor[numLight] = color;
}

//------------------------------------------------------------------------------
//	���C�g�̋����i�͈́j
//------------------------------------------------------------------------------
void MultiPointLighting::SetLightPower(float pow, int numLight)
{
	m_lightsPower[numLight] = pow;
}

//------------------------------------------------------------------------------
//	���C�g�̐�
//------------------------------------------------------------------------------
void MultiPointLighting::SetMax(int maxLight)
{
	m_maxLight = maxLight;
}

//------------------------------------------------------------------------------
//	���f���̕`��O�̃V�F�[�_�[�ݒ� ���f����
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
//�@�A�j���[�V�����t�����f����
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
//	���f���̕`���
//------------------------------------------------------------------------------
void MultiPointLighting::End()
{
	shader->EndPass();
	shader->End();
}



