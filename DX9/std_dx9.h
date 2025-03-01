/*
*
*	Megan Grass
*	April 12, 2024
*
*
*	TODO:
*		Draw is now broken because texture dimensions are pow2
*/


#pragma once

#include "../Windows/std_window.h"

#include "../Geometry/std_matrix.h"

#include "../std_image.h"

#include "../std_thread_pool.h"

#include <sony_texture.h>

#include <d3d9.h>

#include <d3dx9tex.h>

/*
	Shaders
*/
extern const char* VertexShaderCode;
extern const char* PixelShaderCode;
extern const char* PlayStationDitherShaderCode;

/*
	Point (Gouraud-shaded)
	 - vecp
*/
#define D3DFVF_POINTG (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE)

/*
	Point (Gouraud-shaded w/ Texture)
	 - vecpt
*/
#define D3DFVF_POINTGT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE | D3DFVF_TEX1)

/*
	Texture
	 - vec3t
*/
#define D3DFVF_TEX3D (D3DFVF_XYZ | D3DFVF_TEX1)

/*
	Texture W
	 - vec4t
*/
#define D3DFVF_TEX4D (D3DFVF_XYZRHW | D3DFVF_TEX1)

/*
	Vertex (w/ Normal)
	 - vec3n
*/
#define D3DFVF_VERTN (D3DFVF_XYZ | D3DFVF_NORMAL)

/*
	Vertex (w/ Normal and UV)
	 - vec3nt
*/
#define D3DFVF_VERTNT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

/*
	Vertex (Gouraud-shaded)
	 - vec3g
*/
#define D3DFVF_VERTG (D3DFVF_XYZ | D3DFVF_DIFFUSE)

/*
	Vertex (Gouraud-shaded w/ Normal)
	 - vec3gn
*/
#define D3DFVF_VERTGN (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)

/*
	Vertex (Gouraud-shaded w/ UV)
	 - vec3gt
*/
#define D3DFVF_VERTGT (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*
	Vertex (Gouraud-shaded w/ Normal and UV)
	 - vec3gnt
*/
#define D3DFVF_VERTGNT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

/*
	16-bit depth buffer
*/
const D3DFORMAT D3DFMT_DF16 = ((D3DFORMAT)(MAKEFOURCC('D', 'F', '1', '6')));

/*
	24-bit depth buffer
*/
const D3DFORMAT D3DFMT_DF24 = ((D3DFORMAT)(MAKEFOURCC('D', 'F', '2', '4')));

/*
	24-bit depth buffer/8-bit stencil buffer
*/
const D3DFORMAT D3DFMT_INTZ = ((D3DFORMAT)(MAKEFOURCC('I', 'N', 'T', 'Z')));

/*
	Dummy Render Target
*/
const D3DFORMAT D3DFMT_NULL = ((D3DFORMAT)(MAKEFOURCC('N', 'U', 'L', 'L')));

/*
	Direct-X 9 Device State
*/
enum class D3DDEVICE_STATE : int32_t
{
	NORMAL = (1 << 0),			// The device is normally operational
	LOST = (1 << 1),			// The device has been lost but cannot be reset at this time
	REMOVED = (1 << 2),			// The hardware adapter has been removed
	DRIVER_ERROR = (1 << 3),	// Internal driver error
	OUT_OF_MEMORY = (1 << 4),	// Direct3D does not have enough display memory to perform the operation
	UNKNOWN = -1				// The device state is unknown
};

/*
	Direct-X 9 Transparency Rate
*/
enum class D3DTRANSPARENCY_RATE : uint8_t
{
	NONE = 255,					// No transparency
	SIXTH = 192,                // 100%back + 16.67%polygon
	QUARTER = 160,				// 100%back + 25%polygon
	THIRD = 170,				// 100%back + 33.3%polygon
	HALF = 128,					// 50%back + 50%polygon
	TWO_THIRDS = 85,			// 100%back + 66.6%polygon
	THREE_QUARTER = 64,			// 100%back + 75%polygon
	SEVEN_EIGHTHS = 32,			// 100%back + 87.5%polygon
	FULL = 0,					// 100%back + 100%polygon
	INVERSE = 192				// 100%back - 100%polygon
};

/*
	Direct-X 9 Shader Packet
*/
struct D3DSHADERPACKET final
{
	ID3DXConstantTable* Const;
	IDirect3DVertexDeclaration9* Decl;
	IDirect3DVertexShader9* Shader;
};

/*
	Direct-X 9 Draw Packet
*/
struct D3DDRAWPACKET final
{
	IDirect3DVertexBuffer9* Vertices;
	IDirect3DIndexBuffer9* Indices;
	IDirect3DTexture9* Texture;
	IDirect3DPixelShader9* PixelShader;
	UINT Stride;
	bool bZBuffer;
	D3DZBUFFERTYPE ZType;
	D3DCMPFUNC ZFunc;
	D3DFILLMODE FillMode;
	D3DPRIMITIVETYPE PrimitiveType;
};

/*
	Direct-X 9 Texture custom deleter for smart pointers
*/
struct IDirect3DTexture9Delete
{
	void operator()(IDirect3DTexture9* texture) const
	{
		if (texture)
		{
			texture->Release();
			texture = nullptr;
		}
	}
};

/*
	Standard Direct-X 9
*/
class Standard_DirectX_9 final :
	private Standard_Thread_Pool {
private:

	std::shared_ptr<Standard_Window> Wnd;

	IDirect3D9Ex* pD3D;

	IDirect3DDevice9Ex* pDevice;

	IDirect3DSwapChain9Ex* pSwapChain;

	D3DCAPS9 DeviceCaps;

	D3DADAPTER_IDENTIFIER9 AdapterIdentifier;

	D3DDISPLAYMODE DisplayMode;

	D3DPRESENT_PARAMETERS PresentParameters;

	D3DDEVICE_STATE e_DeviceState;

	D3DINDEXBUFFER_DESC IndexBufferDesc;

	D3DVERTEXBUFFER_DESC VertexBufferDesc;

	D3DSURFACE_DESC TextureDesc;

	IDirect3DVertexBuffer9* AxisGrid;

	IDirect3DVertexBuffer9* XyzAxis;

	bool b_Ready;

	bool b_Abort;

	bool b_Active;

	bool b_Complete;

	bool b_NativeResolution;

	float m_NativeWidth;

	float m_NativeHeight;

	bool b_AntiAliasing;

	D3DTEXTUREFILTERTYPE m_TextureFilter;

	DWORD AmbientColor;

	void Update(void);

	void InitShaders(void);

	D3DSHADERPACKET ShaderVecp;

	D3DSHADERPACKET ShaderVecpg;

	D3DSHADERPACKET ShaderVecpgt;

	D3DSHADERPACKET ShaderVec3t;

	D3DSHADERPACKET ShaderVec4t;

	D3DSHADERPACKET ShaderVec3n;

	D3DSHADERPACKET ShaderVec3nt;

	D3DSHADERPACKET ShaderVec3g;

	D3DSHADERPACKET ShaderVec3gn;

	D3DSHADERPACKET ShaderVec3gt;

	D3DSHADERPACKET ShaderVec3gnt;

public:

	/*
		Generic Pixel Shader (optional)
		 - uv coordinates used when texture is bound
		 - diffuse color used when texture is not bound and diffuse exists
		 - solid white used when texture is not bound and diffuse does not exist
		 - this shader is used for generic draw functions when no other shader is specified
	*/
	IDirect3DPixelShader9* PassthroughPixelShader;

	/*
		Sony PlayStation (1994) Dithering Pixel Shader
	*/
	IDirect3DPixelShader9* PS1DitherPixelShader;

	explicit Standard_DirectX_9(void) :
		Wnd(nullptr),
		pD3D(nullptr),
		pDevice(nullptr),
		pSwapChain(nullptr),
		DeviceCaps(),
		AdapterIdentifier(),
		DisplayMode(),
		PresentParameters(),
		e_DeviceState(D3DDEVICE_STATE::UNKNOWN),
		IndexBufferDesc(),
		VertexBufferDesc(),
		TextureDesc(),
		AxisGrid(nullptr),
		XyzAxis(nullptr),
		b_Ready(false),
		b_Abort(false),
		b_Active(false),
		b_Complete(false),
		b_NativeResolution(false),
		m_NativeWidth(0.0f),
		m_NativeHeight(0.0f),
		b_AntiAliasing(true),
		m_TextureFilter(D3DTEXF_POINT),
		AmbientColor(0xFF808080),
		PassthroughPixelShader(nullptr),
		PS1DitherPixelShader(nullptr),
		ShaderVecp{},
		ShaderVecpg{},
		ShaderVecpgt{},
		ShaderVec3t{},
		ShaderVec4t{},
		ShaderVec3n{},
		ShaderVec3nt{},
		ShaderVec3g{},
		ShaderVec3gn{},
		ShaderVec3gt{},
		ShaderVec3gnt{}
	{
		ThreadPoolInit(1);
		ThreadPoolEnqueue([this]() { Update(); });
	}
	virtual ~Standard_DirectX_9(void)
	{
		Shutdown();

		while (!b_Complete)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (AxisGrid) { AxisGrid->Release(); AxisGrid = nullptr; }

		if (ShaderVecpg.Decl) { ShaderVecpg.Decl->Release(); ShaderVecpg.Decl = nullptr; }
		if (ShaderVecpg.Shader) { ShaderVecpg.Shader->Release(); ShaderVecpg.Shader = nullptr; }
		if (ShaderVecpg.Const) { ShaderVecpg.Const->Release(); ShaderVecpg.Const = nullptr; }

		if (ShaderVecpgt.Decl) { ShaderVecpgt.Decl->Release(); ShaderVecpgt.Decl = nullptr; }
		if (ShaderVecpgt.Shader) { ShaderVecpgt.Shader->Release(); ShaderVecpgt.Shader = nullptr; }
		if (ShaderVecpgt.Const) { ShaderVecpgt.Const->Release(); ShaderVecpgt.Const = nullptr; }

		if (ShaderVec3t.Decl) { ShaderVec3t.Decl->Release(); ShaderVec3t.Decl = nullptr; }
		if (ShaderVec3t.Shader) { ShaderVec3t.Shader->Release(); ShaderVec3t.Shader = nullptr; }
		if (ShaderVec3t.Const) { ShaderVec3t.Const->Release(); ShaderVec3t.Const = nullptr; }

		if (ShaderVec4t.Decl) { ShaderVec4t.Decl->Release(); ShaderVec4t.Decl = nullptr; }
		if (ShaderVec4t.Shader) { ShaderVec4t.Shader->Release(); ShaderVec4t.Shader = nullptr; }
		if (ShaderVec4t.Const) { ShaderVec4t.Const->Release(); ShaderVec4t.Const = nullptr; }

		if (ShaderVec3n.Decl) { ShaderVec3n.Decl->Release(); ShaderVec3n.Decl = nullptr; }
		if (ShaderVec3n.Shader) { ShaderVec3n.Shader->Release(); ShaderVec3n.Shader = nullptr; }
		if (ShaderVec3n.Const) { ShaderVec3n.Const->Release(); ShaderVec3n.Const = nullptr; }

		if (ShaderVec3nt.Decl) { ShaderVec3nt.Decl->Release(); ShaderVec3nt.Decl = nullptr; }
		if (ShaderVec3nt.Shader) { ShaderVec3nt.Shader->Release(); ShaderVec3nt.Shader = nullptr; }
		if (ShaderVec3nt.Const) { ShaderVec3nt.Const->Release(); ShaderVec3nt.Const = nullptr; }

		if (ShaderVec3g.Decl) { ShaderVec3g.Decl->Release(); ShaderVec3g.Decl = nullptr; }
		if (ShaderVec3g.Shader) { ShaderVec3g.Shader->Release(); ShaderVec3g.Shader = nullptr; }
		if (ShaderVec3g.Const) { ShaderVec3g.Const->Release(); ShaderVec3g.Const = nullptr; }

		if (ShaderVec3gn.Decl) { ShaderVec3gn.Decl->Release(); ShaderVec3gn.Decl = nullptr; }
		if (ShaderVec3gn.Shader) { ShaderVec3gn.Shader->Release(); ShaderVec3gn.Shader = nullptr; }
		if (ShaderVec3gn.Const) { ShaderVec3gn.Const->Release(); ShaderVec3gn.Const = nullptr; }

		if (ShaderVec3gt.Decl) { ShaderVec3gt.Decl->Release(); ShaderVec3gt.Decl = nullptr; }
		if (ShaderVec3gt.Shader) { ShaderVec3gt.Shader->Release(); ShaderVec3gt.Shader = nullptr; }
		if (ShaderVec3gt.Const) { ShaderVec3gt.Const->Release(); ShaderVec3gt.Const = nullptr; }

		if (ShaderVec3gnt.Decl) { ShaderVec3gnt.Decl->Release(); ShaderVec3gnt.Decl = nullptr; }
		if (ShaderVec3gnt.Shader) { ShaderVec3gnt.Shader->Release(); ShaderVec3gnt.Shader = nullptr; }
		if (ShaderVec3gnt.Const) { ShaderVec3gnt.Const->Release(); ShaderVec3gnt.Const = nullptr; }

		if (pSwapChain) { pSwapChain->Release(); pSwapChain = nullptr; }
		if (pDevice) { pDevice->Release(); pDevice = nullptr; }
		if (pD3D) { pD3D->Release(); pD3D = nullptr; }
	}

	/*
		Shutdown
	*/
	void Shutdown(void);

	/*
		Is renderer in normal state?
	*/
	bool NormalState(void) const { return e_DeviceState == D3DDEVICE_STATE::NORMAL; }

	/*
		Initialize
		 - if NativeResolution is true, Width and Height are used as the internal rendering resolution
		 - if NativeResolution is false, the window's client area size is used as the internal rendering resolution
		 - the drawing area will always be sized to the window's client area
	*/
	bool Initialize(std::shared_ptr<Standard_Window> StdWnd, UINT Width, UINT Height, bool NativeResolution = false);

	/*
		Update device state
	*/
	void Test(void);

	/*
		Reset device state
		 - device state may change
	*/
	void Reset(D3DPRESENT_PARAMETERS* Present = nullptr);

	/*
		Get Window
	*/
	[[nodiscard]] std::shared_ptr<Standard_Window> Window(void) const { return Wnd; }

	/*
		Get D3D
	*/
	[[nodiscard]] IDirect3D9Ex* D3D(void) const { return pD3D; }

	/*
		Get Device
	*/
	[[nodiscard]] IDirect3DDevice9Ex* Device(void) const { return pDevice; }

	/*
		Get device state
	*/
	[[nodiscard]] D3DDEVICE_STATE DeviceState(void) const { return e_DeviceState; }

	/*
		Get Swap Chain (additional)
	*/
	[[nodiscard]] IDirect3DSwapChain9Ex* SwapChain(void) const { return pSwapChain; }

	/*
		Get Device Caps
	*/
	[[nodiscard]] D3DCAPS9* GetDeviceCaps(void);

	/*
		Get Adapter Identifier
	*/
	[[nodiscard]] D3DADAPTER_IDENTIFIER9* GetAdapterId(void);

	/*
		Get Display Mode
	*/
	[[nodiscard]] D3DDISPLAYMODE* GetDisplayMode(void);

	/*
		Get Present Parameters
	*/
	[[nodiscard]] D3DPRESENT_PARAMETERS* GetPresentParameters(void) { return &PresentParameters; }

	/*
		Is render target format supported?
	*/
	[[nodiscard]] bool RenderTargetSupport(D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, Format));
	}

	/*
		Is surface format supported?
	*/
	[[nodiscard]] bool SurfaceFormatSupport(D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, NULL, D3DRTYPE_SURFACE, Format));
	}

	/*
		Is depth format supported?
	*/
	[[nodiscard]] bool DepthFormatSupport(D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, Format));
	}

	/*
		Is texture format supported?
	*/
	[[nodiscard]] bool TextureFormatSupport(D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, NULL, D3DRTYPE_TEXTURE, Format));
	}

	/*
		Is alpha blending supported?
	*/
	[[nodiscard]] bool AlphaBlendingSupport(D3DRESOURCETYPE Type, D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, Type, Format));
	}

	/*
		Is mipmap autogeneration supported?
	*/
	[[nodiscard]] bool MipmapAutogenerationSupport(D3DRESOURCETYPE Type, D3DFORMAT Format)
	{
		return !FAILED(pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDisplayMode()->Format, D3DUSAGE_AUTOGENMIPMAP, Type, Format));
	}

	/*
		Create Texture (32bpp)
		 - 4bpp/8bpp/16bpp/24bpp/32bpp supported
		 - Width and Height are automatically adjusted to power of two
		 - if "b_Alpha" is true and pixel color equals "AlphaColor", alpha channel will be set to "AlphaChannel"
	*/
	[[nodiscard]] IDirect3DTexture9* CreateTexture(std::unique_ptr<Standard_Image>& Image, bool b_Alpha = false, DWORD AlphaColor = 0xFF00FF, std::uint8_t AlphaChannel = 0x00);

	/*
		Create Texture (32bpp) from Sony PlayStation Texture (*.TIM)
		 - 4bpp/8bpp/16bpp/24bpp supported
		 - Width and Height are automatically adjusted to power of two
		 - if TransparencyFlags & Superblack, Full Transparency for solid black pixels (5:5:5:1 and 8:8:8)
		 - if TransparencyFlags & Superimposed, Semi/Full Transparency for palette index 0 (if available)
		 - if TransparencyFlags & External, Semi/Full Transparency for external color (TransparencyColor)
		 - if TransparencyFlags & STP, STP flag determines if Semi/Full Transparency is used
	*/
	[[nodiscard]] IDirect3DTexture9* CreateTexture(
		std::unique_ptr<Sony_PlayStation_Texture>& TIM,
		uint16_t iPalette = 0,
		Sony_Texture_Transparency TransparencyFlags = Sony_Texture_Transparency::None,
		DWORD TransparencyColor = 0xFF00FF);

	/*
		Save Texture (32bpp)
	*/
	bool SaveTexture(IDirect3DTexture9* Texture, D3DXIMAGE_FILEFORMAT Format, const std::filesystem::path& Filename);

	/*
		Create index buffer
	*/
	[[nodiscard]] IDirect3DIndexBuffer9* CreateIndexBuffer(D3DFORMAT Format, std::size_t Length);

	/*
		Create index buffer
	*/
	[[nodiscard]] IDirect3DIndexBuffer9* CreateIndexBuffer(D3DFORMAT Format, void* pData, std::size_t Length);

	/*
		Update index buffer
	*/
	void UpdateIndexBuffer(IDirect3DIndexBuffer9* Buffer, void* pData);

	/*
		Create vertex buffer
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVertexBuffer(DWORD FVF, std::size_t Length);

	/*
		Create vertex buffer
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVertexBuffer(DWORD FVF, void* pData, std::size_t Length);

	/*
		Update vertex buffer
	*/
	void UpdateVertexBuffer(IDirect3DVertexBuffer9* Buffer, void* pData);

	/*
		Create Point Vertex Buffer (Gouraud-shaded)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreatePoint(std::vector<vecpg> Data);

	/*
		Create Point Vertex Buffer (Gouraud-shaded)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreatePoint(std::vector<vec3> Vector, DWORD Color, float Size, D3DTRANSPARENCY_RATE TransparencyRate = D3DTRANSPARENCY_RATE::NONE);

	/*
		Create Point Vertex Buffer (Gouraud-shaded)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreatePoint(std::vector<vec3> Vector, std::vector<DWORD> Color, float Size, D3DTRANSPARENCY_RATE TransparencyRate = D3DTRANSPARENCY_RATE::NONE);

	/*
		Create Point Vertex Buffer (Gouraud-shaded)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreatePoint(std::vector<vec3> Vector, std::vector<DWORD> Color, std::vector<float> Size, D3DTRANSPARENCY_RATE TransparencyRate = D3DTRANSPARENCY_RATE::NONE);

	/*
		Create Point Vertex Buffer (Gouraud-shaded w/ Texture)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreatePoint(std::vector<vecpgt> Data);

	/*
		Create Texture Vertex Buffer
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3t(std::vector<vec3t> Data);

	/*
		Create Texture Vertex Buffer
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3t(std::vector<vec3> Vector, std::vector<vec2> UV);

	/*
		Create Texture Vertex Buffer (W)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec4t(std::vector<vec4t> Data);

	/*
		Create Texture Vertex Buffer (W)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec4t(std::vector<vec4> Vector, std::vector<vec2> UV);

	/*
		Create Vertex Buffer (w/ Normal)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3n(std::vector<vec3n> Data);

	/*
		Create Vertex Buffer (w/ Normal)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3n(std::vector<vec3> Vector, std::vector<vec3> Normal);

	/*
		Create Vertex Buffer (w/ UV)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3nt(std::vector<vec3nt> Data);

	/*
		Create Vertex Buffer (w/ UV)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3nt(std::vector<vec3> Vector, std::vector<vec3> Normal, std::vector<vec2> UV);

	/*
		Create Vertex Buffer (Gouraud-shaded)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3g(std::vector<vec3g> Data);

	/*
		Create Vertex Buffer (Gouraud-shaded)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3g(std::vector<vec3> Vector, DWORD Color, D3DTRANSPARENCY_RATE TransparencyRate = D3DTRANSPARENCY_RATE::NONE);

	/*
		Create Vertex Buffer (Gouraud-shaded w/ Normal)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3gn(std::vector<vec3gn> Data);

	/*
		Create Vertex Buffer (Gouraud-shaded w/ Normal)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3gn(std::vector<vec3> Vector, std::vector<vec3> Normal, DWORD Color, D3DTRANSPARENCY_RATE TransparencyRate = D3DTRANSPARENCY_RATE::NONE);

	/*
		Create Vertex Buffer (Gouraud-shaded w/ UV)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3gt(std::vector<vec3gt> Data);

	/*
		Create Vertex Buffer (Gouraud-shaded w/ UV)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3gt(std::vector<vec3> Vector, DWORD Color, std::vector<vec2> UV, D3DTRANSPARENCY_RATE TransparencyRate = D3DTRANSPARENCY_RATE::NONE);

	/*
		Create Vertex Buffer (Gouraud-shaded w/ Normal and UV)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3gnt(std::vector<vec3gnt> Data);

	/*
		Create Vertex Buffer (Gouraud-shaded w/ Normal and UV)
	*/
	[[nodiscard]] IDirect3DVertexBuffer9* CreateVec3gnt(std::vector<vec3> Vector, std::vector<vec3> Normal, DWORD Color, std::vector<vec2> UV, D3DTRANSPARENCY_RATE TransparencyRate = D3DTRANSPARENCY_RATE::NONE);

	/*
		Create pixel shader
	*/
	IDirect3DPixelShader9* CreatePixelShader(const char* Code, const char* FunctionName = "main", const char* Profile = "ps_3_0");

	/*
		Set vertex shader + matrix
		 - simplified version for pre-established shaders
	*/
	void SetVertexShader(DWORD FVF);

	/*
		Draw
		 - if D3DFILL_WIREFRAME is used, lighting and texture is disabled
		 - pixel shader info:
			Pixel Shader Constant (F) [c0] is set to texture width
			Pixel Shader Constant (F) [c1] is set to texture height
	*/
	void Draw(D3DDRAWPACKET Packet);

	/*
		Draw Point Vertex Buffer (Gouraud-shaded)
	*/
	void DrawPointG(IDirect3DVertexBuffer9* Buffer, IDirect3DPixelShader9* PixelShader = nullptr)
	{
		Draw({ Buffer, nullptr, nullptr, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vecpg), true, D3DZB_TRUE, D3DCMP_LESSEQUAL, D3DFILL_POINT, D3DPT_POINTLIST });
	}

	/*
		Draw Point Vertex Buffer (Gouraud-shaded w/ UV)
	*/
	void DrawPointGT(IDirect3DVertexBuffer9* Buffer, IDirect3DTexture9* Texture, IDirect3DPixelShader9* PixelShader = nullptr)
	{
		Draw({ Buffer, nullptr, Texture, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vecpgt), true, D3DZB_TRUE, D3DCMP_LESSEQUAL, D3DFILL_POINT, D3DPT_POINTLIST });
	}

	/*
		Draw Texture Vertex Buffer
	*/
	void DrawVec3t(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* PixelShader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, Texture, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vec3t), true, D3DZB_TRUE, ZFunc, FillMode, PrimitiveType });
	}

	/*
		Draw Texture Vertex Buffer (W)
		 - lighting will be disabled
	*/
	void DrawVec4t(IDirect3DVertexBuffer9* Buffer, IDirect3DTexture9* Texture, IDirect3DPixelShader9* PixelShader = nullptr);

	/*
		Draw Vertex Buffer (w/ Normal)
	*/
	void DrawVec3n(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DPixelShader9* PixelShader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, nullptr, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vec3n), true, D3DZB_TRUE, ZFunc, FillMode, PrimitiveType });
	}

	/*
		Draw Vertex Buffer (w/ UV)
	*/
	void DrawVec3nt(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* PixelShader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, Texture, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vec3nt), true, D3DZB_TRUE, ZFunc, FillMode, PrimitiveType });
	}

	/*
		Draw Vertex Buffer (Gouraud-shaded)
	*/
	void DrawVec3g(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DPixelShader9* PixelShader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, nullptr, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vec3g), true, D3DZB_TRUE, ZFunc, FillMode, PrimitiveType });
	}

	/*
		Draw Vertex Buffer (Gouraud-shaded w/ Normal)
	*/
	void DrawVec3gn(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DPixelShader9* PixelShader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, nullptr, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vec3gn), true, D3DZB_TRUE, ZFunc, FillMode, PrimitiveType });
	}

	/*
		Draw Vertex Buffer (Gouraud-shaded w/ UV)
	*/
	void DrawVec3gt(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* PixelShader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, Texture, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vec3gt), true, D3DZB_TRUE, ZFunc, FillMode, PrimitiveType });
	}

	/*
		Draw Vertex Buffer (Gouraud-shaded w/ Normal and UV)
	*/
	void DrawVec3gnt(
		IDirect3DVertexBuffer9* Buffer,
		IDirect3DIndexBuffer9* Indices,
		IDirect3DTexture9* Texture,
		IDirect3DPixelShader9* PixelShader = nullptr,
		D3DFILLMODE FillMode = D3DFILL_SOLID,
		D3DPRIMITIVETYPE PrimitiveType = D3DPT_TRIANGLESTRIP,
		D3DCMPFUNC ZFunc = D3DCMP_LESSEQUAL)
	{
		Draw({ Buffer, Indices, Texture, PixelShader ? PixelShader : PassthroughPixelShader, sizeof(vec3gnt), true, D3DZB_TRUE, ZFunc, FillMode, PrimitiveType });
	}

	/*
		Get D3DXMATRIX from Standard_Matrix
	*/
	[[nodiscard]] D3DXMATRIX* GetMatrix(Standard_Matrix Matrix) { return (D3DXMATRIX*)&Matrix; }

	/*
		Set world matrix
	*/
	D3DXMATRIX SetWorld(float X, float Y, float Z, float RX, float RY, float RZ, float SX = 1.0f, float SY = 1.0f, float SZ = 1.0f);

	/*
		Set world matrix
	*/
	void SetWorld(Standard_Matrix World) { pDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&World); }

	/*
		Set view matrix
	*/
	void SetView(Standard_Matrix View) { pDevice->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&View); }

	/*
		Set projection matrix
	*/
	void SetProjection(Standard_Matrix Projection) { pDevice->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&Projection); }

	/*
		Is the renderer in a normal state?
	*/
	[[nodiscard]] bool Ready(void) const { return b_Ready; }

	/*
		Was the device created with native resolution?
	*/
	[[nodiscard]] bool NativeResolution(void) const { return b_NativeResolution; }

	/*
		Get native width
		 - if return is 0.0f, the window's client area is used for the internal rendering resolution
	*/
	[[nodiscard]] float NativeWidth(void) const { return m_NativeWidth; }

	/*
		Get native height
		 - if return is 0.0f, the window's client area is used for the internal rendering resolution
	*/
	[[nodiscard]] float NativeHeight(void) const { return m_NativeHeight; }

	/*
		Get Ambient Light Color
	*/
	[[nodiscard]] DWORD Ambient(void) const { return AmbientColor; }

	/*
		Set Ambient Light Color
	*/
	void Ambient(DWORD Color) { AmbientColor = Color; }

	/*
		Set color transparency
	*/
	DWORD GetTransparency(DWORD Color, D3DTRANSPARENCY_RATE TransparencyRate) { return ((Color & 0xFFFFFF) | (std::to_underlying(TransparencyRate) << 24)); }

	/*
		Enable/Disable Anti-Aliasing
		 - highest (n)x MSAA available (4x max) is the default
	*/
	void AntiAliasing(bool OnOff);

	/*
		Enable/Disable Texture Filtering
	*/
	void TextureFiltering(D3DTEXTUREFILTERTYPE Type);

	/*
		Enable/Disable Lighting
	*/
	void Lighting(bool OnOff);

	/*
		Enable/Disable Z-Buffer
	*/
	void ZBuffer(bool OnOff, D3DZBUFFERTYPE Type, D3DCMPFUNC Func);

	/*
		Create Axis grid
	*/
	void CreateAxisGrid(void);

	/*
		Draw Axis grid
	*/
	void DrawAxisGrid(void)
	{
		Draw({ AxisGrid, nullptr, nullptr, PassthroughPixelShader, sizeof(vec3g), true, D3DZB_TRUE, D3DCMP_LESSEQUAL, D3DFILL_WIREFRAME, D3DPT_LINELIST });
		Draw({ XyzAxis, nullptr, nullptr, PassthroughPixelShader, sizeof(vec3g), true, D3DZB_TRUE, D3DCMP_LESSEQUAL, D3DFILL_WIREFRAME, D3DPT_LINELIST });
	}

	/*
		Save screenshot
	*/
	bool SaveScreenshot(D3DXIMAGE_FILEFORMAT Format, std::filesystem::path Output);

};