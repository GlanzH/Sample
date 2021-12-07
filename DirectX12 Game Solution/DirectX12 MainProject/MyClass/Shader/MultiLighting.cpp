
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
	shader = DX9::Shader::CreateFromFile(DXTK->Device9, L"Point.fx");
}

//------------------------------------------------------------------------------
//	���C�g�̃|�W�V�����ݒ�
//------------------------------------------------------------------------------
void MultiPointLighting::SetLight(DX9::SKINNEDMODEL& model)
{
	auto pos = model->GetPosition();
	m_lightsPos.push_back(SimpleMath::Vector4(pos.x, -17, pos.z - 4, 1));
}

//------------------------------------------------------------------------------
//	���C�g�̐F�ݒ�
//------------------------------------------------------------------------------
void MultiPointLighting::SetLightColor(SimpleMath::Vector4 color)
{
	m_lightsColor = color;
}

//------------------------------------------------------------------------------
//	���C�g�̋����i�͈́j
//------------------------------------------------------------------------------
void MultiPointLighting::SetLightPower(float pow)
{
	m_lightsPower = pow;
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
void MultiPointLighting::PointRender(DX9::CAMERA camera, DX9::MODEL& model, DX9::SKINNEDMODEL& target)
{
	auto playerPos = target->GetPosition();
	shader->SetParameter("g_Light", SimpleMath::Vector4(playerPos.x, playerPos.y - 20, playerPos.z + 25.0f , 1));
	shader->SetParameter("g_Attenuation",SimpleMath::Vector4(1.0f, 0.0045f, 0.0028f, 1));
	shader->SetParameter("g_Pow", m_lightsPower);
	shader->SetParameter("g_LightColor", m_lightsColor);


	shader->SetParameter("g_World", model->GetWorldTransform());
	shader->SetParameter("g_View", camera->GetViewMatrix());
	shader->SetParameter("g_Projection", camera->GetProjectionMatrix());

	shader->SetParameter("g_DLightDir", SimpleMath::Vector4(1,-1,-1,1));

	shader->Begin();
	shader->BeginPass(0);
	model->Draw();
	shader->EndPass();
	shader->End();
}

void MultiPointLighting::ShadeRender(DX9::SKINNEDMODEL& model, SimpleMath::Vector4 color)
{
	SimpleMath::Vector3 lightPos = SimpleMath::Vector3(1, 1, 0);
	auto plane = SimpleMath::Plane(SimpleMath::Vector4(0, 1, 0, 0));

	auto shadow = SimpleMath::Matrix::CreateShadow(lightPos, plane);
	shadow = shadow * SimpleMath::Matrix::CreateScale(0.1f);
	auto modelPos = model->GetPosition();
	shadow *= SimpleMath::Matrix::CreateTranslation(modelPos.x,0,modelPos.z);

	DXTK->Device9->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, 0);

	// �����_�����O�X�e�[�g�ݒ�
	DXTK->Device9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DXTK->Device9->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	// �A���t�@�u�����h�ݒ�
	DXTK->Device9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	DXTK->Device9->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DXTK->Device9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DXTK->Device9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA);
	DXTK->Device9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DXTK->Device9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	// �X�e���V���ݒ�
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
//�@�A�j���[�V�����t�����f����
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




