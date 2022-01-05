//---------------------------------------------------------------------------
//	【プログラム】
//		マルチスポットライト生成FX
//
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//	グローバル
//---------------------------------------------------------------------------

static const int MAX_MATRICES = 26;

float4x4  g_WVP;
float4x4  g_World;

float4x4  g_VP;
float4x4  g_WorldMatrixArray[MAX_MATRICES];
int       g_NumBones = 1;

float4 g_mDiffuse;
float4 g_mAmbient;
float4 g_mSpecular;
float4 g_mEmissive;
float  g_mPower;

static const int MAXLIGHT = 2;

float3 g_LightPos[MAXLIGHT];
float3 g_LightDir[MAXLIGHT];
float3 g_LightAtt[MAXLIGHT];
float  g_Cone[MAXLIGHT];
float4 g_AColor[MAXLIGHT];
float4 g_Color[MAXLIGHT];
float  g_LightRange[MAXLIGHT];
float  g_Pow[MAXLIGHT];
int    g_Count;

//テクスチャ
sampler tex : register(s0);

//バーテックスシェーダー入力構造体
struct VS_IN
{
	float4 pos : POSITION;
	float4 nor : NORMAL;
    float4 weights: BLENDWEIGHT;
    float4 indices : BLENDINDICES;
	float2 uv  : TEXCOORD;
};

//バーテックスシェーダー出力構造体
struct VS_OUT
{
	float4 pos  : POSITION;
	float4 posw : TEXCOORD0;
	float4 normal : TEXCOORD1;
	float2 uv   : TEXCOORD2;
};

//---------------------------------------------------------------------------
//	バーテックスシェーダー
//---------------------------------------------------------------------------
VS_OUT VS(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    int indexArray[4] = (int[4])input.indices;
    float blendWeightsArray[4] = (float[4])input.weights;

    float lastWeight = 0;
    for (int i = 0; i < g_NumBones - 1; i++)
    {
        output.pos.xyz += mul(input.pos, g_WorldMatrixArray[indexArray[i]]) * blendWeightsArray[i];
        output.normal.xyz += mul(input.pos, g_WorldMatrixArray[indexArray[i]]) * blendWeightsArray[i];

        lastWeight += blendWeightsArray[i];
    }
    lastWeight = 1.0f - lastWeight;

    output.pos.xyz += (mul(input.pos, g_WorldMatrixArray[indexArray[g_NumBones - 1]]) * lastWeight);

    output.normal.xyz += (mul(input.nor, g_WorldMatrixArray[indexArray[g_NumBones - 1]]) * lastWeight);

    output.posw = mul(input.pos, g_World);

    output.pos.w = 1.0f;
    output.pos = mul(output.pos, g_VP);
    //output.normal.w = 1.0f;

    output.uv = input.uv;

    return output;
}

//---------------------------------------------------------------------------
//	ピクセルシェーダー用関数　
//---------------------------------------------------------------------------
float4 OneLight(VS_OUT input, int index)
{
    //テクスチャ
    float4 texColor = tex2D(tex, input.uv);
    //初期化
    float3 finalColor = float3(0.0f, 0.0f, 0.0f);

    //ベクトル計算
    float3 lightToPixelVec = g_LightPos[index] - input.posw;

    //ライトの距離
    float d = length(lightToPixelVec);

    //環境光追加
    float3 finalAmbient = texColor * g_AColor[index];

    //ライトのレンジ外は環境光で
    if (d > g_LightRange[index])
        return float4(finalAmbient, texColor.a);

    //Normalize
    lightToPixelVec /= d;

    //法線への角度によって光の強さを変える
    float howMuchLight = dot(lightToPixelVec, input.normal);

    //テクスチャとライトの色の合成
    finalColor += texColor * g_Color[index];

    //距離減衰
    finalColor /= (g_LightAtt[index].x + (g_LightAtt[index].y * d)) + (g_LightAtt[index].z * (d * d));

    //角度減衰
    finalColor *= pow(max(dot(-lightToPixelVec, g_LightDir[index]), 0.0f), g_Cone[index]);

    //0~1にクランプ
    finalColor = saturate(finalColor + finalAmbient);

    return float4(finalColor * g_Pow[index], texColor.a);
}

//---------------------------------------------------------------------------
//	ピクセルシェーダー
//---------------------------------------------------------------------------
float4 PS(VS_OUT input) : COLOR0
{
    float4 color = float4(0,0,0,0);

    input.normal = normalize(input.normal);

    //複数ライトの合成
    for (int i = 0; i < g_Count; i++)
    {
        color += OneLight(input, i);
    }

    color = saturate(color * 1.0f);

    return color;
}

//-----------------------------------------------------------------------------
// Techniques
//-----------------------------------------------------------------------------
technique SpotLight
{
    pass P0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader = compile ps_3_0 PS();
    }
}
