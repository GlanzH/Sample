float4x4 g_WVP;
float4x4 g_World;

float3 g_LightPos;
float  g_LightRange;
float3 g_LightDir;
float3 g_LightAtt;
float  g_Cone;
float4 g_AColor;
float4 g_Color;
float  g_Pow;

sampler tex : register(s0);

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
	float4 normal : TEXCOORD1;
	float2 uv   : TEXCOORD2;
};

VS_OUT VS(VS_IN input)
{
    VS_OUT output;

    output.pos = mul(input.pos, g_WVP);
    output.posw = mul(input.pos, g_World);

    output.normal = mul(input.nor, g_World);

    output.uv = input.uv;

    return output;
}

float4 PS(VS_OUT input) : COLOR0
{
    input.normal = normalize(input.normal);

    float4 diffuse = tex2D(tex,input.uv);

    float3 finalColor = float3(0.0f, 0.0f, 0.0f);

    //Create the vector between light position and pixels position
    float3 lightToPixelVec = g_LightPos - input.posw;

    //Find the distance between the light pos and pixel pos
    float d = length(lightToPixelVec);

    //Add the ambient light
    float3 finalAmbient = diffuse * g_AColor;

    //If pixel is too far, return pixel color with ambient light
    if (d > g_LightRange)
        return float4(finalAmbient, diffuse.a);

    //Turn lightToPixelVec into a unit length vector describing
    //the pixels direction from the lights position
    lightToPixelVec /= d;

    //Calculate how much light the pixel gets by the angle
    //in which the light strikes the pixels surface
    float howMuchLight = dot(lightToPixelVec, input.normal);

    //If light is striking the front side of the pixel
//    if (howMuchLight > 0.0f)
    {
        //Add light to the finalColor of the pixel
        finalColor += diffuse * g_Color;

        //Calculate Light's Distance Falloff factor
        finalColor /= (g_LightAtt.x + (g_LightAtt.y * d)) + (g_LightAtt.z * (d * d));

        //Calculate falloff from center to edge of pointlight cone
        finalColor *= pow(max(dot(-lightToPixelVec, g_LightDir), 0.0f), g_Cone);
    }

    //make sure the values are between 1 and 0, and add the ambient
    finalColor = saturate(finalColor + finalAmbient);

    //Return Final Color
    return float4(finalColor * g_Pow, diffuse.a);
}

//-----------------------------------------------------------------------------
// Techniques
//-----------------------------------------------------------------------------
technique PointLight
{
    pass P0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader = compile ps_3_0 PS();
    }
}
