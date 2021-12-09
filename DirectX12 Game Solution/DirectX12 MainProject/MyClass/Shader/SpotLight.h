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

	void Init(int num);
	void SetPosition(Vector3 pos,int index);
	void SetLightColor(Vector4 color,int index);
	void SetAmbientColor(Vector4 color, int index);
	void SetAtt(Vector3 att, int index);
	void SetAngle(Vector3 angle, int index);
	void SetCone(float angle, int index);
	void SetPower(float pow, int index);
	void SetRange(float range, int index);
	void PointRender(DX9::CAMERA,DX9::MODEL&);
	void ShadeRender(DX9::SKINNEDMODEL& model, SimpleMath::Vector4 color);
private:

	DX9::SHADER shader;

	int m_maxLight;
	Vector3 m_lightsPos[10];
	Vector3 m_lightDir[10];
	Vector4 m_diffuseColor[10];
	Vector4 m_ambientColor[10];
	Vector3 m_att[10];
	float m_lightsPower[10];
	float m_cone[10];
	float m_range[10];
	
};