struct VSOUT
{
	float4 svpos : SV_POSITION;
};

struct VSIN
{
	float4 pos : POSTION;
};

VSOUT VS(VSIN input)
{
	VSOUT vsout;

	vsout.svpos = input.pos;

	return vsout;
}

float4 PS(VSOUT vsout) : SV_Target0
{
	return float4(1,1,1,1);
}