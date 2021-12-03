//-----------------------------------------------------------------------------
// File: Lambert.fx
//
// The effect file for the Lambert HLSL sample.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// VertexShader Output Structure
//-----------------------------------------------------------------------------
struct VS_IN
{
	float4 pos : POSITION;
	float4 nor : NORMAL;
    float2 uv  : TEXCOORD;
};

struct VS_OUT
{
	float4 pos  : POSITION;
	float4 posw : TEXCOORD0;
	float4 norw : TEXCOORD1;
    float2 uv   : TEXCOORD2;
};

sampler tex : register(s0);
//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4 g_World;
float4x4 g_View;
float4x4 g_Projection;
float4   g_Light;
float4   g_Attenuation;
float    g_Pow;

float4   g_DLightDir;
float4   g_Ambient;

//-----------------------------------------------------------------------------
// pass0 VertexShader Main Function
//-----------------------------------------------------------------------------
VS_OUT VS_P0_Main(VS_IN input)
{
    VS_OUT output;
    float3 nor;
    float  col;

    output.posw = mul(input.pos, g_World);
    output.pos  = mul(output.posw, g_View);
    output.pos  = mul(output.pos, g_Projection);

    output.norw = mul(input.nor, g_World);
    output.uv = input.uv;

    return output;
}

float4 PS_P0_Main(VS_OUT input) : COLOR0
{
    float3 dir;
    float  len;
    float  colD;
    float  colA;
    float  col;

    float3 L = -normalize(g_DLightDir.xyz);

    float4 colorD = max(float4(1,1,1,1), dot(input.norw, L));

    //ì_åıåπÇÃï˚å¸
    dir = g_Light.xyz - input.posw.xyz;

    //ì_åıåπÇÃãóó£
    len = length(dir);

    //ì_åıåπÇÃï˚å¸Çnormalize
    dir = dir / len;

    //ägéU
    colD = saturate(dot(normalize(input.norw.xyz), dir));
    //å∏êä
    colA = saturate(1.0f / (g_Attenuation.x + g_Attenuation.y * len + g_Attenuation.z * len * len));

    col = colD * colA * g_Pow;
    col = col + colorD;

    return float4(col, col, col, 1.0f) * tex2D(tex,input.uv);
}

//-----------------------------------------------------------------------------
// Techniques
//-----------------------------------------------------------------------------
technique PointLight
{
   pass P0
   {
      VertexShader = compile vs_3_0 VS_P0_Main();
      PixelShader  = compile ps_3_0 PS_P0_Main();
   }
}
