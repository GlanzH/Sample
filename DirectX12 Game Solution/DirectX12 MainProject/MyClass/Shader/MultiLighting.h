#pragma once

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

//------------------------------------------------------------------------------
//	ライトエフェクト定義
//------------------------------------------------------------------------------
class MultiPointLighting
{
public:
	MultiPointLighting();
	~MultiPointLighting() {};

	void Init();
	void SetLightPos(SimpleMath::Vector4 pos,int numLight);
	void SetLightColor(SimpleMath::Vector4 color, int numLight);
	void SetLightPower(float pow, int numLight);
	void SetMax(int maxLight);
	void Begin(DX9::CAMERA,DX9::MODEL&);
	void Begin(DX9::CAMERA, DX9::SKINNEDMODEL&);
	void End();
private:

	DX9::SHADER shader;

	int m_maxLight;
	SimpleMath::Vector4 m_lightsPos[10];
	SimpleMath::Vector4 m_lightsColor[10];
	float m_lightsPower[10];
};