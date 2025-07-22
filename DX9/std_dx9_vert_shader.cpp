/*
*
*	Megan Grass
*	November 25, 2024
*
*/

const char* VertexShaderCode = R"(
cbuffer MatrixBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
};

cbuffer LightBuffer : register(b1)
{
	int LightMag;
	int LightMode[3];
	float3 LightDiffuse[3];
	float3 LightAmbient;
	float3 LightPosition[3];
	float LightRange[3];
};

struct INPUT_POINTC
{
	float3 Position : POSITION;
	float4 Color : COLOR0;
	float PointSize : PSIZE;
};

struct INPUT_POINTCT
{
	float3 Position : POSITION;
	float4 Color : COLOR0;
	float PointSize : PSIZE;
	float2 TexCoord : TEXCOORD0;
};

struct INPUT_TEX3D
{
	float3 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
};

struct INPUT_TEX4D
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
};

struct INPUT_VERTN
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
};

struct INPUT_VERTNT
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD0;
};

struct INPUT_VERTC
{
	float4 Position : POSITION;
	float4 Color : COLOR0;
};

struct INPUT_VERTCN
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR0;
};

struct INPUT_VERTCT
{
	float4 Position : POSITION;
	float4 Color : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

struct INPUT_VERTCNT
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

struct OUTPUT
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR0;
	float PointSize : PSIZE;
	float2 TexCoord : TEXCOORD0;
};

OUTPUT vecpc(INPUT_POINTC Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(float4(Input.Position, 1.0f), World), View), Projection);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = Input.PointSize;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vecpct(INPUT_POINTCT Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(float4(Input.Position, 1.0f), World), View), Projection);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = Input.PointSize;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3t(INPUT_TEX3D Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(float4(Input.Position, 1.0f), World), View), Projection);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec4t(INPUT_TEX4D Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3n(INPUT_VERTN Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = Input.Normal;
	Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	Output.PointSize = 1.0f;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vec3nt(INPUT_VERTNT Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = Input.Normal;
	Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3c(INPUT_VERTC Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = 1.0f;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vec3cn(INPUT_VERTCN Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = Input.Normal;
	Output.Color = Input.Color;
	Output.PointSize = 1.0f;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vec3ct(INPUT_VERTCT Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3cnt(INPUT_VERTCNT Input)
{
	OUTPUT Output;
	Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = Input.Normal;
	Output.Color = Input.Color;
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}
)";