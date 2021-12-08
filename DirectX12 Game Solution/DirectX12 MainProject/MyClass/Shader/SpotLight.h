#pragma once

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;
using namespace SimpleMath;

//------------------------------------------------------------------------------
//	ライトエフェクト定義
//------------------------------------------------------------------------------
class SpotLight
{
public:
	SpotLight();
	~SpotLight() {};

	void Init();
	void SetPosition(Vector3 pos);
	void SetLightColor(SimpleMath::Vector4 color);
	void SetAmbientColor(Vector4 color);
	void SetCone(float angle);
	void SetPower(float pow);
	void SetRange(float range);
	void SetMax(int maxLight);
	void PointRender(DX9::CAMERA,DX9::MODEL&);
	void ShadeRender(DX9::SKINNEDMODEL& model, SimpleMath::Vector4 color);
private:

	DX9::SHADER shader;

	int m_maxLight;
	Vector3 m_lightsPos;
	Vector3 m_lightDir;
	Vector4 m_diffuseColor;
	Vector4 m_ambientColor;
	float m_lightsPower;
	float m_cone;
	float m_range;
	
};