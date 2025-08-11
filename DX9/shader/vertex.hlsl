/*
*
*	Megan Grass
*	November 26, 2024
*
*/

float4x4 World : register(c0);
float4x4 View : register(c4);
float4x4 Projection : register(c8);
float4 Clip : register(c12);

struct INPUT_POINTC
{
    float4 Position : POSITION;
	float4 Color : COLOR0;
	float PointSize : PSIZE;
};

struct INPUT_POINTCT
{
    float4 Position : POSITION;
	float4 Color : COLOR0;
	float PointSize : PSIZE;
	float2 TexCoord : TEXCOORD0;
};

struct INPUT_VERT3T
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

OUTPUT vecpc(INPUT_POINTC Input)
{
    OUTPUT Output;
    Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = Input.PointSize;
	Output.TexCoord = float2(0.0f, 0.0f);
	return Output;
}

OUTPUT vecpct(INPUT_POINTCT Input)
{
    OUTPUT Output;
    Output.Position = mul(mul(mul(Input.Position, World), View), Projection);
	Output.Normal = float3(0.0f, 0.0f, 0.0f);
	Output.Color = Input.Color;
	Output.PointSize = Input.PointSize;
	Output.TexCoord = Input.TexCoord;
	return Output;
}

OUTPUT vec3t(INPUT_VERT3T Input)
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
        if (z > 1.0f)
        {
            z *= 0.5f;
        }
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

OUTPUT main()
{
    OUTPUT Output;
    Output.Position = float4(0.0f, 0.0f, 0.0f, 0.0f);
    Output.Normal = float3(0.0f, 0.0f, 0.0f);
    Output.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
    Output.PointSize = 0.0f;
    Output.TexCoord = float2(0.0f, 0.0f);
    return Output;
}