
sampler smp : register(s0);

int    g_numLight;

float4 g_vLightPos[10];
float4 g_Ambient[10];
float4 g_Diffuse[10];
float4 g_Specular[10];

float g_Pow[10];

float4 g_vEye;
matrix g_mW;
matrix g_mWVP;

struct VS_OUTPUT
{
	float4 Pos 			: POSITION;
	float3 LightDir		: TEXCOORD0;
	float3 Normal 		: TEXCOORD1;
	float3 EyeVector	: TEXCOORD2;
	float3 WorldPos		: TEXCOORD4;
	float2 Tex 			: TEXCOORD3;
};

VS_OUTPUT VS(float4 Pos : POSITION, float4 Norm : NORMAL , float2 uv : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	// �ˉe�ϊ�
	output.Pos = mul(Pos, g_mWVP);

	// �@��
	output.Normal = mul(Norm, (float3x3)g_mW);

	// ���C�g�ʒu
	float3 PosWorld = mul(Pos, g_mW);
	output.WorldPos = float4(PosWorld, 1.0f);

	// �����x�N�g��
	output.EyeVector = normalize(g_vEye - PosWorld);

	output.Tex = uv;


	return output;
}

float4 PLight(int index, float3 Pos, float3 Normal, float3 EyeVector)
{
	float3 LightDir = normalize(g_vLightPos[index] - Pos);
	float  NL = saturate(dot(Normal, LightDir));

	/*
		// ����(����͖��g�p)
		float4 ambient = g_Ambient[lidx] / 2.0f;
	*/

	// �g�U���ˌ�
	float4 diffuse = g_Diffuse[index] * NL;

	/*
		// ���ʔ��ˌ�(����͖��g�p)
		float3 reflect  = normalize(2.0f * NL * Normal - LightDir);
		float4 specular = pow(saturate(dot(reflect, EyeVector)), 4.0f) * g_Specular[lidx];

		float4 color = diffuse + specular;
	*/
	// ���f���̍ŏI�F
	float4 color = diffuse;

	// ���C�g����
	float Distance = length(g_vLightPos[index] - Pos);

	color *= g_Pow[index];

	color *= 1.0 / (0.0f + 0.0f * Distance + 0.001f * Distance * Distance);

	/*
		// �����̔��f(����͖��g�p)
		color += ambient;
	*/
	return color;
}

float4 PS(VS_OUTPUT input) : COLOR0
{
	float4 col = 0;

	// �S�Ẵ��C�g�̍ŏI�F�̍���
	for (int i = 0; i < g_numLight; i++)
	{
		col += PLight(i,input.WorldPos, input.Normal, input.EyeVector);
	}
	col = saturate(col * 1.0f);
	col.a = 0.5f;


	return  col * tex2D(smp, input.Tex);
}

technique main
{
	pass
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}