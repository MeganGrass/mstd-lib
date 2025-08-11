/*
*
*	Megan Grass
*	December 5, 2024
*
*/

sampler2D TextureSampler : register(s0);
float Width : register(c0);
float Height : register(c1);
float ScaleX : register(c2);
float ScaleY : register(c3);

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
	if (!Width && !Height)
	{
		return Input.Color;
	}
	else if (ScaleX && ScaleY)
	{
		Input.TexCoord.x *= ScaleX;
		Input.TexCoord.y *= ScaleY;
	}
	return tex2D(TextureSampler, Input.TexCoord);
}
