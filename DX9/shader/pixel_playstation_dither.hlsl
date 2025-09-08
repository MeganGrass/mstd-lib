/*
*
*	Megan Grass
*	November 26, 2024
*
*	Dither Matrix: https://psx-spx.consoledev.net/graphicsprocessingunitgpu/#24bit-rgb-to-15bit-rgb-dithering-enabled-in-texpage-attribute
*
*/

sampler2D TextureSampler : register(s0);

float Width : register(c0);
float Height : register(c1);
float ScaleX : register(c2);
float ScaleY : register(c3);

float4 Light_Ambient : register(c5);
float3 Light_Position[3] : register(c6);
float4 Light_Color[3] : register(c9);
float Light_Intensity[3] : register(c12);

float LightingMode : register(c15); // 0 = None, 1 = Per-Vertex, 2 = Per-Pixel

struct INPUT
{
    float4 Position : POSITION;
    float3 Normal : NORMAL;
    float4 Color : COLOR0;
    float PointSize : PSIZE;
    float2 TexCoord : TEXCOORD0;
    float3 WorldPos : TEXCOORD1;
    float3 NormalW : TEXCOORD2;
};

static const float DitherMatrix[4][4] =
{
	{ -4.0f, +0.0f, -3.0f, +1.0f },
	{ +2.0f, -2.0f, +3.0f, -1.0f },
	{ -3.0f, +1.0f, -4.0f, +0.0f },
	{ +3.0f, -1.0f, +2.0f, -2.0f }
};

static const float DitherMatrixAlt[4][4] =
{
    { -4.0f, +2.0f, -3.0f, +3.0f },
    { +0.0f, -2.0f, +1.0f, -1.0f },
    { -3.0f, +3.0f, -4.0f, +2.0f },
    { +1.0f, -1.0f, +0.0f, -2.0f }
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
            Color += nDot * Attenuation * Light_Color[i].rgb;
        }
    }
        
    Color.rgb = saturate(Color.rgb);

    return BaseColor * float4(Color.rgb * 1.5f, 1.0f);
}

float4 main(INPUT Input) : COLOR0
{
    if (Width == 0.0f && Height == 0.0f)
    {
        if (LightingMode == 2)
        {
            return PlayStationLighting(Input.WorldPos, Input.NormalW, Input.Color);
        }
        else if (LightingMode == 1)
        {
            return Input.Color * float4(Input.Color.rgb, 1.0f);
        }
        return Input.Color;
    }

    float2 ScaledTexCoord = Input.TexCoord;
    
    if (ScaleX != 0.0f && ScaleY != 0.0f)
    {
        ScaledTexCoord.x *= ScaleX;
        ScaledTexCoord.y *= ScaleY;
    }
    
    float4 BaseColor = tex2D(TextureSampler, ScaledTexCoord);
	
	int2 Pixel = int2(Input.TexCoord.x * Width, Input.TexCoord.y * Height);
	
	float Dither = DitherMatrix[Pixel.y % 4][Pixel.x % 4];

    BaseColor.r = max(0.0f, min(1.0f, BaseColor.r + Dither / 255.0f));
    BaseColor.g = max(0.0f, min(1.0f, BaseColor.g + Dither / 255.0f));
    BaseColor.b = max(0.0f, min(1.0f, BaseColor.b + Dither / 255.0f));

    BaseColor.r = max(0.0f, min(1.0f, saturate(BaseColor.r)));
    BaseColor.g = max(0.0f, min(1.0f, saturate(BaseColor.g)));
    BaseColor.b = max(0.0f, min(1.0f, saturate(BaseColor.b)));
    
    if (LightingMode == 2)
    {
        return PlayStationLighting(Input.WorldPos, Input.NormalW, BaseColor);
    }
    else if (LightingMode == 1)
    {
        return BaseColor * float4(Input.Color.rgb, 1.0f);
    }

    return BaseColor;
}
