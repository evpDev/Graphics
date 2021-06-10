
Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}

struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct VS_IN2
{
	float4 pos : POSITION0;
	float2 tex : TEXCOORD0;
	float3 norm : NORMAL;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

struct PS_IN2
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 norm : TEXCOORD1;
};

PS_IN2 VSMain(VS_IN2 input)
{
	PS_IN2 output = (PS_IN2)0;
	output.pos = mul(input.pos, World);
	output.pos = mul(output.pos, View);
	output.pos = mul(output.pos, Projection);
	output.norm = mul(input.norm, World);
	output.tex = input.tex;

	return output;
}

//PS_IN VSMain( VS_IN input )
//{
//	PS_IN output = (PS_IN)0;
//	
//	output.pos = mul(input.pos, World);
//	output.pos = mul(output.pos, View);
//	output.pos = mul(output.pos, Projection);
//	//output.pos = input.pos;
//	output.col = input.col;
//	
//	return output;
//}
//
//float4 PSMain( PS_IN input ) : SV_Target
//{
//	float4 col = input.col;
//#ifdef TEST
//	if (input.pos.x > 400) col = TCOLOR;
//#endif
//
//	return col;
//}

float4 PSMain(PS_IN2 input) : SV_Target
{
	float4 col = DiffuseMap.Sample(Sampler, float2(input.tex.x, 1.0f - input.tex.y));
#ifdef TEST
	if (input.pos.x > 400) col = TCOLOR;
#endif

	return col;
}
