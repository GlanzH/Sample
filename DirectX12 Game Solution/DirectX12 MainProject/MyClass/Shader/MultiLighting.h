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
	void SetLightPos(SimpleMath::Vector4 pos,int number);
	//void SetLightColor(SimpleMath::Vector4 color, int numLight);
	void SetLightPower(float pow, int number);
	void SetMax(int maxLight);
	void PointRender(DX9::CAMERA,DX9::MODEL&,DX9::SKINNEDMODEL&);
	//void Begin(DX9::CAMERA, DX9::SKINNEDMODEL);;
	void ShadeRender(DX9::SKINNEDMODEL& model,SimpleMath::Vector4 color);
private:

	DX9::SHADER shader;

	int m_maxLight;
	SimpleMath::Vector4 m_lightsPos;
	SimpleMath::Vector4 m_lightsColor;
	float m_lightsPower;
};