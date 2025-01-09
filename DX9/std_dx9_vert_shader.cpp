/*
*
*	Megan Grass
*	November 25, 2024
*
*/

const char* VertexShaderCode = R"(
cbuffer MatrixBuffer : register(b0)
{
	matrix WorldViewProjectionMatrix;
	matrix WorldMatrix;
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

struct INPUT_POINTG
{
	float3 Position : POSITION;
	float4 Color : COLOR0;
	float PointSize : PSIZE;
};

struct INPUT_POINTGT
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

struct INPUT_VERTG
{
	float4 Position : POSITION;
	float4 Color : COLOR0;
};

struct INPUT_VERTGN
{
	float4 Position : POSITION;
	float3 Normal : NORMAL;
	float4 Color : COLOR0;
};

struct INPUT_VERTGT
{
	float4 Position : POSITION;
	float4 Color : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

struct INPUT_VERTGNT
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

OUTPUT vecpg(INPUT_POINTG Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(float4(Input.Position, 1.0f), WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = Input.PointSize;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vecpgt(INPUT_POINTGT Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(float4(Input.Position, 1.0f), WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = Input.PointSize;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3t(INPUT_TEX3D Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(float4(Input.Position, 1.0f), WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec4t(INPUT_TEX4D Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(Input.Position, WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3n(INPUT_VERTN Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(Input.Position, WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = Input.Normal;
	Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	Output.PointSize = 1.0f;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vec3nt(INPUT_VERTNT Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(Input.Position, WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = Input.Normal;
	Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3g(INPUT_VERTG Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(Input.Position, WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = 1.0f;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vec3gn(INPUT_VERTGN Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(Input.Position, WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = Input.Normal;
	Output.Color = Input.Color;
	Output.PointSize = 1.0f;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vec3gt(INPUT_VERTGT Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(Input.Position, WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3gnt(INPUT_VERTGNT Input)
{
	OUTPUT Output;
	float4 worldPosition = mul(Input.Position, WorldMatrix);
	Output.Position = mul(worldPosition, WorldViewProjectionMatrix);
	Output.Normal = Input.Normal;
	Output.Color = Input.Color;
	Output.PointSize = 1.0f;
	Output.TexCoord = Input.TexCoord;
	return Output;
}
)";