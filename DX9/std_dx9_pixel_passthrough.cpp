/*
*
*	Megan Grass
*	November 25, 2024
*
*/

const char* PixelShaderCode = R"(
sampler2D TextureSampler : register(s0);
float Width : register(c0);
float Height : register(c1);

struct INPUT
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR0;
	float PointSize : PSIZE;
	float2 TexCoord : TEXCOORD0;
};

float4 main(INPUT Input) : COLOR0
{
	if ((Width == 0.0f && Height == 0.0f))
	{
		return Input.Color;
	}
	else
	{
		float4 Color = tex2D(TextureSampler, Input.TexCoord);
		return Color;
	}
}

technique ShaderTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 main();
		PixelShader = compile ps_3_0 main();
	}
}
)";