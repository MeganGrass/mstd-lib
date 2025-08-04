/*
*
*	Megan Grass
*	November 25, 2024
*
*/

const char* HomogeneousShaderCode = R"(
uniform float4x4 Projection;
uniform float4 Clip;

struct INPUT_VERT4T
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD0;
};

struct INPUT_VERT4CT
{
	float4 Position : POSITION;
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

OUTPUT vec4t(INPUT_VERT4T Input)
{
    OUTPUT Output;
    Output.Normal = float3(0.0f, 0.0f, 0.0f);
    Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    Output.PointSize = 1.0f;
    Output.TexCoord = Input.TexCoord;

	float4 p = mul(Input.Position, Projection);

	float z = 0.0f;

	if (Clip.z == 0 || Clip.z == 1)
	{
		z = Clip.z;
	}
	else
	{
		z = (Input.Position.z * Clip.z) / Clip.w;
	}

	Output.Position = float4(p.x, p.y, z, 1.0f);

    return Output;
}

OUTPUT vec4ct(INPUT_VERT4CT Input)
{
    OUTPUT Output;
    Output.Normal = float3(0.0f, 0.0f, 0.0f);
    Output.Color = Input.Color;
    Output.PointSize = 1.0f;
    Output.TexCoord = Input.TexCoord;

	float4 p = mul(Input.Position, Projection);

	float z = 0.0f;

	if (Clip.z == 0 || Clip.z == 1)
	{
		z = Clip.z;
	}
	else
	{
		z = (Input.Position.z * Clip.z) / Clip.w;
	}

	Output.Position = float4(p.x, p.y, z, 1.0f);

    return Output;
}
)";