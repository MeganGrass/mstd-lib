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

float4 Light_Ambient : register(c13);
float3 Light_Position[3] : register(c14);
float4 Light_Color[3] : register(c17);
float Light_Intensity[3] : register(c20);

float LightingMode : register(c23); // 0 = None, 1 = Per-Vertex, 2 = Per-Pixel

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
    float3 WorldPos : TEXCOORD1;
    float3 NormalW : TEXCOORD2;
};

float4 PlayStationLighting(float3 WorldPos, float3 NormalW, float4 BaseColor)
{
    float3 Normal = normalize(NormalW);
    
    float3 Color = Light_Ambient.rgb;

    [unroll]
    for (int i = 0; i < 3; i++)
    {
        if (length(Light_Color[i].rgb) != 0.0f && length(Light_Position[i].xyz) != 0.0f)
        {
            float3 Vector = (Light_Position[i] - WorldPos) * Light_Intensity[i];
            float Attenuation = saturate(1.0f - dot(Vector, Vector));
            float nDot = max(0.0f, dot(Normal, normalize(Vector)));
            Color += nDot * Attenuation * Light_Color[i];
        }
    }
    
    Color.rgb = saturate(Color.rgb);

    // Color = floor(Color * 31.0f + 0.5f) / 31.0f;
    
    return BaseColor * float4(Color.rgb * 1.5f, 1.0f);
}

OUTPUT vecpc(INPUT_POINTC Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = float3(0.0f, 0.0f, 0.0f);
    Output.Color = Input.Color;
    Output.PointSize = Input.PointSize;
    Output.TexCoord = float2(0.0f, 0.0f);
    
    Output.WorldPos = wp.xyz;
    Output.NormalW = float3(0.0f, 0.0f, 0.0f);
    
    return Output;
}

OUTPUT vecpct(INPUT_POINTCT Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = float3(0.0f, 0.0f, 0.0f);
    Output.Color = Input.Color;
    Output.PointSize = Input.PointSize;
    Output.TexCoord = Input.TexCoord;
    
    Output.WorldPos = wp.xyz;
    Output.NormalW = float3(0.0f, 0.0f, 0.0f);
    
    return Output;
}

OUTPUT vec3t(INPUT_VERT3T Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = float3(0.0f, 0.0f, 0.0f);
    Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    Output.PointSize = 1.0f;
    Output.TexCoord = Input.TexCoord;
    
    Output.WorldPos = wp.xyz;
    Output.NormalW = float3(0.0f, 0.0f, 0.0f);
    
    return Output;
}

OUTPUT vec3n(INPUT_VERTN Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = Input.Normal;
    Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    Output.PointSize = 1.0f;
    Output.TexCoord = float2(0.0f, 0.0f);

    Output.WorldPos = wp.xyz;
    Output.NormalW = mul(Input.Normal, (float3x3)World);
    
    if (LightingMode == 1)
    {
        Output.Color = PlayStationLighting(Output.WorldPos, Output.NormalW, Output.Color);
    }
    
    return Output;
}

OUTPUT vec3nt(INPUT_VERTNT Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = Input.Normal;
    Output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);
    Output.PointSize = 1.0f;
    Output.TexCoord = Input.TexCoord;

    Output.WorldPos = wp.xyz;
    Output.NormalW = mul(Input.Normal, (float3x3)World);
    
    if (LightingMode == 1)
    {
        Output.Color = PlayStationLighting(Output.WorldPos, Output.NormalW, Output.Color);
    }
    
    return Output;
}

OUTPUT vec3c(INPUT_VERTC Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = float3(0.0f, 0.0f, 0.0f);
    Output.Color = (Input.Color.rgba == 0.0f) ? float4(1.0f, 1.0f, 1.0f, 1.0f) : Input.Color;
    Output.PointSize = 1.0f;
    Output.TexCoord = float2(0.0f, 0.0f);
    
    Output.WorldPos = wp.xyz;
    Output.NormalW = float3(0.0f, 0.0f, 0.0f);
    
    return Output;
}

OUTPUT vec3cn(INPUT_VERTCN Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = Input.Normal;
    Output.Color = (Input.Color.rgba == 0.0f) ? float4(1.0f, 1.0f, 1.0f, 1.0f) : Input.Color;
    Output.PointSize = 1.0f;
    Output.TexCoord = float2(0.0f, 0.0f);

    Output.WorldPos = wp.xyz;
    Output.NormalW = mul(Input.Normal, (float3x3)World);

    if (LightingMode == 1)
    {
        Output.Color = PlayStationLighting(Output.WorldPos, Output.NormalW, Output.Color);
    }
    
    return Output;
}

OUTPUT vec3ct(INPUT_VERTCT Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = float3(0.0f, 0.0f, 0.0f);
    Output.Color = (Input.Color.rgba == 0.0f) ? float4(1.0f, 1.0f, 1.0f, 1.0f) : Input.Color;
    Output.PointSize = 1.0f;
    Output.TexCoord = Input.TexCoord;

    Output.WorldPos = wp.xyz;
    Output.NormalW = float3(0.0f, 0.0f, 0.0f);
    
    return Output;
}

OUTPUT vec3cnt(INPUT_VERTCNT Input)
{
    OUTPUT Output;
    float4 wp = mul(Input.Position, World);
    Output.Position = mul(mul(wp, View), Projection);
    Output.Normal = Input.Normal;
    Output.Color = (Input.Color.rgba == 0.0f) ? float4(1.0f, 1.0f, 1.0f, 1.0f) : Input.Color;
    Output.PointSize = 1.0f;
    Output.TexCoord = Input.TexCoord;

    Output.WorldPos = wp.xyz;
    Output.NormalW = mul(Input.Normal, (float3x3)World);

    if (LightingMode == 1)
    {
        Output.Color = PlayStationLighting(Output.WorldPos, Output.NormalW, Output.Color);
    }
    
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

    if (Clip.z == 0 || Clip.z == 1)
    {
        Output.Position = float4(p.x, p.y, Clip.z, 1.0f);
    }
    else
    {
        float z = -32.0 * p.z;
        Output.Position = float4(p.x, p.y, -(z * Clip.z + Clip.w) / z, 1.0f);
    }
    
    Output.WorldPos = mul(Input.Position, World).xyz;
    Output.NormalW = float3(0.0f, 0.0f, 0.0f);

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

    if (Clip.z == 0 || Clip.z == 1)
    {
        Output.Position = float4(p.x, p.y, Clip.z, 1.0f);
    }
    else
    {
        float z = -32.0 * p.z;
        Output.Position = float4(p.x, p.y, -(z * Clip.z + Clip.w) / z, 1.0f);
    }
    
    Output.WorldPos = mul(Input.Position, World).xyz;
    Output.NormalW = float3(0.0f, 0.0f, 0.0f);

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
    Output.WorldPos = float3(0.0f, 0.0f, 0.0f);
    Output.NormalW = float3(0.0f, 0.0f, 0.0f);
    return Output;
}