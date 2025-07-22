/*
*
*	Megan Grass
*	November 25, 2024
*
*	Dither Matrix: https://psx-spx.consoledev.net/graphicsprocessingunitgpu/#24bit-rgb-to-15bit-rgb-dithering-enabled-in-texpage-attribute
*
*/

const char* PlayStationDitherShaderCode = R"(
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

static const float DitherMatrix[4][4] =
{
	{ -4.0f, +0.0f, -3.0f, +1.0f },
	{ +2.0f, -2.0f, +3.0f, -1.0f },
	{ -3.0f, +1.0f, -4.0f, +0.0f },
	{ +3.0f, -1.0f, +2.0f, -2.0f }
};

float4 main(INPUT Input) : COLOR0
{
	if(ScaleX && ScaleY)
	{
		Input.TexCoord.x *= ScaleX;
		Input.TexCoord.y *= ScaleY;
	}

	float4 color = tex2D(TextureSampler, Input.TexCoord);
	
	int2 Pixel = int2(Input.TexCoord.x * Width, Input.TexCoord.y * Height);
	
	float Dither = DitherMatrix[Pixel.y % 4][Pixel.x % 4];

	color.r = max(0.0f, min(1.0f, color.r + Dither / 255));
	color.g = max(0.0f, min(1.0f, color.g + Dither / 255));
	color.b = max(0.0f, min(1.0f, color.b + Dither / 255));

	color.r = max(0.0f, min(1.0f, saturate(color.r)));
	color.g = max(0.0f, min(1.0f, saturate(color.g)));
	color.b = max(0.0f, min(1.0f, saturate(color.b)));

	return color;
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
